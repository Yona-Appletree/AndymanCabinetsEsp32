//
// Created by Yona Appletree on 12/30/19.
//

#include "ui.h"
#include "util.h"
#include <FastLED.h>
#include <EEPROM.h>

static CRGB g_uiLeds[UI_LED_COUNT];

UiState g_uiState = {
	.programMode = 0,
	.colorMode = RAINBOW,
	.brightness = 1.0,
	.speed = 1.0,
	.time = 0,
	.effectMode = 0
};

bool g_uiStateNeedsPersist = false;

void readInputs();
void updateUiLeds();
void updateTime();
void persistChanges();
void readAndValidateState();













////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UI Displays
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class UIBrightnessDial : public UIDisplay {
public:
	const char * name() override {
		return "Brightness Dial";
	}

protected:
	void render(
		uint64_t deltaTime,
		double brightness
	) override {
		FastLED.setBrightness(32 * brightness);

		double endLed = (UI_LED_COUNT) * g_uiState.brightness;
		double endLedBrightness = endLed - int(endLed);

		for (int i=0; i<UI_LED_COUNT; i++) {
			if (i <= ceil(endLed)) {
				g_uiLeds[i] = CRGB(
					64 + ((i * 255) / (UI_LED_COUNT - 1)) / 2,
					64 + ((i * 255) / (UI_LED_COUNT - 1)) / 3,
					0
				);
			}

			if (i == ceil(endLed)) {
				g_uiLeds[i].nscale8_video(endLedBrightness);
			}
		}
	}
};

class UIDisplayPreview : public UIDisplay {
public:
	CabinetRing previewRing {
		.host = nullptr,
		.cabinets = {
			new CabinetInfo(7, TOP_RIGHT, true, 1),
			new CabinetInfo(7, TOP_LEFT, true, 2)
		}
	};

	const char * name() override {
		return "Preview";
	}

protected:
	void render(
		uint64_t deltaTime,
		double brightness
	) override {
		auto pVisualizationProgram = g_visualizationPrograms[g_uiState.programMode % g_visualizationPrograms.size()];
		auto pVisualizationEffect = g_visualizationEffects[g_uiState.effectMode % g_visualizationEffects.size()];

		pVisualizationProgram->applyToRing(previewRing, deltaTime);
		pVisualizationEffect->applyToRing(previewRing, deltaTime);

		FastLED.setBrightness(64 * g_uiState.brightness / 8 * brightness);

		// Start writing to the output leds offset by program mode to give the effect of a turning dial
		int outputLedIndex = UI_LED_COUNT + 1 + g_uiState.programMode - g_visualizationPrograms.size() / 2;

		for (auto cab : previewRing.cabinets) {
			for (int ledIndex = 0; ledIndex < cab->ledCount; ledIndex++) {
				g_uiLeds[(outputLedIndex++) % UI_LED_COUNT] = cab->buffer[ledIndex];
			}

			g_uiLeds[(outputLedIndex++) % UI_LED_COUNT] = CRGB::Black;
		}
	}
};


class UIPaletteDial : public UIDisplay {
public:
	const char * name() override {
		return "Palette Dial";
	}

	uint32_t activationMs() override {
		return 9000;
	}

protected:
	void render(
		uint64_t deltaTime,
		double brightness
	) override {
		FastLED.setBrightness(24 * brightness);

		auto time = double(millis() % 4000) / 4000;

		g_uiLeds[
			(UI_LED_COUNT + g_uiState.colorMode - ColorModeCount / 2) % UI_LED_COUNT
		] = CRGB::Yellow;

		int ledIndex = (UI_LED_COUNT + ColorModeCount - ColorModeCount / 2) % UI_LED_COUNT + 1;

		const int paletteLedCount = UI_LED_COUNT - ColorModeCount - 2;

		for (int i=0; i < paletteLedCount; i++) {
			g_uiLeds[ledIndex % UI_LED_COUNT] = colorFor(
				(double(i) / (paletteLedCount - 1) / 4) + time,
				(1.0 / (paletteLedCount - 1) / 4)
			);
			ledIndex ++;
		}
	}
};


class UISpeedDial : public UIDisplay {
public:
	const char * name() override {
		return "Speed Dial";
	}

protected:

	void bar(
		double center,
		double size,
		const CRGB& color,
		double multiplier
	) {
		double halfSize = size / 2;

		int startLed = floor(center - halfSize);
		int endLed = ceil(center + halfSize);

		for (int i=startLed; i<endLed; i++) {
			double distance = abs((i + .5) - center);
			if (distance > UI_LED_COUNT - halfSize) {
				distance = UI_LED_COUNT - distance;
			}

			if (distance < halfSize) {
				double brightness = 1 - distance / halfSize;

				CRGB& led = g_uiLeds[(i+UI_LED_COUNT) % UI_LED_COUNT];

				led += CRGB(
					std::min(255.0, color.r * brightness * multiplier),
					std::min(255.0, color.g * brightness * multiplier),
					std::min(255.0, color.b * brightness * multiplier)
				);
			}
		}
	}

	void render(
		uint64_t deltaTime,
		double brightness
	) override {
		FastLED.setBrightness(32 * brightness);

		auto time = double(g_uiState.time % 3000) / 3000;

		int endLed = round((UI_LED_COUNT - 1) * g_uiState.speed);

		bar(
			mapd(
				g_uiState.speed,
				0,
				1,
				1/16.0,
				15/16.0
			) * UI_LED_COUNT,
			4,
			CRGB::Yellow,
			1.7
		);
		bar(UI_LED_COUNT * time, 5, CRGB::Blue, 1.15);
	}
};

struct {
	UIPaletteDial paletteDial;
	UIBrightnessDial brightnessDial;
	UISpeedDial speedDial;
	UIDisplayPreview visualizationPreview;

	std::vector<UIDisplay *> displays = {
		& visualizationPreview,
		& paletteDial,
		& brightnessDial,
		& speedDial,
	};

	UIDisplay * currentDisplay = &visualizationPreview;
	uint64_t currentDisplayExpireMs = 0;

	void activate(UIDisplay& display) {
		currentDisplay = &display;
		if (&display == &visualizationPreview) {
			// Set it far back in time to avoid fade in
			currentDisplayExpireMs = 0;
		} else {
			currentDisplayExpireMs = millis() + display.activationMs();
		}
		//Serial.printf("Display \"%s\" for %dms\n", display.name(), display.activationMs());
	}

	bool isActive(UIDisplay& display) {
		return currentDisplay == &display;
	}
} display;


//////////////////////////////////////////////////////
// Base Implementation

void UIDisplay::update(
	double brightness
) {
	auto deltaTime = millis() - lastUpdateMs;
	lastUpdateMs = millis();

	// Clear Display
	for (auto & uiLed : g_uiLeds) {
		uiLed = CRGB::Black;
	}

	// Render
	render(
		deltaTime,
		brightness
	);

	// Luminance Correction
	for (auto & uiLed : g_uiLeds) {
		uiLed.r = scale8(uiLed.r, uiLed.r);
		uiLed.g = scale8(uiLed.g, uiLed.g);
		uiLed.b = scale8(uiLed.b, uiLed.b);
	}

	FastLED.show();
}

uint32_t UIDisplay::activationMs() {
	return 8000;
}













////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Hardware Handling
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IRAM_ATTR programRotaryIsr() {
	static int a0=0, a1=0, b0=0, b1=0;
	a1 = a0;
	b1 = b0;
	a0 = digitalRead(UI_PIN_MODE_A);
	b0 = digitalRead(UI_PIN_MODE_B);

	if (a0 == 0 && a1 == 1 && b0 == 0 && b1 == 0) {
		// Clockwise
		if (g_uiState.programMode < g_visualizationPrograms.size() - 1) {
			g_uiState.programMode = g_uiState.programMode + 1;

			Serial.printf("[UI] Next Program (%d): %s\n",
			              g_uiState.programMode,
			              g_visualizationPrograms[g_uiState.programMode]->name());
			g_uiStateNeedsPersist = true;
		}
	} else if (a0 == 0 && a1 == 0 && b0 == 0 && b1 == 1) {
		// Counterclockwise
		if (g_uiState.programMode > 0) {
			g_uiState.programMode = g_uiState.programMode - 1;

			Serial.printf("[UI] Prev Program (%d): %s\n",
			              g_uiState.programMode,
			              g_visualizationPrograms[g_uiState.programMode]->name());
			g_uiStateNeedsPersist = true;
		}
	}

	display.activate(display.visualizationPreview);
}

void IRAM_ATTR programButtonIsr() {
	// Clockwise
	if (g_uiState.effectMode < g_visualizationEffects.size() - 1)
		g_uiState.effectMode = g_uiState.effectMode + 1;
	else
		g_uiState.effectMode = 0;

	Serial.printf("[UI] Next Effect (%d): %s\n", g_uiState.effectMode, g_visualizationEffects[g_uiState.effectMode]->name());

	//g_uiDisplayProgress.displayProgress(g_uiState.effectMode, g_visualizationEffects.size(), false);
	g_uiStateNeedsPersist = true;
}


void IRAM_ATTR colorRotaryIsr() {
	static int a0=0, a1=0, b0=0, b1=0;
	a1 = a0;
	b1 = b0;
	a0 = digitalRead(UI_PIN_COLOR_A);
	b0 = digitalRead(UI_PIN_COLOR_B);

	if (a0 == 0 && a1 == 1 && b0 == 0 && b1 == 0) {
		// Clockwise
		if (g_uiState.colorMode < ColorModeCount - 1) {
			g_uiState.colorMode = static_cast<ColorMode>(g_uiState.colorMode + 1);

			Serial.printf("[UI] Next Color: %d\n", g_uiState.colorMode);
			g_uiStateNeedsPersist = true;
		}
	} else if (a0 == 0 && a1 == 0 && b0 == 0 && b1 == 1) {
		// Counterclockwise
		if (g_uiState.colorMode > 0) {
			g_uiState.colorMode = static_cast<ColorMode>(g_uiState.colorMode - 1);

			Serial.printf("[UI] Prev Color: %d\n", g_uiState.colorMode);
			g_uiStateNeedsPersist = true;
		}
	}

	display.activate(display.paletteDial);
}

void IRAM_ATTR colorButtonIsr() {
	g_uiState.colorMode = static_cast<ColorMode>(0);

	display.activate(display.visualizationPreview);
}













////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Lifecycle Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void uiSetup() {
	// Initialize the LEDs
	CFastLED::addLeds<WS2812B, UI_PIN_LED, GRB>(g_uiLeds, UI_LED_COUNT);
	FastLED.setCorrection(TypicalSMD5050);

	EEPROM.begin(sizeof(g_uiState));
	readAndValidateState();

	pinMode(UI_PIN_MODE_A, INPUT);
	pinMode(UI_PIN_MODE_B, INPUT);
	pinMode(UI_PIN_MODE_BTN, INPUT);

	pinMode(UI_PIN_COLOR_A, INPUT);
	pinMode(UI_PIN_COLOR_B, INPUT);
	pinMode(UI_PIN_COLOR_BTN, INPUT);

	attachInterrupt(UI_PIN_MODE_A, programRotaryIsr, CHANGE);
	attachInterrupt(UI_PIN_MODE_B, programRotaryIsr, CHANGE);
	attachInterrupt(UI_PIN_MODE_BTN, programButtonIsr, FALLING);

	attachInterrupt(UI_PIN_COLOR_A, colorRotaryIsr, CHANGE);
	attachInterrupt(UI_PIN_COLOR_B, colorRotaryIsr, CHANGE);
	attachInterrupt(UI_PIN_COLOR_BTN, colorButtonIsr, FALLING);
}

void uiLoop() {
	readInputs();
	updateUiLeds();
	updateTime();

	persistChanges();
}













////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utility Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void readAndValidateState() {
	EEPROM.readBytes(0, &g_uiState, sizeof(g_uiState));

	g_uiState.programMode = g_uiState.programMode % g_visualizationPrograms.size();
	g_uiState.colorMode = static_cast<ColorMode>(g_uiState.colorMode % ColorModeCount);
	g_uiState.time = 0;

	g_uiState.speed = isnan(g_uiState.speed) ? 0.5 : g_uiState.speed;
	g_uiState.brightness = isnan(g_uiState.brightness) ? 0.5 : g_uiState.brightness;

	g_uiState.effectMode = g_uiState.effectMode % g_visualizationEffects.size();

	Serial.println("UI Settings Loaded");
}

void persistChanges() {
	static auto lastPersistMs = 0;

	if (g_uiStateNeedsPersist && (millis() - lastPersistMs) > 10000) {
		g_uiStateNeedsPersist = false;

		EEPROM.writeBytes(0, &g_uiState, sizeof(g_uiState));
		EEPROM.commit();

		Serial.println("UI Settings Persisted");

		lastPersistMs = millis();
	}
}

void updateTime() {
	static auto lastTime = millis();
	auto now = millis();

	auto timeDelta = now - lastTime;
	lastTime = now;

	g_uiState.time += timeDelta * g_uiState.speed;
}

void readInputs() {
	// Update Speed
	double newSpeed = analogRead(UI_PIN_SPEED) / 4096.0;
	if (abs(newSpeed - g_uiState.speed) > 0.03) {
		g_uiState.speed = newSpeed;
		Serial.printf("Speed: %f (%d)\n", newSpeed,  analogRead(UI_PIN_SPEED));
		display.activate(display.speedDial);
	}

	// Update Brightness
	double newBrightness = analogRead(UI_PIN_BRIGHTNESS) / 4096.0;
	if (abs(newBrightness - g_uiState.brightness) > 0.03) {
		g_uiState.brightness = newBrightness;
		Serial.printf("Brightness: %f (%d)\n", newBrightness, analogRead(UI_PIN_BRIGHTNESS));
		display.activate(display.brightnessDial);
	}
}

void updateUiLeds() {
	const int fadeInMs = 1000;
	const int fadeOutMs = 1500;

	if (millis() > display.currentDisplayExpireMs) {
		display.currentDisplay = & display.visualizationPreview;
	}

	double brightness = 1.0;
	if (display.currentDisplay != & display.visualizationPreview) {
		auto remainingMs = display.currentDisplayExpireMs - millis();
		if (remainingMs < fadeOutMs) {
			brightness = double(remainingMs) / fadeOutMs;
		}
	} else {
		auto durationMs = millis() - display.currentDisplayExpireMs;
		if (durationMs < fadeInMs) {
			brightness = double(durationMs) / fadeInMs;
		}
	}

	display.currentDisplay->update(brightness);
}

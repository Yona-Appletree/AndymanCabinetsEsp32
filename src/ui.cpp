//
// Created by Yona Appletree on 12/30/19.
//

#include "ui.h"
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

class UIDisplayPreview : public UIDisplay {
public:
	UIDisplayPreview(
		uint8_t defaultPriority,
		uint8_t increasedPriority
	) : UIDisplay(defaultPriority, increasedPriority) {}

	CabinetRing previewRing {
		.host = nullptr,
		.cabinets = {
			new CabinetInfo(7, TOP_RIGHT, true, 1),
			new CabinetInfo(7, TOP_LEFT, true, 2)
		}
	};

protected:
	void render(uint64_t deltaTime) override {
		auto pVisualizationProgram = g_visualizationPrograms[g_uiState.programMode % g_visualizationPrograms.size()];
		auto pVisualizationEffect = g_visualizationEffects[g_uiState.effectMode % g_visualizationEffects.size()];

		pVisualizationProgram->applyToRing(previewRing, deltaTime);
		pVisualizationEffect->applyToRing(previewRing, deltaTime);

		auto rawBright = dim8_video(255*g_uiState.brightness);
		auto uiBright = rawBright / 4;

		FastLED.setBrightness(uiBright == 0 ? (rawBright == 0 ? 0 : 1) : uiBright);

		// Start writing to the output leds offset by program mode to give the effect of a turning dial
		int outputLedIndex = g_uiState.programMode + 1;

		for (auto cab : previewRing.cabinets) {
			for (int ledIndex = 0; ledIndex < cab->ledCount; ledIndex++) {
				g_uiLeds[(outputLedIndex++) % UI_LED_COUNT] = cab->buffer[ledIndex];
			}

			g_uiLeds[(outputLedIndex++) % UI_LED_COUNT] = CRGB::Black;
		}

		FastLED.show();
	}
};


class UIDisplayDial : public UIDisplay {
public:
	UIDisplayDial(
		uint8_t defaultPriority,
		uint8_t increasedPriority
	) : UIDisplay(defaultPriority, increasedPriority) {}

	uint8_t value;
	uint8_t maxValue;

	bool progressMode = false;

	CRGB activeColor = CRGB(0, 32, 0);
	CRGB inactiveColor = CRGB(0, 0, 0);
	CRGB marginColor = CRGB(4, 0, 0);

	void displayProgress(
		uint8_t value,
		uint8_t maxValue,
		bool progressMode
	) {
		this->value = value;
		this->maxValue = maxValue;
		this->progressMode = progressMode;
		this->increasePriorityFor(1000);
	}

protected:
	void render(uint64_t deltaTime) override {
		FastLED.setBrightness(255);

		int ledsPerSection = UI_LED_COUNT / maxValue;
		int ledIndex = 0;
		for (int secIndex=0; secIndex < maxValue; secIndex++) {
			for (int i=0; i<ledsPerSection; i++, ledIndex++) {
				if (progressMode) {
					if (secIndex <= value) {
						g_uiLeds[ledIndex] = activeColor;
						g_uiLeds[ledIndex].nscale8(std::max(8, (secIndex * 256) / maxValue));
					} else {
						g_uiLeds[ledIndex] = inactiveColor;
					}
				} else {
					g_uiLeds[ledIndex] = (secIndex == value) ? activeColor : inactiveColor;
				}
			}
		}

		for (; ledIndex<UI_LED_COUNT; ledIndex++) {
			g_uiLeds[ledIndex] = marginColor;
		}

		FastLED.show();
	}
};

UIDisplayDial g_uiDisplayProgress(100, 192);
UIDisplayPreview g_uiDisplayPreview(128, 110);

std::vector<UIDisplay *> g_uiDisplays = {
	& g_uiDisplayPreview,
	& g_uiDisplayProgress,
};


//////////////////////////////////////////////////////
// Base Implementation


UIDisplay::UIDisplay(uint8_t defaultPriority, uint8_t increasedPriority)
	: defaultPriority(defaultPriority), increasedPriority(increasedPriority) {}

void UIDisplay::increasePriorityFor(
	uint32_t durationMs
) {
	restoreDefaultPriorityAtMs = millis() + durationMs;
	currentPriority = increasedPriority;
}

void UIDisplay::update() {
	auto deltaTime = millis() - lastUpdateMs;
	lastUpdateMs = millis();

	if (millis() > restoreDefaultPriorityAtMs) {
		currentPriority = defaultPriority;
	}

	// Clear Display
	for (auto & uiLed : g_uiLeds) {
		uiLed = CRGB::Black;
	}

	// Render
	render(
		deltaTime
	);

	// Luminance Correction
	for (auto & uiLed : g_uiLeds) {
		uiLed.r = scale8_video(uiLed.r, uiLed.r);
		uiLed.g = scale8_video(uiLed.g, uiLed.g);
		uiLed.b = scale8_video(uiLed.b, uiLed.b);
	}
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
		if (g_uiState.programMode < g_visualizationPrograms.size() - 1)
			g_uiState.programMode = g_uiState.programMode + 1;
		else
			g_uiState.programMode = 0;
		
		Serial.printf("[UI] Next Program (%d): %s\n", g_uiState.programMode, g_visualizationPrograms[g_uiState.programMode]->name());
		g_uiStateNeedsPersist = true;
	} else if (a0 == 0 && a1 == 0 && b0 == 0 && b1 == 1) {
		// Counterclockwise
		if (g_uiState.programMode > 0)
			g_uiState.programMode = g_uiState.programMode - 1;
		else
			g_uiState.programMode = g_visualizationPrograms.size() - 1;
		
		Serial.printf("[UI] Prev Program (%d): %s\n", g_uiState.programMode, g_visualizationPrograms[g_uiState.programMode]->name());
		g_uiStateNeedsPersist = true;
	}
}

void IRAM_ATTR programButtonIsr() {
	// Clockwise
	if (g_uiState.effectMode < g_visualizationEffects.size() - 1)
		g_uiState.effectMode = g_uiState.effectMode + 1;
	else
		g_uiState.effectMode = 0;

	Serial.printf("[UI] Next Effect (%d): %s\n", g_uiState.effectMode, g_visualizationEffects[g_uiState.effectMode]->name());

	g_uiDisplayProgress.displayProgress(g_uiState.effectMode, g_visualizationEffects.size(), false);
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
		if (g_uiState.colorMode < ColorModeCount - 1)
			g_uiState.colorMode = static_cast<ColorMode>(g_uiState.colorMode + 1);
		else
			g_uiState.colorMode = static_cast<ColorMode>(0);
		
		Serial.printf("[UI] Next Color: %d\n", g_uiState.colorMode);
		g_uiDisplayProgress.displayProgress(g_uiState.colorMode, ColorModeCount, false);
		g_uiStateNeedsPersist = true;
	} else if (a0 == 0 && a1 == 0 && b0 == 0 && b1 == 1) {
		// Counterclockwise
		if (g_uiState.colorMode > 0)
			g_uiState.colorMode = static_cast<ColorMode>(g_uiState.colorMode - 1);
		else
			g_uiState.colorMode = static_cast<ColorMode>(ColorModeCount - 1);
		
		Serial.printf("[UI] Prev Color: %d\n", g_uiState.colorMode);
		g_uiDisplayProgress.displayProgress(g_uiState.colorMode, ColorModeCount, false);
		g_uiStateNeedsPersist = true;
	}
}

void IRAM_ATTR colorButtonIsr() {
	g_uiState.colorMode = static_cast<ColorMode>(0);

	Serial.printf("[UI] Color Reset\n");
	g_uiStateNeedsPersist = true;
}













////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Lifecycle Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void uiSetup() {
	// Initialize the LEDs
	CFastLED::addLeds<WS2812B, UI_PIN_LED, GRB>(g_uiLeds, UI_LED_COUNT);

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
	if (abs(newSpeed - g_uiState.speed) > 0.05) {
		g_uiState.speed = newSpeed;
		Serial.printf("Speed: %f (%d)\n", newSpeed,  analogRead(UI_PIN_SPEED));
		g_uiDisplayProgress.displayProgress(round(g_uiState.speed*15), 16, true);
	}

	// Update Brightness
	double newBrightness = analogRead(UI_PIN_BRIGHTNESS) / 4096.0;
	if (abs(newBrightness - g_uiState.brightness) > 0.05) {
		g_uiState.brightness = newBrightness;
		Serial.printf("Brightness: %f (%d)\n", newBrightness, analogRead(UI_PIN_BRIGHTNESS));
		g_uiDisplayProgress.displayProgress(round(g_uiState.brightness*15), 16, true);
	}
}

void updateUiLeds() {
	UIDisplay* highestPriorityDisplay = g_uiDisplays[0];
	for (auto display : g_uiDisplays) {
		if (display->currentPriority > highestPriorityDisplay->currentPriority) {
			highestPriorityDisplay = display;
		}
	}

	highestPriorityDisplay->update();
}

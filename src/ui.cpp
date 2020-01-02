//
// Created by Yona Appletree on 12/30/19.
//

#include "ui.h"
#include <FastLED.h>

int readRotarySwitch(
	int pin,
	int count
);

void readInputs();
void updateUiLeds();
void printValues();

void uiSetup() {
	// Initialize the LEDs
	CFastLED::addLeds<WS2812B, UI_PIN_LED, GRB>(g_uiLeds, UI_LED_COUNT);
}

void uiLoop() {
	readInputs();
	updateUiLeds();
	printValues();
}

void readInputs() {
	// Update Speed
	double newSpeed = analogRead(UI_PIN_SPEED) / 4096.0;
	if (abs(newSpeed - g_uiState.speed) > 0.01)
		g_uiState.speed = newSpeed;

	// Update Brightness
	double newBrightness = analogRead(UI_PIN_BRIGHTNESS) / 4096.0;
	if (abs(newBrightness - g_uiState.brightness) > 0.01)
		g_uiState.brightness = newBrightness;

	// Update Program Mode
	g_uiState.programMode = static_cast<ProgramMode>(readRotarySwitch(UI_PIN_COLOR, 6));

	// Update Color Mode
	g_uiState.colorMode = static_cast<ColorMode>(readRotarySwitch(UI_PIN_MODE, 6));
}

void updateUiLeds() {
	FastLED.setBrightness(uint8_t(g_uiState.brightness * 32));

	auto colorFunc = colorFunctionForMode(g_uiState.colorMode);
	int period = 500 + (1 - g_uiState.speed) * 3000;
	auto time = double(millis() % period) / period;

	for (int i=0; i<UI_LED_COUNT; i++) {
		g_uiLeds[i] = colorFunc((time + double(i) / UI_LED_COUNT));
	}

	FastLED.show();
}


void printValues() {
	static int lastMode = -1;
	int curMode = readRotarySwitch(UI_PIN_MODE, 6);
	if (curMode != lastMode) {
		lastMode = curMode;
		Serial.printf("Mode Value: %d (%d)\n", curMode, analogRead(UI_PIN_MODE));
	}

	static int lastColor = -1;
	int curColor = readRotarySwitch(UI_PIN_COLOR, 6);
	if (curColor != lastColor) {
		lastColor = curColor;
		Serial.printf("Color Value: %d (%d)\n", curColor, analogRead(UI_PIN_COLOR));
	}

	static int lastSpeed = -1;
	int curSpeed = analogRead(UI_PIN_SPEED);
	if (abs(curSpeed - lastSpeed) > 100) {
		lastSpeed = curSpeed;
		Serial.println(String("Speed Value: ") + curSpeed);
	}

	static int lastBright = -1;
	int curBright = analogRead(UI_PIN_BRIGHTNESS);
	if (abs(curBright - lastBright) > 100) {
		lastBright = curBright;
		Serial.println(String("Bright Value: ") + curBright);
	}
}



/**
 * Reads the switch position from a rotary switch connected to a series of resistors, like this:
 *
 * GPIO ---------------+
 *                     |
 *     (===========switch============)
 *     |     |     |     |     |     |
 *     v     v     v     v     v     v
 * GND - 1KΩ - 1KΩ - 1KΩ - 1KΩ - 1KΩ - VCC
 */

int readRotarySwitch(int pin, int count) {
	int increment = 4096 / (count - 1);
	int value = analogRead(pin);

	if (value < increment / 2) {
		return 0;
	}

	if (value > increment * (count - 2) + increment/2) {
		return count - 1;
	}

	return (value - increment/2) / increment + 1;
}
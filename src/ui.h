//
// Created by Yona Appletree on 12/30/19.
//

#ifndef ANDYMANCABINETSESP32_UI_H
#define ANDYMANCABINETSESP32_UI_H

#include <cstdint>
#include <FastLED.h>

#define UI_LED_COUNT (16)
#define UI_LED_PIN 32

static CRGB g_uiLeds[UI_LED_COUNT];

enum ProgramMode {
	OFF,
	ALL_SOLID,
	FADE_SINGLE,
	FADE_EACH,
	TWINKLE_FADE
};

enum ColorMode {
	RAINBOW,
	SUNSET,
	NATURE,
	FIRE,
	PARTY,
	CHANGING
};

static struct {
	ProgramMode programMode;
	ColorMode colorMode;
	uint8_t brightness;
	uint8_t speed;
} g_uiState;

void uiSetup();
void uiLoop();



#endif //ANDYMANCABINETSESP32_UI_H

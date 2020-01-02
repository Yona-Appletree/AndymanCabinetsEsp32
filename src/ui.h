//
// Created by Yona Appletree on 12/30/19.
//

#ifndef ANDYMANCABINETSESP32_UI_H
#define ANDYMANCABINETSESP32_UI_H

#include <cstdint>
#include <FastLED.h>
#include <color.h>
#include <mode.h>

#define UI_LED_COUNT (16)
#define UI_PIN_LED 32

#define UI_PIN_MODE       34
#define UI_PIN_COLOR      39

#define UI_PIN_BRIGHTNESS 33
#define UI_PIN_SPEED      35

static CRGB g_uiLeds[UI_LED_COUNT];

static struct {
	ProgramMode programMode;
	ColorMode colorMode;
	double brightness;
	double speed;
} g_uiState = {
	.programMode = NOISE,
	.colorMode = RAINBOW,
	.brightness = 1.0,
	.speed = 1.0
};

void uiSetup();
void uiLoop();

#endif //ANDYMANCABINETSESP32_UI_H

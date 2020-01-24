//
// Created by Yona Appletree on 12/30/19.
//

#ifndef ANDYMANCABINETSESP32_UI_H
#define ANDYMANCABINETSESP32_UI_H

#include <cstdint>
#include <FastLED.h>
#include <color.h>
#include <visualizations.h>

#define UI_LED_COUNT     (16)
#define UI_PIN_LED        14

#define UI_PIN_MODE_A       34
#define UI_PIN_MODE_B       33
#define UI_PIN_MODE_BTN     32

#define UI_PIN_COLOR_A      36
#define UI_PIN_COLOR_B      39
#define UI_PIN_COLOR_BTN    35

#define UI_PIN_BRIGHTNESS   15
#define UI_PIN_SPEED        13

struct UiState {
	int programMode;
	ColorMode colorMode;
	double brightness;
	double speed;
	int64_t time;
	int effectMode;
};

extern UiState g_uiState;

void uiSetup();
void uiLoop();

#endif //ANDYMANCABINETSESP32_UI_H

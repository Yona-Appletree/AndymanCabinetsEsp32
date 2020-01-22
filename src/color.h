//
// Created by Yona Appletree on 12/31/19.
//

#ifndef ANDYMANCABINETSESP32_COLOR_H
#define ANDYMANCABINETSESP32_COLOR_H

#include <functional>
#include <vector>
#include <FastLED.h>

void colorSetup();
void colorLoop();

CRGB colorFor(double value);
CRGB colorFor8(uint8_t value);
CRGB colorFor(
	double center,
	double width
);
CRGB colorFor8(
	double center,
	double width
);

enum ColorMode {
	RAINBOW,
	SUNSET,
	NATURE,
	FIRE,
	PARTY,
	CHANGING
};

const auto ColorModeCount = 6;

#endif //ANDYMANCABINETSESP32_COLOR_H

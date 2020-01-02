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

enum ColorMode {
	RAINBOW,
	SUNSET,
	NATURE,
	FIRE,
	PARTY,
	CHANGING
};

#endif //ANDYMANCABINETSESP32_COLOR_H

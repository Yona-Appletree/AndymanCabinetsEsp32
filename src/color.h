//
// Created by Yona Appletree on 12/31/19.
//

#ifndef ANDYMANCABINETSESP32_COLOR_H
#define ANDYMANCABINETSESP32_COLOR_H

#include <functional>
#include <vector>
#include <FastLED.h>

enum ColorMode {
	RAINBOW,
	SUNSET,
	NATURE,
	FIRE,
	PARTY,
	CHANGING
};

/**
 * Function that maps a fractional value to a color
 */
typedef std::function<CRGB(double)> TColorFunction;

CRGB colorRainbow(double value);
CRGB colorSunset(double value);
CRGB colorNature(double value);
CRGB colorFire(double value);
CRGB colorParty(double value);
CRGB colorChanging(double value);

TColorFunction colorFunctionForMode(ColorMode mode);


#endif //ANDYMANCABINETSESP32_COLOR_H

//
// Created by Yona Appletree on 12/31/19.
//

#include "renderer.h"

#ifndef ANDYMANCABINETSESP32_MODE_H
#define ANDYMANCABINETSESP32_MODE_H

#endif //ANDYMANCABINETSESP32_MODE_H

enum ProgramMode {
	OFF,
	ALL_SOLID,
	FADE_SINGLE,
	FADE_EACH,
	TWINKLE_FADE,
	NOISE
};

CRGB modeOff(const TLedColorFunctionProps& props);
CRGB modeAllSolid(const TLedColorFunctionProps& props);
CRGB modeFadeSingle(const TLedColorFunctionProps& props);
CRGB modeFadeEach(const TLedColorFunctionProps& props);
CRGB modeTwinkleFade(const TLedColorFunctionProps& props);
CRGB modeNoise(const TLedColorFunctionProps& props);

TLedColorFunction functionForMode(ProgramMode mode);
//
// Created by Yona Appletree on 12/31/19.
//

#include "mode.h"
#include <FastLED.h>
#include <noise.h>

CRGB modeOff(const TLedColorFunctionProps& props) {
	return CRGB::Black;
}

CRGB modeAllSolid(const TLedColorFunctionProps& props) {
	double time = double(props.millis % 3000) / 3000;

	return colorFor(time);
}

CRGB modeFadeSingle(const TLedColorFunctionProps& props) {
	double time = double(props.millis % 3000) / 3000;

	return colorFor(
		time + double(props.cabinetIndex) / props.ring.cabinets.size()
	);
}

CRGB modeFadeEach(const TLedColorFunctionProps& props) {
	double time = double(props.millis % 3000) / 3000;

	auto cabinetFrac = double(props.cabinetIndex) / props.ring.cabinets.size();
	auto ledFrac = double(props.ledIndex) / props.ring.cabinets[props.cabinetIndex].ledCount;

	return colorFor(
		time + ledFrac + cabinetFrac,
		1.0 / props.ring.cabinets[props.cabinetIndex].ledCount
	);
}

CRGB modeTwinkleFade(const TLedColorFunctionProps& props) {
	return CRGB::Black;
}

CRGB modeNoise(const TLedColorFunctionProps& props) {
	auto time = double(props.millis % 10000) / 10000;

	auto cabinetFrac = double(props.cabinetIndex) / props.ring.cabinets.size();
	auto ledFrac = double(props.ledIndex) / props.ring.cabinets[props.cabinetIndex].ledCount;

	return colorFor(
		cos16(
			inoise16(
				cabinetFrac * 256 * 256,
				ledFrac * 256 * 256,
				double(props.millis) * 24
			) + (time * 65536)
		) / 65536.0
	);
}


TLedColorFunction functionForMode(ProgramMode mode) {
	switch (mode) {
		case OFF:
			return modeOff;
		case ALL_SOLID:
			return modeAllSolid;
		case FADE_SINGLE:
			return modeFadeSingle;
		case FADE_EACH:
			return modeFadeEach;
		case TWINKLE_FADE:
			return modeTwinkleFade;
		case NOISE:
			return modeNoise;
	}
}
//
// Created by Yona Appletree on 12/31/19.
//

#include "mode.h"
#include "color.h"
#include <FastLED.h>

CRGB modeOff(const TLedColorFunctionProps& props) {
	return CRGB::Black;
}

CRGB modeAllSolid(const TLedColorFunctionProps& props) {
	double time = fmod(double(props.millis) / 1000, (1 - props.speed)*10);

	return props.colorFunction(time);
}

CRGB modeFadeSingle(const TLedColorFunctionProps& props) {
	double time = fmod(double(props.millis) / 1000, (1 - props.speed)*10);

	return props.colorFunction(
		time + double(props.cabinetIndex) / props.ring.cabinets.size()
	);
}

CRGB modeFadeEach(const TLedColorFunctionProps& props) {
	double time = fmod(double(props.millis) / 1000, (1 - props.speed)*10);

	return props.colorFunction(
		time + double(props.ledIndex) / props.ring.cabinets[props.cabinetIndex].ledCount
	);
}

CRGB modeTwinkleFade(const TLedColorFunctionProps& props) {
	return CRGB::Black;
}

CRGB modeNoise(const TLedColorFunctionProps& props) {
	auto ledPos = props.ring.ledPosInRing(
		props.cabinetIndex,
		props.ledIndex
	);

	double x = cos(ledPos.angle) * 10;
	double y = sin(ledPos.angle) * 10;

	return props.colorFunction(
		inoise16(
			x * 256,
			y * 256,
			(ledPos.z + double(props.millis) / 10 * props.speed) * 256
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
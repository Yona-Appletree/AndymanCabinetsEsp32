//
// Created by Yona Appletree on 12/31/19.
//

#include "color.h"
#include <colorpalettes.h>

DEFINE_GRADIENT_PALETTE(bhw3_32) {
	0,247,244,9,
	15,219,114,57,
	40,192,0,0,
	53,175,14,108,
	71,158,28,216,
	94,123,136,241,
	109,188,123,241,
	127,123,136,241,
	147,158,28,216,
	181,234,94,10,
	193,211,74,73,
	216,158,28,216,
	255,32,40,108,
};

CRGBPalette32 bhw3_32p = bhw3_32;

double triangle(double input) {
	input = fmod(input, 1.0);

	return input < 0.5
		? input / 0.5
		: 1 - (input - 0.5) / 0.5;
}

CRGB colorRainbow(double value) {
	return CHSV(triangle(value)*255, 255, 255);
}

CRGB colorSunset(double value) {
	return ColorFromPalette(bhw3_32p, triangle(value)*256);
}

CRGB colorNature(double value) {
	return ColorFromPalette(ForestColors_p, triangle(value)*256);
}

CRGB colorFire(double value) {
	return ColorFromPalette(HeatColors_p, triangle(value)*256);
}

CRGB colorParty(double value) {
	return ColorFromPalette(PartyColors_p, triangle(value)*256);
}

CRGB colorChanging(double value) {
	return CRGB::Black;
}

TColorFunction colorFunctionForMode(ColorMode mode) {
	switch (mode) {
		case RAINBOW: return colorRainbow;
		case SUNSET: return colorSunset;
		case NATURE: return colorNature;
		case FIRE: return colorFire;
		case PARTY: return colorParty;
		case CHANGING: return colorChanging;
	}
}

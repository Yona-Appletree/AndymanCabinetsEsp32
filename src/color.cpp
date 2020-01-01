//
// Created by Yona Appletree on 12/31/19.
//

#include "color.h"

CRGB colorRainbow(double value) {
	return CHSV(value*255, 255, 255);
}

CRGB colorSunset(double value) {
	return CRGB::Black;
}

CRGB colorNature(double value) {
	return CRGB::Black;
}

CRGB colorFire(double value) {
	return CRGB::Black;
}

CRGB colorParty(double value) {
	return CRGB::Black;
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

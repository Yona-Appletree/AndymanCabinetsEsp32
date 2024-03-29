//
// Created by Yona Appletree on 12/31/19.
//

#include "util.h"
#include "color.h"
#include "ui.h"
#include "presetPalettes.h"
#include "FastLED.h"
#include <colorpalettes.h>

CRGBPalette32 staticPalette;
static CRGBPalette32* g_currentPalette = & staticPalette;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Predefinitions

void handleModeChange();
void updatePalette();
void nblendPaletteTowardPalette2(CRGBPalette32& current, CRGBPalette32& target);

void updateRainbow();
void updateSunset();
void updateNature();
void updateFire();
void updateChanging();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Lifecycle Functions

void colorSetup() {}

void colorLoop() {
	switch (g_uiState.colorMode) {
		case RAINBOW: updateRainbow(); break;
		case SUNSET: updateSunset(); break;
		case NATURE: updateNature(); break;
		case FIRE: updateFire(); break;
		case CHANGING: updateChanging(); break;
	}
}

CRGB colorFor(double value) {
	return colorFor8(value * 255);
}

CRGB colorFor8(uint8_t value) {
	return ColorFromPalette(* g_currentPalette, value);
}

CRGB colorFor8(
	uint8_t center,
	uint8_t width
) {
	if (width == 0 || width == 1) {
		return colorFor8(center);
	}

	uint32_t r = 0;
	uint32_t g = 0;
	uint32_t b = 0;

	int start = int(center) - width/2;
	int end = int(center) + width/2;
	if (end - start < width) start --;

	for (int i=start; i<end; i++) {
		auto c = colorFor8(i);
		r += c.r;
		g += c.g;
		b += c.b;
	}

	return CRGB(r/width, g/width, b/width);
}

CRGB colorFor(
	double center,
	double width
) {
	return colorFor8(
		uint8_t(center * 255.0),
		uint8_t(width * 255.0)
	);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start Functions

void updateRainbow() {
	staticPalette = niceRainbow;
	g_currentPalette = & staticPalette;
}

void updateSunset() {
	staticPalette = bhw3_32;
	g_currentPalette = & staticPalette;
}



void updateNature() {
	static uint32_t lastSwitchMs = 0;

	static CRGBPalette32 currentPalette( CloudColors_p );
	static CRGBPalette32 targetPalette( LavaColors_p );

	static int blendCounter = 5;

	if (g_uiState.time - lastSwitchMs > uint32_t (1000 + (1 - g_uiState.speed) * 10000)) {
		lastSwitchMs = g_uiState.time;

		switch (random8() % 4) {
			case 0: targetPalette = CloudColors_p; break;
			case 1: targetPalette = LavaColors_p; break;
			case 2: targetPalette = OceanColors_p; break;
			case 3: targetPalette = ForestColors_p; break;
		}
	}

	nblendPaletteTowardPalette2(currentPalette, targetPalette);

	g_currentPalette = & currentPalette;
}

void updateFire() {
	staticPalette = HeatColors_p;
	g_currentPalette = & staticPalette;
}

void updateChanging() {
	static uint32_t lastSwitchMs = g_uiState.time;

	static CRGBPalette32 currentPalette( palettes[ random8() % paletteCount ] );
	static CRGBPalette32 targetPalette( palettes[ random8() % paletteCount ] );

	if (g_uiState.time - lastSwitchMs > 3000) {
		lastSwitchMs = g_uiState.time;
		targetPalette = palettes[random8() % paletteCount];
	}

	nblendPaletteTowardPalette2(currentPalette, targetPalette);

	g_currentPalette = & currentPalette;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utility Functions

void nblendPaletteTowardPalette2(CRGBPalette32 &current, CRGBPalette32 &target) {
	uint8_t* p1;
	uint8_t* p2;

	p1 = (uint8_t*)current.entries;
	p2 = (uint8_t*)target.entries;

	const uint8_t totalChannels = sizeof(CRGBPalette32);
	for( uint8_t i = 0; i < totalChannels; i++) {
		// if the values are equal, no changes are needed
		if( p1[i] == p2[i] ) { continue; }

		// if the current value is less than the target, increase it by one
		if( p1[i] < p2[i] ) { p1[i]++; }

		// if the current value is greater than the target,
		// increase it by one (or two if it's still greater).
		if( p1[i] > p2[i] ) {
			p1[i]--;
		}
	}
}
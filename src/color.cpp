//
// Created by Yona Appletree on 12/31/19.
//

#include "color.h"
#include "ui.h"
#include "presetPalettes.h"
#include <colorpalettes.h>

CRGBPalette32 staticPalette;
static CRGBPalette32* g_currentPalette = & staticPalette;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Predefinitions

void handleModeChange();
void updatePalette();
double triangle(double input);
void nblendPaletteTowardPalette2( CRGBPalette32& current, CRGBPalette32& target);

void updateRainbow();
void updateSunset();
void updateNature();
void updateFire();
void updateParty();
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
		case PARTY: updateParty(); break;
		case CHANGING: updateChanging(); break;
	}
}

CRGB colorFor(double value) {
	return ColorFromPalette(* g_currentPalette, uint8_t(triangle(value) * 256));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start Functions

void updateRainbow() {
	staticPalette = RainbowColors_p;
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

	if (millis() - lastSwitchMs > uint32_t (1000 + (1 - g_uiState.speed) * 10000)) {
		lastSwitchMs = millis();

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

void updateParty() {
	staticPalette = PartyColors_p;
	g_currentPalette = & staticPalette;
}

void updateChanging() {
	static uint32_t lastSwitchMs = millis();

	static CRGBPalette32 currentPalette( palettes[ random8() % paletteCount ] );
	static CRGBPalette32 targetPalette( palettes[ random8() % paletteCount ] );

	if (millis() - lastSwitchMs > uint32_t (1000 + (1 - g_uiState.speed) * 10000)) {
		lastSwitchMs = millis();
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

double triangle(double input) {
	input = fmod(input, 1.0);

	return input < 0.5
	       ? input / 0.5
	       : 1 - (input - 0.5) / 0.5;
}

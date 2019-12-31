//
// Created by Yona Appletree on 12/30/19.
//

#include "ui.h"
#include <FastLED.h>

void uiSetup() {
	// Initialize the LEDs
	CFastLED::addLeds<WS2812B, UI_LED_PIN, GRB>(g_uiLeds, UI_LED_COUNT);
}

void uiLoop() {
	FastLED.show();
}

//
// Created by Yona Appletree on 12/30/19.
//

#include "renderer.h"
#include "ui.h"

#define CABINET_LED_COUNT 70

extern std::vector<CabinetRing*> g_cabinetRings = {
	// Preview
	new CabinetRing {
		.host = nullptr,
		.cabinets = {
			new CabinetInfo(7, TOP_RIGHT, true, 1),
			new CabinetInfo(7, TOP_LEFT, true, 2)
		}
	},

	// North Cabinets (8)
	new CabinetRing {
		.host = "192.168.1.10",
		.cabinets = {
			new CabinetInfo(CABINET_LED_COUNT, TOP_RIGHT, true, 1),
			new CabinetInfo(CABINET_LED_COUNT, TOP_LEFT, true, 2),
			new CabinetInfo(CABINET_LED_COUNT, TOP_RIGHT, true, 3),
			new CabinetInfo(CABINET_LED_COUNT, TOP_LEFT, true, 4),
			new CabinetInfo(CABINET_LED_COUNT, TOP_RIGHT, true, 5),
			new CabinetInfo(CABINET_LED_COUNT, TOP_LEFT, true, 6),
			new CabinetInfo(CABINET_LED_COUNT, TOP_RIGHT, true, 7),
			new CabinetInfo(CABINET_LED_COUNT, TOP_LEFT, true, 8),
		}
	},

	// South Cabinets (4)
	new CabinetRing {
		.host = "192.168.1.201",
		.cabinets = {
			new CabinetInfo(CABINET_LED_COUNT, TOP_RIGHT, true, 1),
			new CabinetInfo(CABINET_LED_COUNT, TOP_LEFT, true, 2),
			new CabinetInfo(CABINET_LED_COUNT, TOP_RIGHT, true, 3),
			new CabinetInfo(CABINET_LED_COUNT, TOP_LEFT, true, 4),
		}
	},
};


void rendererSetup() {
	Serial.println("Starting Renderer...");

	for (auto ring : g_cabinetRings) {
		ring->begin();
	}
}

void rendererLoop() {
	auto pVisualizationProgram = g_visualizationPrograms[g_uiState.programMode % g_visualizationPrograms.size()];
	auto pVisualizationEffect = g_visualizationEffects[g_uiState.effectMode % g_visualizationEffects.size()];

	static auto lastTime = g_uiState.time;
	auto deltaTime = g_uiState.time - lastTime;
	lastTime = g_uiState.time;

	for (auto ring : g_cabinetRings) {
		pVisualizationProgram->applyToRing(*ring, deltaTime);
		pVisualizationEffect->applyToRing(*ring, deltaTime);
		ring->swapBuffers();
	}
}

void rendererSend() {
	for (auto ring : g_cabinetRings) {
		ring->send();
	}
}

CabinetInfo::CabinetInfo(int ledCount, CabinetCorner startCorner, bool clockwise, int universe) {
	this->ledCount = ledCount;
	this->startCorner = startCorner;
	this->clockwise = clockwise;
	this->universe = universe;
	this->buffer = new CRGB[ledCount];
	this->buffer2 = new CRGB[ledCount];
}

CabinetInfo::~CabinetInfo() {
	delete buffer;
	delete buffer2;
}

CabinetSide CabinetInfo::startSide() const {
	switch (startCorner) {
		case TOP_LEFT:
			return clockwise
			       ? TOP
			       : LEFT;

		case TOP_RIGHT:
			return clockwise
			       ? RIGHT
			       : TOP;

		case BOTTOM_RIGHT:
			return clockwise
			       ? BOTTOM
			       : RIGHT;

		case BOTTOM_LEFT:
			return clockwise
			       ? LEFT
			       : BOTTOM;
	}
}

CabinetLedPos CabinetInfo::ledPos(int ledIndex) const {
	ledIndex = ledIndex % ledCount;

	int ledsPerSide = ledCount / 4;

	auto side = static_cast<CabinetSide>(
		(startSide() + (ledIndex / ledsPerSide) * (clockwise ? 1 : -1)) % 4
	);

	auto sideFraction = double(clockwise
	                           ? ledIndex % ledsPerSide
	                           : ledsPerSide - 1 - (ledIndex % ledsPerSide)) / ledsPerSide;

	switch (side) {
		case TOP:    return CabinetLedPos { .x = sideFraction, .y = -1 };
		case RIGHT:  return CabinetLedPos { .x = 1,            .y = 1 - sideFraction };
		case BOTTOM: return CabinetLedPos { .x = -1,           .y = sideFraction };
		case LEFT:   return CabinetLedPos { .x = -1,           .y = 1 - sideFraction };
	}
}

void CabinetInfo::fill(CRGB color) const {
	for (int i=0; i<ledCount; i++) {
		buffer[i] = color;
	}
}

void CabinetInfo::swapBuffers() {
	CRGB* temp = buffer;
	buffer = buffer2;
	buffer2 = temp;
}

double CabinetRing::cabinetAngle(int cabinet) {
	return TWO_PI * (double) cabinet / cabinets.size();
}

CabinetRingLedPos CabinetRing::ledPosInRing(int cabinetIndex, int ledIndex) const {
	auto ledPos = cabinets[cabinetIndex]->ledPos(ledIndex);

	// [-.5, .5] value for the x position
	auto ledXFrac = ledPos.x / 2;

	return CabinetRingLedPos {
		.angle = TWO_PI * (double(cabinetIndex) + ledXFrac) / cabinets.size(),
		.z = ledPos.y
	};
}

void CabinetRing::begin() {
	if (host != nullptr) {
		Serial.printf("\tConnecting to %s\n", host);
		sender.begin(host);
	}
}

void CabinetRing::send() {
	if (host == nullptr) {
		return;
	}

	uint8_t brightness = dim8_video(255 * (g_uiState.brightness));

	int maxLedCount = 0;
	for (auto cab : cabinets) {
		maxLedCount = std::max(maxLedCount, cab->ledCount);
	}

	auto channelCount = maxLedCount * 3;

	auto * tempBuffer = static_cast<uint8_t *>(malloc(channelCount));

	for (int cabinetIndex=0; cabinetIndex<cabinets.size(); cabinetIndex++) {
		auto cabinet = cabinets[cabinetIndex];

		memcpy(tempBuffer, (uint8_t *) cabinet->buffer2, channelCount);

		for (int i=0; i<channelCount; i++) {
			tempBuffer[i] = scale8(tempBuffer[i], tempBuffer[i]);
			tempBuffer[i] = scale8_video(tempBuffer[i], brightness);
		}

		sender.set(
			cabinet->universe - 1,
			(uint8_t *) tempBuffer,
			channelCount
		);

		sender.send();
	}

	free(tempBuffer);
}

void CabinetRing::swapBuffers() {
	for (auto cab : cabinets) {
		cab->swapBuffers();
	}
}

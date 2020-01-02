//
// Created by Yona Appletree on 12/30/19.
//

#include "renderer.h"
#include "ui.h"

static std::vector<CabinetRing> cabinetRings = {
	CabinetRing {
		.host = "192.168.1.10",
		.cabinets = {
			CabinetInfo(70, TOP_RIGHT, true, 1),
			CabinetInfo(70, TOP_LEFT, true, 2),
			CabinetInfo(70, TOP_RIGHT, true, 3),
			CabinetInfo(70, TOP_LEFT, true, 4),
			CabinetInfo(70, TOP_RIGHT, true, 5),
			CabinetInfo(70, TOP_LEFT, true, 6),
			CabinetInfo(70, TOP_RIGHT, true, 7),
			CabinetInfo(70, TOP_LEFT, true, 8),
		}
	},

	CabinetRing {
		.host = "192.168.1.11",
		.cabinets = {
			CabinetInfo(70, TOP_RIGHT, true, 1),
			CabinetInfo(70, TOP_LEFT, true, 2),
			CabinetInfo(70, TOP_RIGHT, true, 3),
			CabinetInfo(70, TOP_LEFT, true, 4),
		}
	},
};


void rendererSetup() {

}

void rendererLoop() {
	auto fun = functionForMode(g_uiState.programMode);

	for (CabinetRing& ring : cabinetRings) {
		ring.computeColors(
			fun,
			millis(),
			g_uiState.speed
		);
	}

//	Serial.printf(
//		"%d %d %d \n",
//		cabinetRings[0].cabinets[0].buffer[0].r,
//		cabinetRings[0].cabinets[0].buffer[0].g,
//		cabinetRings[0].cabinets[0].buffer[0].b
//	);
}


CabinetInfo::CabinetInfo(int ledCount, CabinetCorner startCorner, bool clockwise, int universe) {
	this->ledCount = ledCount;
	this->startCorner = startCorner;
	this->clockwise = clockwise;
	this->universe = universe;
	this->buffer = new CRGB[ledCount];
}

CabinetInfo::CabinetInfo(const CabinetInfo &other) : CabinetInfo(
	other.ledCount,
	other.startCorner,
	other.clockwise,
	other.universe
) {
	for (int i=0; i<ledCount; i++) {
		buffer[i] = other.buffer[i];
	}
}

CabinetInfo::~CabinetInfo() {
	delete buffer;
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

double CabinetRing::cabinetAngle(int cabinet) {
	return TWO_PI * (double) cabinet / cabinets.size();
}

CabinetRingLedPos CabinetRing::ledPosInRing(int cabinetIndex, int ledIndex) const {
	auto ledPos = cabinets[cabinetIndex].ledPos(ledIndex);

	// [-.5, .5] value for the x position
	auto ledXFrac = ledPos.x / 2;

	return CabinetRingLedPos {
		.angle = TWO_PI * (double(cabinetIndex) + ledXFrac) / cabinets.size(),
		.z = ledPos.y
	};
}


void CabinetRing::computeColors(
	const TLedColorFunction& ledColorFunction,
	uint64_t millis,
	double speed
) {
	for (int cabinetIndex=0; cabinetIndex<cabinets.size(); cabinetIndex++) {
		const CabinetInfo& cabinet = cabinets[cabinetIndex];

		for (int ledIndex=0; ledIndex<cabinet.ledCount; ledIndex++) {
			cabinet.buffer[ledIndex] = ledColorFunction({
				.ring = *this,
				.cabinetIndex = cabinetIndex,
				.ledIndex = ledIndex,
				.millis = millis,
				.speed = speed,
			});
		}
	}
}

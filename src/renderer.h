//
// Created by Yona Appletree on 12/30/19.
//

#ifndef ANDYMANCABINETSESP32_RENDERER_H
#define ANDYMANCABINETSESP32_RENDERER_H

#include <FastLED.h>
#include <functional>
#include <vector>
#include "color.h"

void rendererSetup();
void rendererLoop();

enum CabinetCorner {
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_RIGHT,
	BOTTOM_LEFT,
};


enum CabinetSide {
	TOP,
	RIGHT,
	BOTTOM,
	LEFT,
};

struct CabinetRingLedPos {
	// Angle from center of ring
	double angle;

	// Position from midline
	double z;
};

struct CabinetLedPos {
	double x;
	double y;
};

struct CabinetInfo;
struct CabinetRing;

struct TLedColorFunctionProps {
	TColorFunction colorFunction;
	const CabinetRing& ring;
	int cabinetIndex;
	int ledIndex;

	uint64_t millis;
	double speed;
};

typedef std::function<CRGB(const TLedColorFunctionProps&)> TLedColorFunction;

struct CabinetInfo {
	int ledCount;
	CabinetCorner startCorner;
	bool clockwise;
	int universe;

	CRGB* buffer;

	CabinetInfo(
		int ledCount,
		CabinetCorner startCorner,
		bool clockwise,
		int universe
	);

	CabinetInfo(
		const CabinetInfo &other
	);

	~CabinetInfo();

	CabinetSide startSide() const;

	CabinetLedPos ledPos(int ledIndex) const;

	double ledAngle(int ledIndex) {
		auto pos = ledPos(ledIndex);
		return atan2(pos.y, pos.x);
	}
};

struct CabinetRing {
	String host;
	std::vector<CabinetInfo> cabinets;

	double cabinetAngle(int cabinet);

	CabinetRingLedPos ledPosInRing(
		int cabinetIndex,
		int ledIndex
	) const;

	void computeColors(
		const TLedColorFunction& ledColorFunction,
		const TColorFunction& colorFunction,
		uint64_t millis,
		double speed
	);
};

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


#endif //ANDYMANCABINETSESP32_RENDERER_H

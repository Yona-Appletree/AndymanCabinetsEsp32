//
// Created by Yona Appletree on 12/30/19.
//

#ifndef ANDYMANCABINETSESP32_RENDERER_H
#define ANDYMANCABINETSESP32_RENDERER_H

#include <FastLED.h>
#include <functional>
#include <vector>
#include <Artnet.h>
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
	const CabinetRing& ring;
	int cabinetIndex;
	int ledIndex;

	uint64_t millis;
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

	ArtnetSender sender;

	double cabinetAngle(int cabinet);

	void begin();

	CabinetRingLedPos ledPosInRing(
		int cabinetIndex,
		int ledIndex
	) const;

	void computeColors(
		const TLedColorFunction& ledColorFunction,
		uint64_t millis
	);

	void send();
};

#endif //ANDYMANCABINETSESP32_RENDERER_H

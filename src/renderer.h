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
void rendererSend();

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

struct CabinetInfo {
	CabinetInfo(const CabinetInfo&) = delete;

	int ledCount;
	CabinetCorner startCorner;
	bool clockwise;
	int universe;

	CRGB* buffer;
	CRGB* buffer2;

	CabinetInfo(
		int ledCount,
		CabinetCorner startCorner,
		bool clockwise,
		int universe
	);

	~CabinetInfo();

	CabinetSide startSide() const;

	CabinetLedPos ledPos(int ledIndex) const;

	double ledAngle(int ledIndex) {
		auto pos = ledPos(ledIndex);
		return atan2(pos.y, pos.x);
	}

	void fill(CRGB color) const;

	void swapBuffers();
};

struct CabinetRing {
	CabinetRing(const CabinetRing&) = delete;

	String host;
	std::vector<CabinetInfo*> cabinets;

	ArtnetSender sender;

	double cabinetAngle(int cabinet);

	void begin();

	CabinetRingLedPos ledPosInRing(
		int cabinetIndex,
		int ledIndex
	) const;

	void send();
};

#endif //ANDYMANCABINETSESP32_RENDERER_H

//
// Created by Yona Appletree on 12/31/19.
//

#include "renderer.h"
#include <vector>

#ifndef ANDYMANCABINETSESP32_MODE_H
#define ANDYMANCABINETSESP32_MODE_H

#endif //ANDYMANCABINETSESP32_MODE_H

class Visualization {
public:

	virtual void applyToRing(const CabinetRing& ring) = 0;
	virtual void applyToPreview(CRGB* buffer, int count) = 0;

	double time3s();
	double time10s();



	void sectionedPreview(
		CRGB *buffer,
		int count,
		std::function<CRGB(double sectionFrac, double ledFrac)> pLedFn
	);
};

extern std::vector<Visualization*> g_visualizationPrograms;

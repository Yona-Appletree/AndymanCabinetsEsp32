//
// Created by Yona Appletree on 12/31/19.
//

#include "renderer.h"
#include <vector>

#ifndef ANDYMANCABINETSESP32_MODE_H
#define ANDYMANCABINETSESP32_MODE_H

#endif //ANDYMANCABINETSESP32_MODE_H

class VisualCommon {
public:
	double timeNormal();
	double timeSlow();

	virtual void applyToRing(const CabinetRing &ring, const uint64_t deltaTime) = 0;
	virtual const char* name() = 0;
};

class VisualizationProgram : public VisualCommon {

};


class VisualizationEffect : public VisualCommon {

};

extern std::vector<VisualizationProgram*> g_visualizationPrograms;
extern std::vector<VisualizationEffect*> g_visualizationEffects;

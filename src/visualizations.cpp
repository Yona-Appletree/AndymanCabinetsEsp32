//
// Created by Yona Appletree on 12/31/19.
//

#include "ui.h"
#include "util.h"
#include <FastLED.h>
#include <noise.h>
#include <map>








////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Programs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Each cabinet fades through the palette, offset by a bit
 */
class VisualizationEachCabGradient : public VisualizationProgram {
public:
	const char *name() override {
		return "Each Cabinet Gradient";
	}

	double cabGradientMultiplier;
	double ledGradientMultiplier;

	VisualizationEachCabGradient(
		double cabGradientMultiplier,
		double ledGradientMultiplier
	) :
		cabGradientMultiplier(cabGradientMultiplier),
		ledGradientMultiplier(ledGradientMultiplier)
	{}

	void applyToRing(const CabinetRing &ring, const uint64_t deltaTime) override {
		double time = timeNormal();

		for (int cabIndex = 0; cabIndex < ring.cabinets.size(); cabIndex++) {
			auto cab = ring.cabinets[cabIndex];
			auto cabFrac = (double(cabIndex) / ring.cabinets.size()) * cabGradientMultiplier;

			for (int ledIndex = 0; ledIndex < cab->ledCount; ledIndex++) {
				auto ledFrac = triangle(double(ledIndex) / cab->ledCount) * ledGradientMultiplier;

				cab->buffer[ledIndex] = colorFor(
					time + ledFrac + cabFrac,
					std::min(0.17, (1.0 / cab->ledCount) / 2)
				);
			}
		}
	}
};

/**
 * Each cabinet displays data from perlin noise
 */
class VisualizationPerlinNoise : public VisualizationProgram {
public:
	const char *name() override {
		return "Each Cabinet Perlin Noise";
	}

	void applyToRing(const CabinetRing &ring, const uint64_t deltaTime) override {
		auto time = timeSlow();

		for (int cabIndex = 0; cabIndex < ring.cabinets.size(); cabIndex++) {
			auto cab = ring.cabinets[cabIndex];
			auto cabFrac = double(cabIndex) / ring.cabinets.size();

			for (int ledIndex = 0; ledIndex < cab->ledCount; ledIndex++) {
				auto ledFrac = double(ledIndex) / cab->ledCount;

				cab->buffer[ledIndex] = colorFor(
					cos16(
						inoise16(
							cabFrac * 256 * 256,
							ledFrac * 128 * 256,
							double(g_uiState.time) * 24
						) + (time * 65536)
					) / 65536.0
				);
			}
		}
	}
};

extern std::vector<VisualizationProgram *> g_visualizationPrograms = {
	new VisualizationEachCabGradient(.05, .01),
	new VisualizationEachCabGradient(1.5, .04),
	new VisualizationEachCabGradient(.3, .05),
	new VisualizationEachCabGradient(.5, .5),
	new VisualizationEachCabGradient(1.2, .5),
	new VisualizationEachCabGradient(1.2, 1.2),
	new VisualizationPerlinNoise()
};








////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Effects
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * Each cabinet fades in an out in a "sparking" pattern
 */
class VisualizationEffectNop : public VisualizationEffect {
public:
	const char *name() override {
		return "No Effect";
	}

	void applyToRing(const CabinetRing &ring, const uint64_t deltaTime) override {}
};

/**
 * Each cabinet fades in an out in a "sparking" pattern
 */
class VisualizationEffectTwinkleEach : public VisualizationEffect {
public:
	const char *name() override {
		return "Twinkle Each Cabinet";
	}

	std::map<CabinetInfo*, double> sparkMap;
	uint64_t lastSparkMs = 0;

	void applyToRing(const CabinetRing &ring, const uint64_t deltaTime) override {
		double colorTime = timeSlow();

		int sparkCabIndex = -1;
		if (! sparkMap.empty() && g_uiState.time - lastSparkMs > random(50, 100)) {
			lastSparkMs = g_uiState.time;

			sparkCabIndex = random(ring.cabinets.size());
		}

		for (int cabIndex = 0; cabIndex < ring.cabinets.size(); cabIndex++) {
			auto cab = ring.cabinets[cabIndex];
			auto cabFrac = double(cabIndex) / ring.cabinets.size();

			auto sparkValue = sparkMap[cab];

			if (cabIndex == sparkCabIndex) {
				sparkValue = sparkValue + std::min(50 + (double)random(100), 255 - sparkValue);
			} else {
				sparkValue = std::max(0.0, sparkValue - deltaTime / 10.0);
			}

			sparkMap[cab] = sparkValue;

			for (int ledIndex = 0; ledIndex < cab->ledCount; ledIndex++) {
				cab->buffer[ledIndex] = cab->buffer[ledIndex].nscale8_video(sparkValue);
			}
		}
	}
};

extern std::vector<VisualizationEffect *> g_visualizationEffects = {
	new VisualizationEffectNop(),
	new VisualizationEffectTwinkleEach()
};










////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double VisualCommon::timeNormal() {
	return double(g_uiState.time % 3000) / 3000;
}

double VisualCommon::timeSlow() {
	return double(g_uiState.time % 5000) / 5000;
}


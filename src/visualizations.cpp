//
// Created by Yona Appletree on 12/31/19.
//

#include "ui.h"
#include <FastLED.h>
#include <noise.h>
#include <map>








////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Programs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * All cabinets the same color.
 */
class VisualizationAllSameColor : public VisualizationProgram {
public:
	const char *name() override {
		return "All Same Color";
	}

	void applyToRing(const CabinetRing &ring, const uint64_t deltaTime) override {
		double time = time3s();
		auto color = colorFor(time);

		for (auto cab : ring.cabinets) {
			cab->fill(color);
		}
	}
};

/**
 * Each cabinet one single color.
 */
class VisualizationEachCabSameColor : public VisualizationProgram {
public:
	const char *name() override {
		return "Each Cabinet Same Color";
	}

	void applyToRing(const CabinetRing &ring, const uint64_t deltaTime) override {
		double time = time3s();

		for (int cabIndex = 0; cabIndex < ring.cabinets.size(); cabIndex++) {
			auto cab = ring.cabinets[cabIndex];
			auto cabFrac = double(cabIndex) / ring.cabinets.size();

			for (int ledIndex = 0; ledIndex < cab->ledCount; ledIndex++) {
				cab->buffer[ledIndex] = colorFor(
					time + cabFrac
				);
			}
		}
	}
};

/**
 * Each cabinet fades through the palette, offset by a bit
 */
class VisualizationEachCabGradient : public VisualizationProgram {
public:
	const char *name() override {
		return "Each Cabinet Gradient";
	}

	double zoomMultiplier;

	explicit VisualizationEachCabGradient(
		double zoomMultiplier
	) {
		this->zoomMultiplier = zoomMultiplier;
	}

	void applyToRing(const CabinetRing &ring, const uint64_t deltaTime) override {
		double time = time3s();

		for (int cabIndex = 0; cabIndex < ring.cabinets.size(); cabIndex++) {
			auto cab = ring.cabinets[cabIndex];
			auto cabFrac = double(cabIndex) / ring.cabinets.size();

			for (int ledIndex = 0; ledIndex < cab->ledCount; ledIndex++) {
				auto ledFrac = (double(ledIndex) / cab->ledCount) * zoomMultiplier;

				cab->buffer[ledIndex] = colorFor(
					time + ledFrac + cabFrac
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
		auto time = time10s();

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
	new VisualizationAllSameColor(),
	new VisualizationEachCabSameColor(),
	new VisualizationEachCabGradient(1),
	new VisualizationEachCabGradient(.3),
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
		double colorTime = time10s();

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

double VisualCommon::time3s() {
	return double(g_uiState.time % 3000) / 3000;
}

double VisualCommon::time10s() {
	return double(g_uiState.time % 10000) / 10000;
}


//
// Created by Yona Appletree on 12/31/19.
//

#include "ui.h"
#include <FastLED.h>
#include <noise.h>

double Visualization::time3s() {
	return double(g_uiState.time % 3000) / 3000;
}

double Visualization::time10s() {
	return double(g_uiState.time % 10000) / 10000;
}

void Visualization::sectionedPreview(
	CRGB *buffer,
	int count,
	std::function<CRGB(double sectionFrac, double ledFrac)> pLedFn
) {
	auto overallOffset = 1 + g_uiState.programMode;

	const auto sectionCount = 2;
	const auto sectionLedCount = count / sectionCount;

	for (int sectionIndex = 0; sectionIndex < sectionCount; sectionIndex++) {
		const auto ledOffset = sectionIndex * sectionLedCount;
		const auto sectionFrac = double(sectionIndex) / sectionCount;
		const auto thisSectionLedCount = sectionIndex == sectionCount - 1
			? count - ledOffset
			: sectionLedCount;

		for (int ledIndex = 0; ledIndex < thisSectionLedCount - 1; ledIndex++) {
			auto ledFrac = double(ledIndex) / (thisSectionLedCount - 1);

			buffer[(overallOffset + ledOffset + ledIndex) % count] = pLedFn(
				sectionFrac,
				ledFrac
			);
		}

		buffer[(overallOffset + ledOffset + thisSectionLedCount - 1) % count] = CRGB::Black;
	}
}

/**
 * All cabinets the same color.
 */
class AllSolid : public Visualization {
	void applyToRing(const CabinetRing &ring) override {
		double time = time3s();
		auto color = colorFor(time);

		for (auto cab : ring.cabinets) {
			cab->fill(color);
		}
	}

	void applyToPreview(CRGB *buffer, int count) override {
		double time = time3s();
		auto color = colorFor(time);

		sectionedPreview(
			buffer,
			count,
			[time, color](double sectionFrac, double ledFrac) {
				return color;
			}
		);
	}
};

/**
 * Each cabinet one single color.
 */
class FadeSingle : public Visualization {
	void applyToRing(const CabinetRing &ring) override {
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

	void applyToPreview(CRGB *buffer, int count) override {
		double time = time3s();

		sectionedPreview(
			buffer,
			count,
			[time](double sectionFrac, double ledFrac) {
				return colorFor(
					time + sectionFrac
				);
			}
		);
	}
};

/**
 * Each cabinet fades through the palette, offset by a bit
 */
class FadeEach : public Visualization {
public:
	double zoomMultiplier;

	FadeEach(
		double zoomMultiplier
	) {
		this->zoomMultiplier = zoomMultiplier;
	}

	void applyToRing(const CabinetRing &ring) override {
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

	void applyToPreview(CRGB *buffer, int count) override {
		double time = time3s();

		sectionedPreview(
			buffer,
			count,
			[time, this](double sectionFrac, double ledFrac) {
				return colorFor(
					time + sectionFrac + (ledFrac * this->zoomMultiplier / 4)
				);
			}
		);
	}
};

/**
 * Each cabinet displays data from perlin noise
 */
class Noise : public Visualization {
	void applyToRing(const CabinetRing &ring) override {
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

	void applyToPreview(CRGB *buffer, int count) override {
		auto time = time10s();

		sectionedPreview(
			buffer,
			count,
			[time](double sectionFrac, double ledFrac) {
				return colorFor(
					cos16(
						inoise16(
							sectionFrac * 128 * 256,
							ledFrac * 64 * 256,
							double(g_uiState.time) * 24
						) + (time * 65536)
					) / 65536.0
				);
			}
		);
	}
};


extern std::vector<Visualization *> g_visualizationPrograms = {
	new AllSolid(),
	new FadeSingle(),
	new FadeEach(1),
	new FadeEach(.3),
	new Noise()
};
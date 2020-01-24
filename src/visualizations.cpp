//
// Created by Yona Appletree on 12/31/19.
//

#include "ui.h"
#include <FastLED.h>
#include <noise.h>
#include <map>
#include <iterator>

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
	sectionedPreviewIndexed(
		buffer,
		count,
		[pLedFn](
			int sectionIndex,
			int sectionCount,
			int ledIndex,
			int ledCount
		) {
			return pLedFn(
				double(sectionIndex) / sectionCount,
				double(ledIndex) / ledCount
			);
		}
	);
}


void Visualization::sectionedPreviewIndexed(
	CRGB *buffer,
	int count,
	std::function<CRGB(
		int sectionIndex,
		int sectionCount,
		int ledIndex,
		int ledCount
	)> pLedFn
) {
	auto overallOffset = 1 + g_uiState.programMode;

	const auto sectionCount = 2;
	const auto sectionLedCount = count / sectionCount;

	for (int sectionIndex = 0; sectionIndex < sectionCount; sectionIndex++) {
		const auto ledOffset = sectionIndex * sectionLedCount;
		const auto thisSectionLedCount = sectionIndex == sectionCount - 1
		                                 ? count - ledOffset
		                                 : sectionLedCount;

		for (int ledIndex = 0; ledIndex < thisSectionLedCount - 1; ledIndex++) {
			buffer[(overallOffset + ledOffset + ledIndex) % count] = pLedFn(
				sectionIndex,
				sectionCount,
				ledIndex,
				thisSectionLedCount
			);
		}

		buffer[(overallOffset + ledOffset + thisSectionLedCount - 1) % count] = CRGB::Black;
	}
}

/**
 * All cabinets the same color.
 */
class AllSolid : public Visualization {
	void applyToRing(const CabinetRing &ring, const uint64_t deltaTime) override {
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

template <template<class,class,class...> class C, typename K, typename V, typename... Args>
V mapValueOrDefault(const C<K,V,Args...>& m, K const& key, const V & defval)
{
	typename C<K,V,Args...>::const_iterator it = m.find( key );
	if (it == m.end())
		return defval;
	return it->second;
}

/**
 * Each cabinet fades through the palette, offset by a bit
 */
class TwinkleEach : public Visualization {
public:
	double zoomMultiplier;

	std::map<CabinetInfo*, double> sparkMap;
	uint64_t lastSparkMs = 0;

	TwinkleEach(
		double zoomMultiplier
	) {
		this->zoomMultiplier = zoomMultiplier;
	}

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
				auto ledFrac = (double(ledIndex) / cab->ledCount) * zoomMultiplier;

				cab->buffer[ledIndex] = colorFor(colorTime + ledFrac + cabFrac).nscale8_video(sparkValue);
			}
		}
	}

	void applyToPreview(CRGB *buffer, int count) override {
		double time = time3s();

		sectionedPreviewIndexed(
			buffer,
			count,
			[time, this](
				int sectionIndex,
				int sectionCount,
				int ledIndex,
				int ledCount
			) {
				double ledFrac = double(ledIndex) / ledCount * (zoomMultiplier / 4);
				double sectionFrac = double(sectionIndex) / sectionCount;

				auto sparkEntry = sparkMap.begin();
				std::advance(sparkEntry, std::min(sectionIndex, (int) sparkMap.size()));

				uint8_t sparkValue;
				if (sparkEntry == sparkMap.end()) {
					sparkValue = 0;
				} else {
					sparkValue = sparkEntry->second;
				}

				return colorFor(time + ledFrac + sectionFrac).nscale8_video(sparkValue);
			}
		);
	}
};

/**
 * Each cabinet displays data from perlin noise
 */
class Noise : public Visualization {
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
	new Noise(),
	new TwinkleEach(.3)
};
#include "network.h"
#include "ui.h"

#include "renderer.h"

void setup()
{
	Serial.begin(115200);

	uiSetup();
	networkSetup();
	rendererSetup();
}


void loop()
{
	auto start = millis();

	uiLoop();
	networkLoop();
	rendererLoop();

	auto duration = millis() - start;
	Serial.printf("Duration: %dms\n\n", (int) duration);

	if (duration < 30) {
		delay(30 - duration);
	}
}
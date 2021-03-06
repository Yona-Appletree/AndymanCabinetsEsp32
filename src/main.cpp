#include "network.h"
#include "ui.h"

#include "renderer.h"

void core2loop(void * data);
TaskHandle_t renderTask;

volatile bool rendererStarted = false;

void setup()
{
	Serial.begin(115200);

	uiSetup();
	colorSetup();
	networkSetup();

	xTaskCreatePinnedToCore(
		core2loop, /* Function to implement the task */
		"Render", /* Name of the task */
		10000,  /* Stack size in words */
		NULL,  /* Task input parameter */
		0,  /* Priority of the task */
		&renderTask,  /* Task handle. */
		0  /* Core where the task should run */
	);
}


void loop()
{
	auto start = millis();

	uiLoop();
	colorLoop();
	networkLoop();

	if (rendererStarted) {
		rendererSend();
	}

	auto duration = millis() - start;

	//Serial.printf("main: %dms\n", (int) duration);

	if (duration < 30) {
		FastLED.delay(30 - duration);
	}
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void core2loop(void * data) {
	// Wait for network
	while (! g_ethConnected) {
		delay(100);
	}

	rendererSetup();

	rendererStarted = true;

	while (true) {
		auto start = millis();

		rendererLoop();

		auto duration = millis() - start;

		//Serial.printf("render ms: %d\n", (int) duration);

		if (duration < 30) {
			delay(30 - duration);
		}
	}
}
#pragma clang diagnostic pop
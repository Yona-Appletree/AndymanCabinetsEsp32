#include "network.h"
#include "ui.h"

void setup()
{
	Serial.begin(115200);

	uiSetup();
	networkSetup();
}


void loop()
{
	uiLoop();
	networkLoop();
}
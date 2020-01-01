//
// Created by Yona Appletree on 12/30/19.
//

#define ARDUHAL_LOG_LEVEL ARDUHAL_LOG_LEVEL_INFO

#include "network.h"
#include <ETH.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>

#define HOSTNAME "andycabinets"

void handleNetworkEvent(WiFiEvent_t event);
static bool g_ethConnected = false;

// Web server
WebServer server(80);

// HTTP handlers
void handleRoot() {
	server.send(200, "text/plain", "Hello from Andycabinets\n");
}

void handleNotFound() {
	server.send(404, "text/plain", String("No ") + server.uri() + " here!\n");
}

void networkSetup(){
	// Listen to events
	WiFi.onEvent(handleNetworkEvent);

	// Start the ethernet
	ETH.begin();

	// Bind HTTP handler
	server.on("/", handleRoot);
	server.onNotFound(handleNotFound);

	// Start the Ethernet web server
	server.begin();

	// Setup OTA updates
	ArduinoOTA
		.setMdnsEnabled(true)
		.setHostname(HOSTNAME)
		.onStart([]() {
			String type = (ArduinoOTA.getCommand() == U_FLASH)
				? "sketch"
				: "filesystem";

			// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
			Serial.println("OTA: Start updating " + type);
		})
		.onEnd([]() {
			Serial.println("\nOTA: End");
		})
		.onProgress([](unsigned int progress, unsigned int total) {
			Serial.printf("OTA: Progress: %u%%\r", (progress / (total / 100)));
		})
		.onError([](ota_error_t error) {
			Serial.printf("OTA: Error[%u]: ", error);
			if (error == OTA_AUTH_ERROR) Serial.println("OTA: Auth Failed");
			else if (error == OTA_BEGIN_ERROR) Serial.println("OTA: Begin Failed");
			else if (error == OTA_CONNECT_ERROR) Serial.println("OTA: Connect Failed");
			else if (error == OTA_RECEIVE_ERROR) Serial.println("OTA: Receive Failed");
			else if (error == OTA_END_ERROR) Serial.println("OTA: End Failed");
		})
		.begin();

	// Add service to MDNS-SD
	MDNS.addService("http", "tcp", 80);
}

void networkLoop(){
	server.handleClient();
	ArduinoOTA.handle();
}

void handleNetworkEvent(WiFiEvent_t event) {
	switch (event) {
		case SYSTEM_EVENT_ETH_START:
			Serial.println("ETH Started");
			//set eth hostname here
			ETH.setHostname(HOSTNAME);
			break;

		case SYSTEM_EVENT_ETH_CONNECTED:
			Serial.println("ETH Connected");
			break;

		case SYSTEM_EVENT_ETH_GOT_IP:
			Serial.print("ETH MAC: ");
			Serial.print(ETH.macAddress());
			Serial.print(", IPv4: ");
			Serial.print(ETH.localIP());
			if (ETH.fullDuplex()) {
				Serial.print(", FULL_DUPLEX");
			}
			Serial.print(", ");
			Serial.print(ETH.linkSpeed());
			Serial.println("Mbps");
			g_ethConnected = true;

			break;

		case SYSTEM_EVENT_ETH_DISCONNECTED:
			Serial.println("ETH Disconnected");
			g_ethConnected = false;
			break;

		case SYSTEM_EVENT_ETH_STOP:
			Serial.println("ETH Stopped");
			g_ethConnected = false;
			break;

		default:
			break;
	}
}

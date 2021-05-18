#include <ETH.h>
#include <WebServer.h>
#include "JsAr.h"

#define ETH_PHY_MDC 23
#define ETH_PHY_MDIO 18
#define ETH_CLK_MODE ETH_CLOCK_GPIO0_IN

IPAddress local_IP(10, 10, 11, 2);  //Your IP
IPAddress gateway(10, 10, 11, 1);   //Gateway IP
IPAddress subnet(255, 255, 255, 0); //Net mask
WebServer server(80);

int someData = 1;

void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP-JS-AR! " + String(someData++));
}

void setup() {
  Serial.begin(115200);
  JsAr.begin();
  JsAr.enableEthernet();

  ETH.begin();
  ETH.config(local_IP, gateway, subnet);
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}

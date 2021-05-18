#define ETH_PHY_MDC 23
#define ETH_PHY_MDIO 18
#define ETH_CLK_MODE ETH_CLOCK_GPIO0_IN
#include <ETH.h>
#include <WebServer.h>
#include "JsAr.h"


// Set your Static IP address
IPAddress local_IP(10, 10, 11, 2);
// Set your Gateway IP address
IPAddress gateway(10, 10, 11, 1);

IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

int global_var = 1;

void handleRoot() {
//  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp32! " + String(global_var++));
//  digitalWrite(led, 0);
}

void handleNotFound() {
//  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  //digitalWrite(led, 0);
}

static bool eth_connected = false;

void WiFiEvent(WiFiEvent_t event)
{
  switch (event) {
    case SYSTEM_EVENT_ETH_START:
      Serial.println("ETH Started");
      //set eth hostname here
      ETH.setHostname("esp32-ethernet");
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
      eth_connected = true;
      break;
    case SYSTEM_EVENT_ETH_DISCONNECTED:
      Serial.println("ETH Disconnected");
      eth_connected = false;
      break;
    case SYSTEM_EVENT_ETH_STOP:
      Serial.println("ETH Stopped");
      eth_connected = false;
      break;
    default:
      break;
  }
}

void testClient(const char * host, uint16_t port)
{
  Serial.print("\nconnecting to ");
  Serial.println(host);

  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }
  client.printf("GET / HTTP/1.1\r\nHost: %s\r\n\r\n", host);
  while (client.connected() && !client.available());
  while (client.available()) {
    Serial.write(client.read());
  }

  Serial.println("closing connection\n");
  client.stop();
}

void stage(String name, int is_press_key = 0) {
  Serial.println(name);
  while (Serial.read() != '1') {};
}

int pin = 2;

void setup()
{
  Serial.begin(115200);
  JsAr.begin();
  JsAr.enableEthernet();

  WiFi.onEvent(WiFiEvent);
  ETH.begin();
  //ETH.config(local_IP, gateway, subnet);
  //server.on("/", handleRoot);
  //server.on("/inline", []() {
  //  server.send(200, "text/plain", "this works as well");
  //});

  //server.onNotFound(handleNotFound);
  //server.begin();
}

void loop()
{
  if (eth_connected) {
    testClient("google.com", 80);
  }
  delay(1000);
}

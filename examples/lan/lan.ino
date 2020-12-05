#define ETH_PHY_MDC 23
#define ETH_PHY_MDIO 18
#define ETH_CLK_MODE ETH_CLOCK_GPIO0_IN

#include <ETH.h>
#include "DxlMaster.h"
#include "extender.h"
#include <WebServer.h>

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

const uint8_t id = 253;
DynamixelDevice device(id);

void stage(String name, int is_press_key = 0) {
  Serial.println(name);
  while (Serial.read() != '1') {};
}

int pin = 2;

void setup()
{
  JsAr.begin(JsAr_ETHERNET | JsAr_GPIO_PULL_UP | JsAr_SPI_DRV_5V | JsAr_CAN});
  JsAr.ethernet.enable();
  JsAr.ethernet.rst(0);
  Serial.begin(115200);

  JsAr.pinMode(44, JsAr_Extender_OUTPUT)

  while(JsAr.begin() != JsAr_OK)
  {
    Serial.println("Failed to init esp-js-ar board");
    delay(1000);
  }
  Serial.println("Ready!");
  Serial.println("Ready!");
  
  device.write(GPIO_PULL_UP_ENABLE, (uint8_t)1);
  device.write(SPI_MODE, (uint8_t)0);
  device.write(ETHERNET_ENABLE, (uint8_t)1);
  device.write(ETHERNET_RST, (uint8_t)0);

  
  JsAr.spi.mode(JsAr_SPI_MODE_3V3);
  //device.write(D7_MODE, (uint8_t)PinMode_ST_PWM);
  //device.write(D6_MODE, (uint8_t)PinMode_ST_OUTPUT);
  device.write(D6_MODE, (uint8_t)PinMode_ESP_DIVIDER);
  //device.write(D12_MODE, (uint8_t)PinMode_ESP_DIVIDER);
  //device.write(D3_D7_PULL_UP_ENABLE, (uint8_t)1);
  pinMode(pin, OUTPUT);
  return;
  WiFi.onEvent(WiFiEvent);
  ETH.begin();

  ETH.config(local_IP, gateway, subnet);

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
}

void loop()
{
  //server.handleClient();
  //return;
  //device.write(D8_OUTPUT_VAL, 1);
  volatile uint8_t u8;
  //device.read(IR_TX_ENABLE, u8);

  //device.write(IR_RX_ENABLE, (uint8_t)0);

  char cmd = Serial.read();
  switch(cmd)
  {
    case '0': device.write(SPI_MODE, (uint8_t)0); break;
    case '1': device.write(SPI_MODE, (uint8_t)1); break;
    case '2': device.write(SPI_MODE, (uint8_t)2); break;
    case '3': device.write(SPI_MODE, (uint8_t)3); break;
    case '4': device.write(SPI_MODE, (uint8_t)4); break;
    case '5': device.write(MISO_OUTPUT_EN, (uint8_t)0); break;
    case '6': device.write(MISO_OUTPUT_EN, (uint8_t)1); break;
    case '7': device.write(GPIO_PULL_UP_ENABLE, (uint8_t)0); break;
    case '8': device.write(GPIO_PULL_UP_ENABLE, (uint8_t)1); break;
    case '9': device.write(D7_OUTPUT_VAL, (uint16_t)200); break;
    case 'p': device.write(D7_MODE, (uint8_t)PinMode_ST_PWM); break;
    case 'i': device.write(D7_OUTPUT_VAL, (uint16_t)700); break;
  };
  //Serial.println(analogRead(pin));

  device.write(LED, (uint8_t)1);
  digitalWrite(pin, HIGH);
  delay(200);
  //device.write(D6_OUTPUT_VAL, (uint8_t)0);
  device.write(LED, (uint8_t)0);
  digitalWrite(pin, LOW);
  //digitalWrite(pin2, LOW);
  delay(200);
  //Serial.println("Ready!");

  if (eth_connected) {
    testClient("google.com", 80);
  }
  delay(1000);

  //dump_regs();
  //delay(500);
}

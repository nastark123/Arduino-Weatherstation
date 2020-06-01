#include "DHT.h"
#include <WiFiNINA.h>
#include <SPI.h>

WiFiClient client;
DHT11 dht(1);
int status = WL_IDLE_STATUS;
String postData;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  while(status != WL_CONNECTED) {
    Serial.println("Attempting to connect to network...");
    status = WiFi.begin("SKSCR2", "Philmont19T360");
    delay(30000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  dht.read();
//  uint8_t *ptr = dht.getBuff();
//  Serial.println("Buffer:");
//  for(int i = 0; i < 5; i++) {
//    Serial.println(*ptr);
//    ptr++;
//  }
//  Serial.println("End buffer");

  postData = "temp=" + String(dht.getTempF()) + "&humid=" + String(dht.getHumid());

  if (client.connect("192.168.1.12", 80)) {
    client.println("POST /postdata.php HTTP/1.1");
    client.println("Host: 192.168.1.12");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();
    client.print(postData);
  }

  if (client.connected()) {
    client.stop();
  }
  
  Serial.print("Temp (°C): ");
  Serial.println(dht.getTempC());
  Serial.print("Temp (°F): ");
  Serial.println(dht.getTempF());
  Serial.print("Humidity: ");
  Serial.println(dht.getHumid());
  Serial.print("Parity byte: ");
  Serial.println(dht.getParity());

  delay(60000);
}

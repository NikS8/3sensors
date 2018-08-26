#include <DHT.h>        // You have to download DHT22  library
#define DHT1PIN 8             // PIN №8 подключения датчика DTH22
#define DHT1TYPE DHT22 
DHT dht1(DHT1PIN, DHT1TYPE);
int sensorDhtTemp;      // температура от датчика DHT22 в прихожей 
int sensorDhtHum;       // влажность от датчика DHT22

void setup() {
  Serial.begin(9600);
  dht1.begin();
}

void loop() {
    sensorDhtHum = dht1.readHumidity();
    sensorDhtTemp = dht1.readTemperature();

}
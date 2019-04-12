#include <DHT.h>        // You have to download DHT22  library
#define DHT1PIN 8             // PIN №8 подключения датчика DTH22
#define DHT1TYPE DHT22 
DHT dht1(DHT1PIN, DHT1TYPE);
int sensorDhtTemp;      // температура от датчика DHT22 в прихожей 
int sensorDhtHum;       // влажность от датчика DHT22

//  Управление светодиодной лентой датчиками движения SR501
#define PIN_PIR1 2 // назначаем порт для PIR1 sensor
#define PIN_RELE 13 // назначаем порт для реле
unsigned long counttime; // выделение памяти для счетчика

void setup() {
  Serial.begin(9600);
  dht1.begin();
  pinMode(PIN_RELE, OUTPUT);
  pinMode(PIN_PIR1, INPUT);
}

void loop() {
    sensorDhtHum = dht1.readHumidity();
    sensorDhtTemp = dht1.readTemperature();
if (digitalRead(PIN_PIR1) == HIGH) { 
        counttime = millis();
    }

    if (millis() - counttime > 20000) {
        digitalWrite(PIN_RELE, LOW);
    } else {
        digitalWrite(PIN_RELE, HIGH);
}
}

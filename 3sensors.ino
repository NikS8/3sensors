#include <DHT.h>        // You have to download DHT22  library
#define DHT1PIND 7       // PIN подключения датчика DTH22
#define DHT1TYPE DHT22 
DHT dht1(DHT1PIND, DHT1TYPE);
int sensorDhtTemp;      // температура от датчика DHT22 в прихожей 
int sensorDhtHum;       // влажность от датчика DHT22

#define MQ1PINA 1   //  аналоговыйPIN подключения датчика дыма MQ9
#define MQ1PIND 6   //  цифровойPIN подключения датчика дыма MQ9
int sensorMQa;  //  аналоговый сигнал датчика дыма
int sensorMQd;  //  цифровой сигнал датчика дыма

#define HCSRPIND 5 //  цифровойPIN подключения датчика движения
int sensorSRd;  //  цифровой сигнал датчика движения


void setup() {
  Serial.begin(9600);
  pinMode(MQ1PINA, INPUT);
  dht1.begin();

}

void loop() {
  sensorDhtHum = dht1.readHumidity();
  sensorDhtTemp = dht1.readTemperature();

  sensorMQa = analogRead(MQ1PINA);
  sensorMQd = digitalRead(MQ1PIND);

  sensorSRd = digitalRead(HCSRPIND);
}
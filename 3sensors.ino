/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
                                                    3sensors.ino 
                                         Copyright © 2018, Nik.S 
    30.10.2018 v0.1
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*******************************************************************\
   Сервер ArduinoJson выдает значения: 
          аналоговый: 
              от датчика дыма и газа MQ9
          цифровые: 
              от датчика дыма и газа MQ9
              от датчика движения HC-SR501
              от датчика температуры и вдажности DHT22
/*******************************************************************/

#include <ArduinoJson.h>
#include <Ethernet2.h>
#include <SPI.h>
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192,168,0,156);
EthernetServer server(3003);

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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void setup() {
  Serial.begin(9600);
// Initialize Ethernet libary
Ethernet.begin(mac, ip);
 /* if (!Ethernet.begin(mac)) {
    Serial.println(F("Failed to initialize Ethernet library"));
    return;
  }
  */
// Start to listen
  server.begin();
  Serial.println(F("Server is ready."));
  Serial.print(F("Please connect to http://"));
  Serial.println(Ethernet.localIP());

  pinMode(MQ1PINA, INPUT);
  dht1.begin();

}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void loop() {
  sensorDhtHum = dht1.readHumidity();
  sensorDhtTemp = dht1.readTemperature();

  sensorMQa = analogRead(MQ1PINA);
  sensorMQd = digitalRead(MQ1PIND);

  sensorSRd = digitalRead(HCSRPIND);

  // Wait for an incomming connection
  EthernetClient client = server.available();

  // Do we have a client?
  if (!client) return;

  Serial.println(F("New client"));

  // Read the request (we ignore the content in this example)
  while (client.available()) client.read();

  // Allocate JsonBuffer
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonBuffer <512> jsonBuffer;

  // Create the root object
  JsonObject& root = jsonBuffer.createObject();

  // Create the "analog" array
  JsonArray& analogValues = root.createNestedArray("analog");
  /*for (int pin = 0; pin < 6; pin++) {
    // Read the analog input
    int value = analogRead(pin);

    // Add the value at the end of the array
    analogValues.add(value);
  }
  */
   
    root["sensorMQa"] = sensorMQa;
   

  // Create the "digital" array
  JsonArray& digitalValues = root.createNestedArray("digital");
  /*for (int pin = 0; pin < 14; pin++) {
    // Read the digital input
    int value = digitalRead(pin);

    // Add the value at the end of the array
    digitalValues.add(value);
   }
   */
    root["sensorMQd"] = sensorMQd;   
    root["sensorSRd"] = sensorSRd; 
    root["sensorDhtHum %"] = sensorDhtHum;
    root["sensorDhtTemp °C"] = sensorDhtTemp;

  Serial.print(F("Sending: "));
  root.printTo(Serial);
  Serial.println();

  // Write response headers
  client.println("HTTP/1.0 200 OK");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();

  // Write JSON document
  root.prettyPrintTo(client);

  // Disconnect
  client.stop();

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

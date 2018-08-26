#include <DHT.h>        // You have to download DHT  library
#define DHTPIN 5                        // PIN №5 подключения датчика DTH22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
int sensorDhtTempKitchen;
int sensorDhtHumKitchen;

//-----------------
int alarmKitchenPin = A0;          //сигнал открытия двери и окон в летней кухне
int sensorAlarmKitchen;
//-------------------------------------------------

//-----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);

  delay(50);
 
  //----------
  dht.begin();
  //------------
  
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

void loop() {
 
  sensorDhtTempKitchen = dht.readTemperature(); //  считываем показания температуры
  sensorDhtHumKitchen = dht.readHumidity();     //  считываем показания влажности

  sensorAlarmKitchen = analogRead(alarmKitchenPin);

  //-------------
 

        Serial.print(" sensorDhtTempKitchen = ");
        Serial.print(sensorDhtTempKitchen);
        Serial.print(" sensorDhtHumKitchen = ");
        Serial.print(sensorDhtHumKitchen);                 // и отправляем в Serial
        Serial.print(" sensorAlarmKitchen = ");
        Serial.print(sensorAlarmKitchen);                 // и отправляем в Serial

        Serial.println();
        delay(10);                                     // небольшая задержка, иначе неуспевает

        
      
    
  
  //----------
}

#include <SPI.h>
#include <Ethernet2.h>

// МАК адрес
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// адрес сервера
char server[] = "www.cbr-xml-daily.ru";

IPAddress ip(192, 168, 0, 177);

EthernetClient client;

unsigned char buffer[512]; // буфер для чтения
int i = 0, count_read = 0;

void setup() 
{
  Serial.begin(9600);

  if (Ethernet.begin(mac) == 0) 
  {
    Serial.println("Ошибка инициалации, включение режима DHCP");
    Ethernet.begin(mac, ip);
  }
  
  delay(1000); // ждем инициалацию модуля
}

void loop() 
{
  if (client.connect(server, 80))
  {
    Serial.println("Есть подключение к серверу");
    Serial.println("www.cbr-xml-daily.ru");

    // формирование HTTP запроса
    client.println("GET /daily_json.js HTTP/1.1");
    client.println("Host: www.cbr-xml-daily.ru");
    client.println("Connection: close");
    client.println();

    i = 0, count_read = 0;

    while(true)
    {
        while( client.available() ) 
        {
          count_read = client.read(buffer, 1024);

          if( count_read == 0 )
          {
            break;
          }

          buffer[ count_read ] = '\0'; // запишем в конец символ конца строки
          
          Serial.print( (char *) buffer);
        }

        // ждем данные
        if( ! client.available() )
        {
            Serial.print(".");
            i += 1;
            delay(22);
        }

        if(i > 20)
        {
          break;
        }
    }
  
    Serial.println();
    Serial.println("Отключение.");
    client.flush(); // сброс
    client.stop();  // отключение
  } 
  else 
  {
    Serial.println("Не удалось подключиться");
  }

  delay(55000);
}

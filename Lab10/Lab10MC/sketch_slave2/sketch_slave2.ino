#include <DHT.h>
 
#define CRC16 0x8005
#define DHTPIN 9
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

bool isAddress = true;
byte address;
bool isCommand = false;
byte command;
byte data;

void setWriteModeRS485() {
  PORTD |= 1 << PD2;
  delay(1);
}

ISR(USART_TX_vect)
{
  PORTD &= ~(1 << PD2); 
}

void readFromSensor() {
  float temp_c = dht.readTemperature();
  float humidity_c = dht.readHumidity();

  byte* temp = (byte*) &temp_c;
  byte* hum = (byte*) &humidity_c;
  for (int i = 3; i >= 0; i--) {
    Serial.write(hum[i]);
  }
  for (int i = 3; i >= 0; i--) {
    Serial.write(temp[i]);
  }
}

void setup() {
  delay(1000);

  DDRD = 0b00000111;
  PORTD = 0b11111000;

  Serial.begin(9600, SERIAL_8N1);
  UCSR0B |= (1 << UCSZ02) | (1 << TXCIE0);
  UCSR0A |= (1 << MPCM0);

  delay(1);

  address = 0xEA;
  dht.begin();
  
}

void loop() {
  data = (~PIND);
  data = data >> 3;
  if (Serial.available()) {
    byte inByte = Serial.read();
    if (isAddress) {
      if (address == inByte) {
          isAddress = false;
          isCommand = true;
          UCSR0A &= ~(1 << MPCM0);
        }
    } else if (isCommand) {
      command = inByte;
      isCommand = false;
      if (command = 0xB1) {
          isAddress = true;
          setWriteModeRS485();
          //writeData();
          readFromSensor();
        }
    }
  }
}

#define CRC16 0x8005

#define M 0x01
#define A 0x02
#define X 0x03
#define Y 0x04
#define R 0x05
#define I 0x06
#define N 0x07
#define V 0x08
#define O 0x09
#define L 0x0A
#define D 0x0B
#define C 0x0C
#define H 0x0D
#define _ 0x00


bool isAddress = true;
byte address;
bool isCommand = false;
byte command;
byte data;

void setWriteModeRS485() {
  PORTD |= 1 << PD2;
  delay(1);
}

ISR(USART_TX_vect) {
  PORTD &= ~(1 << PD2); 
}

int writeData() {
  byte message[30] = {
    M, A, X, Y, M, _, 
    M, A, R, I, N, A, _,
    V, O, L, O, D, Y, M, Y, R, O, V, Y, C, H, _,
    0x00, 0x00
  };

  byte reflected[28];
  for (int i = 0; i < 28; i++) {
    reflected[i] = ReverseByte(message[i]);
  }

  unsigned short checkSum = Compute_CRC16(reflected);
  byte firstByteOfCheckSum = (checkSum >> 8) & 0xFF;
  byte secondByteOfCheckSum = checkSum & 0xFF;

  message[28] = firstByteOfCheckSum;
  message[29] = secondByteOfCheckSum;
  for (int i = 0; i < 30; i++) {
    Serial.write(message[i]);
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

  address = 0x0B;
}

void loop() {
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
          writeData();
        }
    }
  }
}






unsigned short Compute_CRC16(byte* bytes) {
  const unsigned short generator = 0x1021;
  unsigned short crc = 0xC6C6;

  for (int b = 0; b < 28; b++) {
    crc ^= (unsigned short) (bytes[b] << 8);

    for (int i = 0; i < 8; i++) {
      if ((crc & 0x8000) != 0) {
        crc = (unsigned short) ((crc << 1) ^ generator);
      } else {
        crc <<= 1;
      }
    }
  }
  unsigned short myNewResult = Reflect16(crc);
  return myNewResult;
}


unsigned short Reflect16(unsigned short val) {
  unsigned short resVal = 0;
  for (int i = 0; i < 16; i++) {
    if ((val & (1 << i)) != 0) {
      resVal |= (unsigned short)(1 << (15 - i));
    }
  }
  return resVal;
}

byte ReverseByte(byte b) {
  int a = 0;
  for (int i = 0; i < 8; i++) {
    if ((b & (1 << i)) != 0) {
      a |= 1 << (7 - i);
    }
  }
  return (byte) a;
}

int CombineBytes(byte b1, byte b2) {
  int combined = b1 << 8 | b2;
  return combined;
}

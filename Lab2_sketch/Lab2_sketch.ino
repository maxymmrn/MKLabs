const int leds[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const int btn1 = 12;
const int btn2 = 11;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
}

void loop() {
  bool isClicked1 = !digitalRead(btn1);
  bool isClicked2 = !digitalRead(btn2);
  
  if (isClicked1) {
    Serial.write(0xB1);
  }
  
  if (isClicked2) {
    Serial.write(0xB2);
  }
  
  if (Serial.available()) {
    byte command = Serial.read();
    if (command == 0xB1) {
      for (int i = 0; i < 8; i++) {
        digitalWrite(leds[i], HIGH);
        delay(500);
        digitalWrite(leds[i], LOW);
      }
    } else if (command == 0xB2){
      for (int i = 0; i < 8; i += 2) {
        digitalWrite(leds[i], HIGH);
        delay(500);
        digitalWrite(leds[i], LOW);
      }
      for (int i = 1; i < 8; i += 2) {
        digitalWrite(leds[i], HIGH);
        delay(500);
        digitalWrite(leds[i], LOW);
      }
    }
  }
}

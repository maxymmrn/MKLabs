const int leds[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const int button = 12;

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  bool isClicked = !digitalRead(button);
  if (isClicked) {
    for (int i = 0; i < 8; i++) {
      digitalWrite(leds[i], HIGH);
      delay(500);
      digitalWrite(leds[i], LOW);
    }
  }
}

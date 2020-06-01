#include <IRremote.h>
#include <LiquidCrystal.h>


#define RECEIVE_PIN 2
#define BUZZER_PIN 13

#define BTN_UP 0x511DBB
#define BTN_LEFT 0x52A3D41F
#define BTN_OK 0xD7E84B1B
#define BTN_RIGHT 0x20FE4DBB
#define BTN_DOWN 0xA3C8EDDB

#define BTN_1 0xFF6897
#define BTN_2 0x97483BFB
#define BTN_3 0xF0C41643

#define BTN_4 0x9716BE3F
#define BTN_5 0x3D9AE3F7
#define BTN_6 0x6182021B

#define BTN_7 0x8C22657B
#define BTN_8 0x488F3CBB
#define BTN_9 0x449E79F

#define BTN_STAR 0x32C6FDF7
#define BTN_0 0x1BC0157B
#define BTN_HASHTAG 0x3EC3FC1B


bool regimeA = 0;
bool regimeB = 0;
bool regimeC = 0;
bool regimeD = 0;

LiquidCrystal lcd(3, 4, 5, 6, 7, 8);
IRrecv irrecv(RECEIVE_PIN);
decode_results results;

struct _clock {
  int hours;
  int minutes;
  int seconds;
};

struct _clock clk = {0, 0, 0};
struct _clock alarm = {0, 0, 0};
bool isActiveAlarm = 0;

unsigned long timer = millis();
unsigned long buzzTimer = millis();
int tmp[4] = {0, 0, 0, 0};
int index = 0;


//----------------------------------------------------------------------------------------------------------------------------------

void runAlarm() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
}

void buzzOn() {
  digitalWrite(BUZZER_PIN, HIGH);
  buzzTimer = millis();
}

void buzzOff() {
  if (millis() - buzzTimer >= 200) {
    digitalWrite(BUZZER_PIN, LOW);
  }
}

int getIRNumber(long value) {
  switch (value) {
      case BTN_0:
        return 0;
      case BTN_1:
        return 1;
      case BTN_2:
        return 2;
      case BTN_3:
        return 3;
      case BTN_4:
        return 4;
      case BTN_5:
        return 5;
      case BTN_6:
        return 6;
      case BTN_7:
        return 7;
      case BTN_8:
        return 8;
      case BTN_9:
        return 9;
      default:
        return -1;
    }
}


void chooseRegime(long value) {
  lcd.setCursor(0, 1);
  buzzOn();
  switch (value) {
      case BTN_UP:
        regimeA = 1;
        lcd.print("A:");
        break;
      case BTN_LEFT:
        regimeB = 1;
        lcd.print("B:");
        break;
      case BTN_DOWN:
        regimeC = 1;
        lcd.print("C:");
        break;
      case BTN_RIGHT:
        regimeD = 1;
        lcd.print("D:");
        break;
    }
}


void showTime(int hour, int minute, int second, int row) {
  lcd.setCursor(2, row);
  
  if (hour < 10) {
    lcd.print("0");
    lcd.setCursor(3, row);
    lcd.print(hour);
  } else {
    lcd.print(hour);
  }
  
  lcd.setCursor(4, row);
  lcd.print(":");
  lcd.setCursor(5, row);
  
  if (minute < 10) {
    lcd.print("0");
    lcd.setCursor(6, row);
    lcd.print(minute);
  } else {
    lcd.print(minute);
  }

  lcd.setCursor(7, row);
  lcd.print(":");
  lcd.setCursor(8, row);

  if (second < 10) {
    lcd.print("0");
    lcd.setCursor(9, row);
    lcd.print(second);
  } else {
    lcd.print(second);
  }
}




void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
  lcd.begin(16, 2);
}



void loop() {
  if (irrecv.decode(&results)) {
    if (results.value == BTN_STAR ) {
      regimeA = 0;
      regimeB = 0;
      regimeC = 0;
      regimeD = 0;
      lcd.setCursor(0, 1);
      lcd.print("                ");
      buzzOn();
    } else if (!(regimeA || regimeB || regimeC || regimeD)) {
      chooseRegime(results.value);
    }
    delay(50);
    irrecv.resume();
  }




  if (regimeA) {
    lcd.setCursor(index + 2, 1);
    if (tmp[index] == 0 && getIRNumber(results.value) != -1) {
      tmp[index] = getIRNumber(results.value);
      lcd.print(tmp[index]);
      buzzOn();
      if (++index >= 4) {
        lcd.setCursor(0, 1);
        int h = tmp[0] * 10 + tmp[1];
        int m = tmp[2] * 10 + tmp[3];
        if (h >= 24 || m >= 60) {
          lcd.print("Error           ");
        } else {
          clk.hours = h;
          clk.minutes = m;
          clk.seconds = 0;
          lcd.print("                ");
        }
        index = 0;
        regimeA = 0;
        for (int i = 0; i < 4; i++) {
          tmp[i] = 0;
        }
      }
    }
  } else if (regimeB) {
    lcd.setCursor(index + 2, 1);
    if (tmp[index] == 0 && getIRNumber(results.value) != -1) {
      tmp[index] = getIRNumber(results.value);
      lcd.print(tmp[index]);
      buzzOn();
      if (++index >= 4) {
        lcd.setCursor(0, 1);
        int h = tmp[0] * 10 + tmp[1];
        int m = tmp[2] * 10 + tmp[3];
        if (h >= 24 || m >= 60) {
          lcd.print("Error           ");
        } else {
          alarm.hours = h;
          alarm.minutes = m;
          isActiveAlarm = 1;
          lcd.print("                ");
        }
        index = 0;
        regimeB = 0;
        for (int i = 0; i < 4; i++) {
          tmp[i] = 0;
        }
      }
    }
  } else if (regimeC) {
    showTime(alarm.hours, alarm.minutes, alarm.seconds, 1);
  } else if (regimeD) {
    lcd.setCursor(2, 1);
    if (isActiveAlarm) {
      lcd.print("Yep!");
    } else {
      lcd.print("Nope");
    }
    if (getIRNumber(results.value) == 1) {
      buzzOn();
      isActiveAlarm = 1; 
    } else if (getIRNumber(results.value) == 0) {
      buzzOn();
      isActiveAlarm = 0; 
    }
  }
  
  results.value = 0;


  
  if (millis() - timer * 1000 >= 1000) {
    timer = millis() / 1000;
    
    if (++clk.seconds >= 60) {
      clk.seconds = 0;
      if (++clk.minutes >= 60) {
        clk.minutes = 0;
        if (++clk.hours >= 24) {
          clk.hours = 0;
        }
      }
    }
    showTime(clk.hours, clk.minutes, clk.seconds, 0);
  }

  buzzOff();

  if (clk.hours == alarm.hours 
      && clk.minutes == alarm.minutes 
      && clk.seconds == alarm.seconds 
      && isActiveAlarm) {
    runAlarm();
  }
}

#include <IRremote.h>


#define RECEIVE_PIN 13

#define BTN_UP      0x511DBB
#define BTN_LEFT    0x52A3D41F
#define BTN_OK      0xD7E84B1B
#define BTN_RIGHT   0x20FE4DBB
#define BTN_DOWN    0xA3C8EDDB

#define BTN_1       0xFF6897
#define BTN_2       0x97483BFB
#define BTN_3       0xF0C41643

#define BTN_4       0x9716BE3F
#define BTN_5       0x3D9AE3F7
#define BTN_6       0x6182021B

#define BTN_7       0x8C22657B
#define BTN_8       0x488F3CBB
#define BTN_9       0x449E79F

#define BTN_STAR    0x32C6FDF7
#define BTN_0       0x1BC0157B
#define BTN_HASHTAG 0x3EC3FC1B


bool regimeA = 0;
bool regimeB = 0;
bool regimeC = 0;
bool regimeD = 0;


int numberPins[8] = {1, 2, 3, 4, 5, 6, 7, 8};
int anods[4] = {12, 11, 10, 9};


const int zero[8] =  {1, 1, 1, 1, 1, 1, 0, 0};
const int one[8] =   {0, 1, 1, 0, 0, 0, 0, 0};
const int two[8] =   {1, 1, 0, 1, 1, 0, 1, 0};
const int three[8] = {1, 1, 1, 1, 0, 0, 1, 0};
const int four[8] =  {0, 1, 1, 0, 0, 1, 1, 0};
const int five[8] =  {1, 0, 1, 1, 0, 1, 1, 0};
const int six[8] =   {1, 0, 1, 1, 1, 1, 1, 0};
const int seven[8] = {1, 1, 1, 0, 0, 0, 0, 0};
const int eight[8] = {1, 1, 1, 1, 1, 1, 1, 0};
const int nine[8] =  {1, 1, 1, 1, 0, 1, 1, 0};



IRrecv irrecv(RECEIVE_PIN);
decode_results results;

typedef struct _clock {
  int hours;
  int minutes;
  int seconds;
};

_clock clk = {0, 0, 0};
_clock alarm = {0, 0, 0};
bool isActiveAlarm = 0;

unsigned long timer = millis();

int index = 0;
int tmp[4] = {0, 0, 0, 0};


//////////////////////////////////////////////////////////////////////////////////////////  
void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(anods[i], OUTPUT);
  }
  for (int i = 0; i < 8; i++) {
    pinMode(numberPins[i], OUTPUT);
  }
  irrecv.enableIRIn();
}


void loop() {
  
  if (irrecv.decode(&results)) {
    if (results.value == BTN_STAR) {
      regimeA = 0;
      regimeB = 0;
      regimeC = 0;
      regimeD = 0;
    } else if (!(regimeA || regimeB || regimeC || regimeD)) {
      chooseRegime(results.value);
    }
    delay(50);
    irrecv.resume();
  }

  if (regimeA) {
    show(tmp[0], tmp[1], tmp[2], tmp[3]); 
    if (tmp[index] == 0 && getIRNumber(results.value) != -1) {
      tmp[index] = getIRNumber(results.value);
      if (++index >= 4) {
        int h = tmp[0] * 10 + tmp[1];
        int m = tmp[2] * 10 + tmp[3];
        if (h >= 24 || m >= 60) {
          show(8, 8, 8, 8);
        } else {
          clk.hours = h;
          clk.minutes = m;
          clk.seconds = 0;
        }
        index = 0;
        regimeA = 0;
        for (int i = 0; i < 4; i++) {
          tmp[i] = 0;
        }
      }
    }
  } else if (regimeB) {
    show(tmp[0], tmp[1], tmp[2], tmp[3]); 
    if (tmp[index] == 0 && getIRNumber(results.value) != -1) {
      tmp[index] = getIRNumber(results.value);
      if (++index >= 4) {
        int h = tmp[0] * 10 + tmp[1];
        int m = tmp[2] * 10 + tmp[3];
        if (h >= 24 || m >= 60) {
          show(8, 8, 8, 8);
        } else {
          alarm.hours = h;
          alarm.minutes = m;
          isActiveAlarm = 1;
        }
        index = 0;
        regimeB = 0;
        for (int i = 0; i < 4; i++) {
          tmp[i] = 0;
        }
      }
    }
  } else if (regimeD) {
    if (isActiveAlarm) {
      show(1, 1, 1, 1);
    } else {
      show(0, 0, 0, 0); 
    }
    if (getIRNumber(results.value) == 1) {
      isActiveAlarm = 1; 
    } else if (getIRNumber(results.value) == 0) {
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
  }

  if (regimeC) {
    showTime(alarm);
  } else if (!(regimeA || regimeB || regimeD)) {
    showTime(clk);
  }

  if (clk.hours == alarm.hours 
      && clk.minutes == alarm.minutes 
      && clk.seconds == alarm.seconds 
      && isActiveAlarm) {
    runAlarm();
  }
}
//////////////////////////////////////////////////////////////////////////////////////////



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



void showTime(_clock clk) {
  show(1, (int) clk.hours / 10);
  show(2, clk.minutes % 10);
  show(3, (int) clk.seconds / 10);
  show(4, clk.seconds % 10);
}



void place(unsigned char n) {
  for (int i = 1; i < 5; i++) {
    if (i == n) {
      digitalWrite(anods[i - 1], LOW);
    } else {
      digitalWrite(anods[i - 1], HIGH);
    }
  }
}


void printNumber(int* num) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(numberPins[i], num[i]);
  }
}


void _clear() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(numberPins[i], LOW);
  }
}


void pickNumber(unsigned char n) {
  switch(n) {
    case 0:
      printNumber(zero);
      break;
    case 1:
      printNumber(one);
      break;
    case 2:
      printNumber(two);
      break;
    case 3:
      printNumber(three);
      break;
    case 4:
      printNumber(four);
      break;
    case 5:
      printNumber(five);
      break;
    case 6:
      printNumber(six);
      break;
    case 7:
      printNumber(seven);
      break;
   case 8:
      printNumber(eight);
      break;
   case 9:
      printNumber(nine);
      break;
   default:
      _clear();
      break; 
  }
}


void show(unsigned char x, unsigned char number) {
  place(x);
  pickNumber(number);
  delay(1);
  if (x == 2) {
    digitalWrite(8, HIGH);
  }
  _clear();
}

void show(int a, int b, int c, int d) {
  show(1, a);
  show(2, b);
  show(3, c);
  show(4, d);
}


void runAlarm() {
  for (int i = 0; i < 3; i++) {
    analogWrite(A0, 100);
    delay(200);
    analogWrite(A0, 0);
    delay(200);
  }
}

void chooseRegime(long value) {
  switch (value) {
      case BTN_UP:
        regimeA = 1;
        break;
      case BTN_LEFT:
        regimeB = 1;
        break;
      case BTN_DOWN:
        regimeC = 1;
        break;
      case BTN_RIGHT:
        regimeD = 1;
        break;
   }
}

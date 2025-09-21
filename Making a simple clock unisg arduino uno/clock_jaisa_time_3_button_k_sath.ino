#include<LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd( rs, en, d4, d5, d6, d7);
int Second = 0;
int Minute = 0;
int Hour = 0;
int setSecond = 0;
int setMinute = 0;
int setHour = 0;
unsigned long previousMillis = 0;
const long interval = 1000;
unsigned long previousMillis1 = 0;
const long interval1 = 25;
int button1 = A3;
int button2 = A2;
int button3 = A1;
int buttonPress1 = 0;
int buttonPress2 = 0;
int buttonPress3 = 0;
void setup() {
  Serial.begin(115200);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("CLOCK TIME");
  myTimecheck();
}
void loop () {
  unsigned long currentMillis = millis();
  if ( currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    if (setSecond < 59)
    {
      setSecond += 1;
    }
    else
    {
      setSecond = 0;
      setMinute += 1;
    }
    if (setMinute > 59)
    {
      setMinute = 0;
      setHour += 1;
    }
    if (setHour > 12)
    {
      setHour = 1;
    }

    myTimecheck();
  }
  if ( currentMillis - previousMillis1 >= interval1)
  {
    previousMillis1 = currentMillis;
    myButton1();
    myButton2();
    myButton3();
  }
}
void myButton1() {
  if ( digitalRead(button1) == LOW)
  {
    if ( buttonPress1 == 0 )
    {
      buttonPress1 = 1;
      if ( setHour < 12)
      {
        setHour += 1;
      }
      else
      {
        setHour = 1;
      }
      myTimecheck();
      Serial.println("hour is increase");
    }
  }
  if ( digitalRead(button1) == HIGH)
  {
    if (buttonPress1 == 1)
    {
      buttonPress1 = 0;
    }
  }
}
void myButton2() {
  if ( digitalRead(button2) == LOW)
  {
    if ( buttonPress2 == 0 )
    {
      buttonPress2 = 1;
      if ( setMinute < 59)
      {
        setMinute += 1;
      }
      else
      {
        setMinute = 0;
      }
      myTimecheck();
      Serial.println("minute is increase");
    }
  }
  if ( digitalRead(button2) == HIGH)
  {
    if (buttonPress2 == 1)
    {
      buttonPress2 = 0;
    }
  }
}
void myButton3() {
  if ( digitalRead(button3) == LOW)
  {
    if ( buttonPress3 == 0 )
    {
      buttonPress3 = 1;
      if ( setSecond < 59)
      {
        setSecond += 1;
      }
      else
      {
        setSecond = 0;
      }
      myTimecheck();
      Serial.println("Second is increase");
    }
  }
  if ( digitalRead(button3) == HIGH)
  {
    if (buttonPress3 == 1)
    {
      buttonPress3 = 0;
    }
  }
}
void myTimecheck() {
  lcd.setCursor(0,  1);
  char timeString[9];
  sprintf ( timeString, "%02d:%02d:%02d", setHour, setMinute, setSecond);
  lcd.print(timeString);
}

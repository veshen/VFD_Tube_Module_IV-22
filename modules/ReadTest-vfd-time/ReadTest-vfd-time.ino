#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

#include "VFDTube.h"

#define TUBE_COUNT 6

VFDTube tube(4, 5, 6, 7, TUBE_COUNT);


void setup() {
  Serial.begin(9600);
  tube.setBrightness(0x20); // set brightness, range 0x00 - 0xff
  //tube.setBackgroundColor(Magenta);
  tube.setBackgroundColor(0,White);
  tube.setBackgroundColor(1,Yellow);
  tube.setBackgroundColor(2,Magenta);
  tube.setBackgroundColor(3,Red);
  tube.setBackgroundColor(4,Cyan);
  tube.setBackgroundColor(5,Blue);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("DS1307RTC Read Test");
  Serial.println("-------------------");
}

void loop() {
  tmElements_t tm;

  if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
    
    tube.printf("%02d.%02d.%02d", tm.Hour,tm.Minute,tm.Second);
    tube.display();
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

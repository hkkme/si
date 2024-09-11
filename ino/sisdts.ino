#include <SPI.h>
#include <SD.h>
#include <RTClib.h>

// sd
File myFile;

// timestamp
// SDA > A4
// SCL > A5
// 5.0 V
RTC_DS3231 rtc;

// sensor
int sensorPin = A0;
int sensorValue = 0;

void setup(){
    Serial.begin(9600);
    while (!Serial) {
      ; // wait serial port connection
    }

    // sensor
    pinMode(sensorPin, INPUT);

    // timestamp
    if (!rtc.begin()) {
        Serial.println("RTC not found");
        Serial.flush();
        abort();
    }

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // rtc.adjust(DateTime(2024, 9, 6, 0, 0, 0));

    // sd
    if (!SD.begin()) {
        Serial.println("failed");
        return;
    }

    Serial.println("init");
}

void loop(){
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);

    DateTime now = rtc.now();

    myFile = SD.open("sidata.csv", FILE_WRITE);
    if (myFile) {
        myFile.print(sensorValue);
        myFile.print(",");
        myFile.print(now.day(), DEC);
        myFile.print(".");
        myFile.print(now.month(), DEC);
        myFile.print(".");
        myFile.print(now.year(), DEC);
        myFile.print("|");
        myFile.print(now.hour(), DEC);
        myFile.print(":");
        myFile.print(now.minute(), DEC);
        myFile.print(":");
        myFile.print(now.second(), DEC);
        myFile.print('\n');
        myFile.flush();
        myFile.close();
    } else {
        Serial.println("error");
    }

    delay(3000);
}

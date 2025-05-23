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

// relay
int relayPin = 8;

void setup(){
    Serial.begin(9600);
    while (!Serial) {
      ; // wait serial port connection
    }

    // sensor
    pinMode(sensorPin, INPUT);

    // relay
    pinMode(relayPin, OUTPUT);

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
    char dateBuffer[16];

    myFile = SD.open("sidata.csv", FILE_WRITE);

    if (myFile) {
        sprintf(dateBuffer, "%04d-%02d-%02d,%02d:%02d:%02d,%00d",
            now.year(), now.month(), now.day(),
            now.hour(), now.minute(), now.second(),
            sensorValue);
        myFile.println(dateBuffer);
        myFile.flush();
        myFile.close();
    } else {
        Serial.println("error");
    }

    if(sensorValue > 425) {
        digitalWrite(relayPin, 1);
        // pause to let water infiltrate
        // adjust according to hose length
        // delay(50000);
        // digitalWrite(relayPin, 0);
        // delay(10000);
    } else {
        digitalWrite(relayPin, 0);
        // delay(60000);
    }

    delay(2000);
}
// smart irrigation + sd

#include <SPI.h>
#include <SD.h>

// sd
File myFile;

// si
int sensorPin = A0;
int sensorValue = 0;
int relayPin = 8;

void setup(){
    pinMode(sensorPin, INPUT);
    pinMode(relayPin, OUTPUT);
    Serial.begin(9600);

    // sd

    if (!SD.begin()) {
        Serial.println("failed");
        return;
    }

    Serial.println("initialized");
}

void loop(){
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);

    // sd
    myFile = SD.open("sidata.txt", FILE_WRITE);
    myFile.print(sensorValue);
    myFile.print(",");
    myFile.close();

    if(sensorValue > 440) {
        digitalWrite(relayPin, 1);
        // pause to let water infiltrate
        // adjust according to hose length
        delay(5000);
        digitalWrite(relayPin, 0);
        delay(20000);

    } else {
        digitalWrite(relayPin, 0);
    }

    delay(2000);
}

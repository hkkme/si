// smart irrigation basic

int sensorPin = A0;
int sensorValue = 0;
int relayPin = 12;

void setup(){
  pinMode(sensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

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

  delay(1000);
}

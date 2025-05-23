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

  if(sensorValue > 480) {
    digitalWrite(relayPin, 1);
  } else {
    digitalWrite(relayPin, 0);
  }

  delay(1000);
}

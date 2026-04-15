const int potPin = 34; 
const int ledPin = 2;  

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);
  Serial.println(potValue); 

  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'H') digitalWrite(ledPin, HIGH);
    if (command == 'L') digitalWrite(ledPin, LOW);
  }
  delay(50); 
}
const int ledPin1 = 12;
const int ledPin2 = 13;
const int sensorPin1 = 34; 
const int sensorPin2 = 35;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  establishContact();
}

void loop() {
  if (Serial.available() > 0) {
    int inByte = Serial.read();

    int val1 = analogRead(sensorPin1);
    int val2 = analogRead(sensorPin2);

    Serial.print(val1);
    Serial.print(",");
    Serial.println(val2);

    if (inByte == 'H') digitalWrite(ledPin1, HIGH);
    if (inByte == 'L') digitalWrite(ledPin1, LOW);
    
    digitalWrite(ledPin2, (val1 > 2000) ? HIGH : LOW);
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("0,0");
    delay(300);
  }
}
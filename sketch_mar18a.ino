const int potPin = 34;    
const int photoPin = 35;  
const int buttonPin = 18; 
const int led1 = 21;      
const int led2 = 22;      
const int led3 = 23;      

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(potPin, INPUT);
  pinMode(photoPin, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);
  int lightValue = analogRead(photoPin);
  int buttonState = digitalRead(buttonPin);

  int speed = map(potValue, 0, 4095, 50, 500);

  if (buttonState == LOW) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  } else {
    digitalWrite(led1, HIGH);
    delay(speed);
    digitalWrite(led1, LOW);

    digitalWrite(led2, HIGH);
    delay(speed);
    digitalWrite(led2, LOW);

    digitalWrite(led3, HIGH);
    delay(speed);
    digitalWrite(led3, LOW);
  }

  Serial.print(potValue);
  Serial.print(",");
  Serial.println(lightValue);

  delay(10); 
}
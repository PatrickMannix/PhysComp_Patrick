
const int potPin = 1;         
const int ldrPin = 2;         
const int touchPin = 3;       
const int btnPin = 4;         
const int pwmLedPin = 5;      
const int digitalLedPin = 6;  
const int piezoPin = 8;       

int btnState = 0;
int lastBtnState = 1;
bool systemActive = false;
unsigned long lastUpdate = 0;
int interval = 1000;
int brightnessArray[] = {0, 85, 170, 255}; 

void setup() {
  pinMode(btnPin, INPUT_PULLUP); 
  pinMode(digitalLedPin, OUTPUT);
  pinMode(pwmLedPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  
  analogReadResolution(12); 

void loop() {
  unsigned long now = millis();
  
  
  int potVal = analogRead(potPin);
  int ldrVal = analogRead(ldrPin);
  int touchVal = analogRead(touchPin);
  btnState = digitalRead(btnPin);

  
  if (btnState == LOW && lastBtnState == HIGH) {
    systemActive = !systemActive;
    delay(50); 
  }
  lastBtnState = btnState;

  
  if (systemActive && (touchVal > 1500 || potVal > 500)) {
    digitalWrite(digitalLedPin, HIGH);

    
    int invertedLDR = 4095 - ldrVal;
    for (int i = 0; i < 4; i++) {
      if (invertedLDR > (i * 1000)) {
        analogWrite(pwmLedPin, brightnessArray[i]);
      }
    }

    
    if (now - lastUpdate >= interval) {
      lastUpdate = now;
      tone(piezoPin, 880, 50);
    }
  } else {
    
    digitalWrite(digitalLedPin, LOW);
    analogWrite(pwmLedPin, 0);
  }
}
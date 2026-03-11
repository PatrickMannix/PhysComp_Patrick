const pins = [1, 2, 3, 4, 5, 6, 7]; 

const potPin = pins[0];      
const ldrPin = pins[1];      
const touchPin = pins[2];    
const btnPin = pins[3];      
const pwmLedPin = pins[4];   
const digitalLedPin = pins[5]; 
const servoPin = pins[6];    
const piezoPin = 8;          

let btnState = 0;
let lastBtnState = 1;
let systemActive = false;
let lastUpdate = 0;
let interval = 1000;
let brightnessArray = [0, 85, 170, 255]; 

void setup() {
  pinMode(btnPin, "INPUT_PULLUP");
  pinMode(digitalLedPin, "OUTPUT");
  pinMode(pwmLedPin, "OUTPUT");
  pinMode(servoPin, "SERVO");
  pinMode(piezoPin, "OUTPUT");
  
  
  analogReadResolution(12); 
}

void loop() {
  let now = millis();
  
  
  let potVal = analogRead(potPin);     
  let ldrVal = analogRead(ldrPin);     
  let touchVal = analogRead(touchPin); 
  btnState = digitalRead(btnPin);

  
  if (btnState === 0 && lastBtnState === 1) {
    systemActive = !systemActive;
  }
  lastBtnState = btnState;

  
  if (systemActive && (touchVal > 1500 || potVal > 500)) {
    digitalWrite(digitalLedPin, 1);

    
    let angle = Math.floor((potVal / 4095) * 180);
    servoWrite(servoPin, angle);

    
    let invertedLDR = 4095 - ldrVal; 
    for (let i = 0; i < brightnessArray.length; i++) {
      if (invertedLDR > (i * 1000)) {
        analogWrite(pwmLedPin, brightnessArray[i]);
      }
    }

    
    if (now - lastUpdate >= interval) {
      lastUpdate = now;
      for (let j = 0; j < 2; j++) {
        tone(piezoPin, 880, 50); 
      }
    }
  } else {
    
    digitalWrite(digitalLedPin, 0);
    analogWrite(pwmLedPin, 0);
    servoWrite(servoPin, 90); 
  }
}

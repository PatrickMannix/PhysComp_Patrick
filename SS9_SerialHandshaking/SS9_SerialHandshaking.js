let serial;
let sensor1 = 0;
let sensor2 = 0;
let mode = 0; 

function setup() {
  createCanvas(800, 600); 
  
  serial = new p5.SerialPort();
  serial.open("/dev/tty.usbserial-XXXX"); 
  serial.on('data', gotData);
}

function gotData() {
  let currentString = serial.readLine();
  trim(currentString);
  if (!currentString) return;
  
  let sensors = split(currentString, ',');
  if (sensors.length > 1) {
    sensor1 = Number(sensors[0]);
    sensor2 = Number(sensors[1]);
  }
  
  if (mouseIsPressed) {
    serial.write('H');
  } else {
    serial.write('L');
  }
}

function draw() {
  background(20, 24, 35);
  
  if (keyIsPressed && key === 'm') mode = 1; 
  else mode = 0;

  if (mode === 0) {
    drawPulseMode();
  } else {
    drawRadarMode();
  }
  
  fill(255);
  noStroke();
  textSize(16);
  text("Mode: " + (mode === 0 ? "Pulse" : "Radar"), 20, 30);
  text("Sensor 1: " + sensor1, 20, 50);
  text("Sensor 2: " + sensor2, 20, 70);
}

function drawPulseMode() {
  let diameter = map(sensor1, 0, 4095, 50, 400);
  fill(0, 200, 255, 150);
  noStroke();
  ellipse(width/2, height/2, diameter);
  
  push();
  translate(width/2, height/2);
  rotate(frameCount * 0.05);
  noFill();
  stroke(255);
  strokeWeight(2);
  rectMode(CENTER);
  let side = map(sensor2, 0, 4095, 10, 300);
  rect(0, 0, side, side);
  pop();
}

function drawRadarMode() {
  stroke(0, 255, 100);
  strokeWeight(2);
  let x = map(sensor1, 0, 4095, 0, width);
  line(x, 0, x, height);
  
  for(let i = 0; i < 10; i++) {
    let y = (frameCount * 2 + (i * 60)) % height;
    let alpha = map(sensor2, 0, 4095, 50, 255);
    stroke(0, 255, 100, alpha);
    line(0, y, width, y);
  }

  noFill();
  stroke(255, 50);
  ellipse(width/2, height/2, sensor2/10, sensor2/10);
}
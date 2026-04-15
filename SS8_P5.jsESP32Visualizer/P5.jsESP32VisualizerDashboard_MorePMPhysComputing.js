let port;
let sensorValue = 0;
let mode = "Visualizer"; 
let circleSize = 50;

function setup() {
  createCanvas(800, 600);
  port = createSerial();
  textSize(18);
  textAlign(CENTER);
}

function draw() {
  if (port.available() > 0) {
    let str = port.readString().trim();
    if (str.length > 0) {
      sensorValue = float(str);
    }
  }

  let mappedHue = map(sensorValue, 0, 4095, 0, 255);
  let mappedSize = map(sensorValue, 0, 4095, 20, 300);
  let rotationSpeed = map(sensorValue, 0, 4095, 0, 0.1);

  background(mappedHue, 80, 150);

  fill(255);
  text(`Current Mode: ${mode} (Click to toggle)`, width / 2, 40);
  text(`Sensor Data: ${sensorValue}`, width / 2, 70);

  push();
  translate(width / 2, height / 2);
  
  if (mode === "Visualizer") {
    drawVisualizer(mappedSize, rotationSpeed);
  } else {
    drawPulse(mappedSize);
  }
  pop();
}

function drawVisualizer(sz, speed) {
  rotate(frameCount * speed);
  fill(255, 204, 0);
  rectMode(CENTER);
  rect(0, 0, sz, sz);
  
  fill(0, 255, 255);
  ellipse(sz/1.2, 0, sz/2.5);
}

function drawPulse(sz) {
  let pulse = sin(frameCount * 0.1) * 40;
  fill(255, 100, 100);
  triangle(0, -sz/2 - pulse, -sz/2, sz/2, sz/2, sz/2);
}

function mousePressed() {
  if (mode === "Visualizer") {
    mode = "Pulse";
    port.write('H');
  } else {
    mode = "Visualizer";
    port.write('L');
  }
  
  if (!port.opened()) {
    port.open(115200);
  }
}
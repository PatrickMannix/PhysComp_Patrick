let isDrawing = false;
let sensorValue = 0;
let bgBrightness = 240;

function setup() {
  let canvasWidth = constrain(windowWidth, 400, 1080);
  let canvasHeight = constrain(windowHeight, 400, 720);
  
  createCanvas(canvasWidth, canvasHeight);
  background(bgBrightness);
}

function draw() {
  sensorValue = mouseX; 

  if (isDrawing) {
    let dynamicColor = map(sensorValue, 0, width, 0, 255);
    let shapeSize = map(sensorValue, 0, width, 10, 150);
    
    fill(dynamicColor, 150, 255 - dynamicColor);
    stroke(0);
    strokeWeight(1);

    line(pmouseX, pmouseY, mouseX, mouseY);
    rect(mouseX, mouseY, shapeSize, shapeSize);
    ellipse(mouseX, mouseY, shapeSize * 0.5);
  }
}

function mousePressed() {
  isDrawing = true;
  bgBrightness = map(mouseY, 0, height, 255, 100);
  background(bgBrightness);
}

function mouseReleased() {
  isDrawing = false;
}

function windowResized() {
  let canvasWidth = constrain(windowWidth, 400, 1080);
  let canvasHeight = constrain(windowHeight, 400, 720);
  resizeCanvas(canvasWidth, canvasHeight);
  background(bgBrightness);
}
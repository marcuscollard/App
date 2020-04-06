
// include and define
#include <SoftwareSerial.h>
#define BT_SERIAL_RX 10

// constants
const int serialBegin = 9600;

// variables
int sensorPin = A0;
int sensorValue = 0;

// define serial
SoftwareSerial BluetoothSerial(BT_SERIAL_RX);


void setup() {
  // put your setup code here, to run once:
  BluetoothSerial.begin(serialBegin);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(sensorPin);
  
}

float maxVelocity = 0.0;
float maxDecelerationX = 0.0;
float maxAccelerationY = 0.0;


bool checkCrash(float gX, float gY, float aX, float aY) {
  // receive variables in form of gX, gY, gZ, aX, aY, aZ, mX, mY, mZ
  return checkXcrash(aX) || checkYcrash(aY);
}                                                                   

bool checkXcrash(float aX) {
  if (aX < maxDecelerationX) {
    return true;
  }
  return false;
}

bool checkYcrash(float aY) {
    if (aY > maxAccelerationY) {
    return true;
  }
  return false;
}

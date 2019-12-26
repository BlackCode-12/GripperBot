
#include <AFMotor.h>

//DUALSHOCK3 CONTROLLED GRIPPER BOT
#include <PS3BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

AF_DCMotor motorXaxis(3);
AF_DCMotor motorYaxis(4);

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
//PS3BT PS3(&Btd); // This will just create the instance
PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;

void setup() {
  Serial.begin(9600);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  motorR.setSpeed(255);//right
  motorL.setSpeed(255);//left
  motorXaxis.setSpeed(150);//xaxis
  motorYaxis.setSpeed(150);//yaxis

  pinMode(A0,OUTPUT);

  delay(2000);
}
void loop() {
  Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    
    if(PS3.getAnalogHat(LeftHatY) > 90 && PS3.getAnalogHat(LeftHatY) <120){
      Serial.print(F("\r\nLeftHatY:STOP STOP"));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      motorR.run(RELEASE);
      motorL.run(RELEASE);
      motorYaxis.run(RELEASE);
      motorXaxis.run(RELEASE);    
    }
    if(PS3.getAnalogHat(LeftHatX) > 110 && PS3.getAnalogHat(LeftHatX) < 135){
      Serial.print(F("\r\nLeftHatY:STOP STOP"));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      motorR.run(RELEASE);
      motorL.run(RELEASE);
      motorYaxis.run(RELEASE);
      motorXaxis.run(RELEASE);
    }
    //up
    if (PS3.getAnalogHat(LeftHatY) == 0) {
      Serial.print(F("\r\nLeftHatY:GO FORWARD "));
      Serial.print(PS3.getAnalogHat(LeftHatY));

      motorYaxis.run(FORWARD);
      motorXaxis.run(RELEASE);
    }

    //DOWN
    if (PS3.getAnalogHat(LeftHatY) == 255) {
      Serial.print(F("\r\nLeftHatY: GO BACKWARD "));
      Serial.print(PS3.getAnalogHat(LeftHatY));

      motorYaxis.run(BACKWARD);
      motorXaxis.run(RELEASE);
    }

    //left
    if (PS3.getAnalogHat(RightHatX) == 0) {
      Serial.print(F("\r\RightHatX: TURN LEFT "));
      Serial.print(PS3.getAnalogHat(RightHatX));

      motorYaxis.run(RELEASE);
      motorXaxis.run(FORWARD);

    }

    //right
    if (PS3.getAnalogHat(RightHatX) == 255) {
      Serial.print(F("\r\RightHatX; TURN RIGHT"));
      Serial.print(PS3.getAnalogHat(RightHatX));

      motorYaxis.run(RELEASE);
      motorXaxis.run(BACKWARD);
    }
void modes(){
    //RAMPAGE MODE destruction mode
    if (PS3.getAnalogButton(L1)) {
      Serial.print(F("\r\nL1: RAMPAGE MODE "));
      Serial.print(PS3.getAnalogButton(L1));
      analogWrite(A0,255);//Telling arduino nano to switch on TURRET RAMPAGE MODE
      motorYaxis.run(RELEASE);//one rampage cycle starts
      motorXaxis.run(FORWARD);
      delay(1000);
      motorXaxis.run(FORWARD);
      motorYaxis.run(RELEASE);
      delay(250);
      motorXaxis.run(RELEASE);
      motorYaxis.run(BACKWARD);
      delay(1000);
      motorXaxis.run(BACKWARD);
      motorYaxis.run(RELEASE);
      delay(250);             //one rampage cyce ends




      
    }

    //release 
    if (PS3.getAnalogButton(L2)) {
      Serial.print(F("\r\nL2:RELEASE "));
      Serial.print(PS3.getAnalogButton(L2));
      motorXaxis.run(BACKWARD);
      motorL.run(RELEASE);
      motorR.run(RELEASE);
      motorYaxis.run(RELEASE);
    }

    //UP
    if (PS3.getAnalogButton(R1)) {
      Serial.print(F("\r\nR1:UP "));
      Serial.print(PS3.getAnalogButton(R1));
      motorYaxis.run(BACKWARD);
      motorL.run(RELEASE);
      motorR.run(RELEASE);
      motorXaxis.run(RELEASE);

    }

    //DOWN
    if (PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nR2:DOWN "));
      Serial.print(PS3.getAnalogButton(R2));
      motorYaxis.run(FORWARD);
      motorL.run(RELEASE);
      motorR.run(RELEASE);
      motorXaxis.run(RELEASE);

    }

  }
}

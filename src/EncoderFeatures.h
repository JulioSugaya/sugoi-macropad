// #include <Mouse.h> //there are some mouse move functions for encoder_Mode 2 and 3
#include <Encoder.h>   
#include <Bounce2.h>
#include "KeyboardAndPad.h"
//Library for simple interfacing with encoders (up to two)
//low performance ender response, pins do not have interrupts

// PIN OUT
// Encoder
// Encoder RotaryEncoderA(14, 15); //the LEFT encoder (encoder A)
int SW = 18;
int DT = 8;
int CLK = 3;
Encoder volumeKnob(DT,CLK);
Bounce encoderButton = Bounce(SW,10);
long positionEncoderA  = -999; //encoderA LEFT position variable
long oldPosition = -999;

void encoderSetup() {
    pinMode(SW, INPUT_PULLUP);
}

void checkEncoder() {
      //check encoder rotation
  long newPosition = volumeKnob.read();
  if(newPosition != oldPosition){
    if((newPosition - oldPosition) > 0) {
      //volumeup
      sendToScreen("volume up");
      keyboard.press(KEY_MEDIA_VOLUME_UP);
    } else {
      //volumedown
      sendToScreen("volume down");
      keyboard.press(KEY_MEDIA_VOLUME_DOWN);
    }
    oldPosition = newPosition;
    delay(200);
  }
}

void checkEncoder_2(){ //testing some encoder wheel pay control for arcade games; centede, tempest...

  long newPos = volumeKnob.read()/2; 
  if (newPos != positionEncoderA && newPos > positionEncoderA) {
    positionEncoderA = newPos;
    sendToScreen("volume up");
    keyboard.press(KEY_MEDIA_VOLUME_UP);
  }

  if (newPos != positionEncoderA && newPos < positionEncoderA) {
    positionEncoderA = newPos;
    sendToScreen("volume down");
    keyboard.press(KEY_MEDIA_VOLUME_DOWN);
  }
}

// //=============Encoder A & B Function ====== Set 3 =========================================================
// void encoderA_Mode3(){
//   long newPos = RotaryEncoderA.read()/2; 
//   if (newPos != positionEncoderA && newPos > positionEncoderA) {
//     positionEncoderA = newPos;
//     // Mouse.press(MOUSE_LEFT); //holds down the mouse left click
//     // Mouse.move(0,4,0); //moves mouse down... Mouse.move(x, y, wheel) range is -128 to +127
//     // Mouse.release(MOUSE_LEFT); //releases mouse left click
//                                                                }

//   if (newPos != positionEncoderA && newPos < positionEncoderA) { 
//     positionEncoderA = newPos;
//     // Mouse.press(MOUSE_LEFT); //holds down the mouse left click
//     // Mouse.move(0,-4,0); //moves mouse up... Mouse.move(x, y, wheel) range is -128 to +127
//     // Mouse.release(MOUSE_LEFT); //releases mouse left click                   
//                                                               }
// }
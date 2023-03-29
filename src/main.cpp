#include <Arduino.h>
// #include "HID.h"
/*******************************************************************
 * RYAN UPDATE THIS (MAYBE LATER ITS DEC 24 AND I JUST GOT THE VIDEO DONE)
 * A multi-mode Macro keyboard with Arduino Pro Micro using row column matrix.
 * This is a basic sketch to understand key layout, basic hotkeys macros and some extras like:
 *    -RBG addressble LEDs compatible with Adafruit's neopixel library.  
 *    -i2c for 4x20 LCD to describe each function.  (you might have a different LCD...)
 *    -mouse movement + mouse clicks.
 *Some mouse movement (in pixels) pull their values from analogRead(pin 0) so make sure something is connected.
 *Don't forget to solder all the diode and encoder solder jumpers on the backside!!
 * (c) 2020 Ryan Bates

  Last time I touched this: Dec 13 2020
  web: www.retrobuiltgames.com
  youtube: https://www.youtube.com/c/ryanbatesrbg
  twitter: @retrobuiltgames
  Buy this PCB at https://www.tindie.com/products/19957/

Ryan's Pro Tips:
=============== Keyboard Control================================================================================
Keyboard.write();   Sends a keystroke to a connected computer. 
                    This is similar to pressing and releasing a key on your keyboard.
                    Will send a shift command if applicable. Example: Keyboard.write('K') will 
                    automatically do SHIFT + k. 
                    Can also accept ASCII code like this:
                    //Keyboard.write(32); // This is space bar (in decimal)
                    Helpful list of ASCII + decimal keys http://www.asciitable.com/
                    

Keyboard.press();   Best for holding down a key with multi-key commands; like copy/ paste
                    This example is [ctrl] + [shift] + [e] 
                      //Keyboard.press(KEY_LEFT_CTRL);
                      //Keyboard.press(KEY_LEFT_SHIFT);
                      //Keyboard.press('e'); 
                      //delay(100); Keyboard.releaseAll();
                

Keyboard.print();   Sends a keystroke(s)
                    Keyboard.print("stop using aim bot"); // types this in as a char or int! (not a string)!


Keyboard.println(); Sends a keystroke followed by a newline (carriage return)
                     Very practical if you want to type a password and login in one button press!
                     
SOMETIMES, applications are coded to recognize Keyboard.press() and not Keyboard.write() and vice versa.
You might have to experiment. 

=============== Mouse Control================================================================================
Mouse.move(x, y, wheel);  Moves the mouse and or scroll wheel up/down left/right.
                          Range is -128 to +127. units are pixels 
                          -number = left or down
                          +number = right or up

Mouse.press(b);         Presses the mouse button (still need to call release). Replace "b" with:
                        MOUSE_LEFT   //Left Mouse button
                        MOUSE_RIGHT  //Right Mouse button
                        MOUSE_MIDDLE //Middle mouse button
                        MOUSE_ALL    //All three mouse buttons
                        
Mouse.release(b);       Releases the mouse button.

Mouse.click(b);         A quick press and release.

**********************************************************************************************************/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Display.h"
#include "EncoderFeatures.h"
#include "LED.h"
// #include <Keyboard.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

unsigned long previousMillis = 0;     // values to compare last time interval was checked (For LCD refreshing)
int check_State = 0;                  // state to check trigger the demo interrupt
int updateLCD_flag = 0;               // LCD updater, this flag is used to only update the screen once between mode changes
                                      // and once every 3 second while in a mode. Saves cycles / resources
const int b = 3;       // Brightness control variable. Used to divide the RBG vales set for the RGB LEDs. full range is 0-255. 255 is super bright
                       // In fact 255 is obnoxiously bright, so this use this variable to reduce the value. It also reduces the current draw on the US

// Variables that will change:
int modePushCounter = 0;       // counter for the number of button presses
int buttonState = 0;           // current state of the button
int lastButtonState = 0;       // previous state of the button

const int ModeButton = 0;     // the pin that the Modebutton is attached to
const int pot = 1;           // pot for adjusting attract mode demoTime or mouseMouse pixel value
//const int Mode1= A2;
//const int Mode2= A3; //Mode status LEDs

void setup() {
  displaySetup();
  // pinMode(ModeButton, INPUT_PULLUP);  // initialize the button pin as a input:  
  // Serial.begin(9600); // initialize serial communication:

  // delay(800);
  encoderSetup();
  keyboardSetup();
}


void loop() {
  if(keyboard.isConnected()) {
    char key = keypad.getKey();
    if(key != -1) {
      keyboardSend(key);
    }
    delay(50);
    checkEncoder_2();
  } else {
    sendToScreen("Not connected.");
  }
}
//---------------------Sub Routine Section--------------------------------------------------------------------------

// void checkModeButton(){
//   buttonState = digitalRead(ModeButton);
//   if (buttonState != lastButtonState) { // compare the buttonState to its previous state
//     if (buttonState == LOW) { // if the state has changed, increment the counter
//       // if the current state is LOW then the button cycled:
//       modePushCounter++;
//       Serial.println("pressed");
//       Serial.print("number of button pushes: ");
//       Serial.println(modePushCounter);
//       colorUpdate = 0;      // set the color change flag ONLY when we know the mode button has been pressed. 
//                             // Saves processor resources from updating the neoPixel colors all the time
//     } 
//     delay(50); // Delay a little bit to avoid bouncing
//   }
//   lastButtonState = buttonState;  // save the current state as the last state, for next time through the loop
//    if (modePushCounter >3){       //reset the counter after 4 presses CHANGE THIS FOR MORE MODES
//       modePushCounter = 0;}
// }
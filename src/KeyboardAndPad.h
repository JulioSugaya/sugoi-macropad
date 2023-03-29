// This library is for interfacing with the 3x4 Matrix
// Can be installed from the library manager, search for "keypad"
// and install the one by Mark Stanley and Alexander Brevig
// https://playground.arduino.cc/Code/Keypad/
// Library with a lot of the HID definitions and methods
// Can be useful to take a look at it see whats available
// https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h
#include <BleKeyboard.h>
#include <Keypad.h>
// #include <Keyboard.h>
// #include <HID-Project.h>
// #include "Display.h"

BleKeyboard keyboard;
// BootKeyboard keyboard;

// 5x2 key matrix 
//IP
#define R1 4
#define R2 5
//OP
#define C1 6
#define C2 7
#define C3 15
#define C4 16
#define C5 17

const byte ROWS = 2; 
const byte COLS = 5;
int colorUpdate = 0; 

byte rowPins[ROWS] = {R1, R2};    //connect to the row pinouts of the keypad
byte colPins[COLS] = {C1, C2, C3, C4, C5};  //connect to the column pinouts of the keypad


char keys[ROWS][COLS] = {
  {'1', '2', '3', '4', '5'},
  {'6', '7', '8', '9', '0'}
};

// The library will return the character inside this array when the appropriate
// button is pressed then look for that case statement. This is the key assignment lookup table.
// Layout(key/button order) looks like this
//     |----------------------------|
//     |                  [2/3]*    |     *TRS breakout connection. Keys 5 and 6 are duplicated at the TRS jack
//     |      [ 1] [ 2] [ 3] [ 4]   |     * Encoder A location = key[1]      
//     |      [ 5] [ 6] [ 7] [ 8]   |     * Encoder B location = Key[4]
//     |      [ 9] [10] [11] [12]   |      NOTE: The mode button is not row/column key, it's directly wired to A0!!
//     |----------------------------|
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void keyboardSetup() {
  // Serial.begin(115200);
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], INPUT_PULLDOWN);
  }
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }
  keyboard.begin();
  keyboard.setDelay(10);
  keyboard.setName("Sugoi Macropad");
}

void keyboardSend(char key) {
  String text = "";
  
  switch (key) {
    case '1': 
      text = "nice shot";
      keyboard.println(text);
      sendToScreen(text);
      break;
    case '2': 
      text = "Copy";
      keyboard.press(KEY_LEFT_CTRL);
      keyboard.print("c");
      keyboard.releaseAll();
      sendToScreen(text);
      break;
    case '3': 
      text = "Paste";
      keyboard.press(KEY_LEFT_CTRL);
      keyboard.print("v");
      keyboard.releaseAll();
      sendToScreen(text);
      break;
  }
  
  delay(100);
}

// void keyboardExecute(int modePushCounter, char key) {
//       switch (modePushCounter) {                  // switch between keyboard configurations:
//       case 0:                                   //Application Alpha or MODE 0. Example = Every button ends your Zoom call
//       // setColorsMode0();                         //indicate what mode is loaded by changing the key colors
        
//       case 1:                     //  Application Beta or MODE 1 Rocket League Quick Chat (with light reactive keys)
//         // encoderA_Mode2();                         //move mouse
//         // setColorsMode1();
//         if (key) {
//       //Serial.println(key);
//       // ledByKey(key);
//       switch (key) {
//         case '1': keyboard.println("nice shot");
//           break;
//         case '2': keyboard.println("great pass"); 
//           break;
//         case '3': keyboard.println("great save"); 
//           break;
//         case '4': keyboard.println("thanks"); 
//           break;
//         case '5': keyboard.println("i got it"); 
//           break;
//         case '6': keyboard.println("take the shot"); 
//           break;
//         case '7': keyboard.println("defending"); 
//           break;
//         case '8': keyboard.println("go for it"); 
//           break;
//         case '9': keyboard.println("oh no!"); 
//           break;
//         case '0': keyboard.println("no problem");                
//           break;
//         case 'A': keyboard.println("whoops"); 
//           break;
//         case 'B': keyboard.println("#@!%*"); 
//           break;
//       }
//       delay(100); 
//       keyboard.releaseAll();                   // this releases the buttons
//       //delay(100);                                         //delay a bit to hold the color (optional)
//       colorUpdate = 0;                                    //call the color update to change the color back to Mode settings   
//     }
//         break;
//   //====================================================================================================================     
//       case 2:    // Application Delta (some basic Arduino IDE Shortcuts and HotKeys)
//       // encoderA_Mode1();                                  //  tab or shift+tab on the encoder rotation
//       // encoderB_Mode1();                                  // + or - on the encoder rotation
//       // setColorsMode2();                                  // set color layout for this mode
//       if (key) {
//       //Serial.println(key);
//       switch (key) {
//         case '1': Keyboard.press(KEY_LEFT_CTRL);  
//                   Keyboard.print('s');                          //Save
//                   break;
//         case '2': Keyboard.press(KEY_LEFT_CTRL);  
//                   Keyboard.print('r');                          //Verify
//                   break; 
//         case '3': Keyboard.press(KEY_LEFT_CTRL);  
//                   Keyboard.print('u');                          //Upload
//                   break;
//         case '4': Keyboard.press(KEY_LEFT_CTRL);  
//                   Keyboard.press(KEY_LEFT_SHIFT);
//                   Keyboard.print('m');                          //Serial Monitor
//                   break; 
//         case '5': Keyboard.press(KEY_LEFT_CTRL);                //undo
//                   Keyboard.print('z'); 
//                   break;
//         case '6': Keyboard.press(KEY_LEFT_CTRL);                //redo
//                   Keyboard.print('y'); 
//                   break;
//         case '7': Keyboard.press(KEY_LEFT_CTRL);  
//                   Keyboard.press(KEY_LEFT_SHIFT); 
//                   Keyboard.print('g');                          //Find Previous
//                   break; 
//         case '8': Keyboard.press(KEY_LEFT_CTRL);  
//                   Keyboard.print('g');                          //Find Next
//                   break; 
//         case '9': Keyboard.press(KEY_LEFT_CTRL);  
//                   Keyboard.print('c');                          //Copy
//                   break;
//         case '0': Keyboard.press(KEY_LEFT_CTRL);  
//                   Keyboard.print('v');                          //Paste
//                   break;
//         case 'A': Keyboard.press(KEY_LEFT_CTRL);  
//                   Keyboard.print('/');                          //Comment / Uncomment
//                   break;
//         case 'B': Keyboard.press(KEY_LEFT_CTRL);        
//                   Keyboard.print('f');                          // Find
//                   break;

//       }
//       delay(100); 
//       Keyboard.releaseAll(); // this releases the buttons 
//     }
//         break;
        
//       case 3:    //Application 3 MS windows nonsense                                  //Mode 3 text for LCD
//       // setColorsMode3();
//       // encoderA_Mode3();                                  //  Etch-a-sketch mouse up/down in MSpaint
//       // encoderB_Mode3();                                  //  Etch-a-sketch mouse left/right in MSpaint
//       if (key) {
//       //Serial.println(key);
//       switch (key) {
//         case '1': //macro example!!! Windows_Key+R = Run then type "mspaint" and press enter. Opens MS Paint
//           Keyboard.press(KEY_LEFT_GUI); 
//           Keyboard.press('r'); delay(150); 
//           Keyboard.release(KEY_LEFT_GUI); 
//           Keyboard.release('r'); 
//           delay(150); //give your system time to catch up with these android-speed keyboard presses
//           Keyboard.println("mspaint"); 
//           break;
          
//         case '2':  
//         Keyboard.press(KEY_LEFT_GUI); 
//           Keyboard.press(KEY_LEFT_ARROW); delay(150);  //snaps window to left side of screen.
//           break;
//         case '3': 
//           Keyboard.press(KEY_LEFT_GUI); 
//           Keyboard.press(KEY_RIGHT_ARROW); delay(150);  //snaps window to right side of screen.
//           break;
//         case '4':  
//           Keyboard.press(KEY_LEFT_ALT); 
//           Keyboard.press(KEY_F4); delay(150);  //Closes active window
//           break;
          
//         case '5': //macro example: Windows_Key+R = Run then type "calc" and press enter. Opens MS Calculator
//           Keyboard.press(KEY_LEFT_GUI); 
//           Keyboard.press('r'); delay(150); 
//           Keyboard.release(KEY_LEFT_GUI); 
//           Keyboard.release('r'); 
//           delay(150);                 //give your system time to catch up with these android-speed keyboard presses
//           Keyboard.println("calc");
//           break; 
//         case '6': //macro example: Windows_Key+R = Run then type "excel" and press enter. Opens MS Excel
//           Keyboard.press(KEY_LEFT_GUI); 
//           Keyboard.press('r'); delay(150); 
//           Keyboard.release(KEY_LEFT_GUI); 
//           Keyboard.release('r'); 
//           delay(150);                 //give your system time to catch up with these android-speed keyboard presses
//           Keyboard.println("excel"); 
//           break;
          
//         case '7': //macro example: Windows_Key+R = Run then type "winword" and press enter. Opens MS Word
//           Keyboard.press(KEY_LEFT_GUI); 
//           Keyboard.press('r'); delay(150); 
//           Keyboard.release(KEY_LEFT_GUI); 
//           Keyboard.release('r'); 
//           delay(150);                 //give your system time to catch up with these android-speed keyboard presses
//           Keyboard.println("winword"); 
//           break;
//         case '8': //macro that opens chrome and a random wiki page for learning.
//           Keyboard.press(KEY_LEFT_GUI); 
//           Keyboard.press('r'); 
//           Keyboard.release(KEY_LEFT_GUI); 
//           Keyboard.release('r'); 
//           delay(50); //give your system time to catch up with these android-speed keyboard presses
//           Keyboard.println("chrome"); delay(500);
//           Keyboard.println("https://en.wikipedia.org/wiki/Special:Random"); 
//           break; 

//         case '9': //macro that opens Chrome & Rick Rolls you like a chump
//           Keyboard.press(KEY_LEFT_GUI); 
//           Keyboard.press('r'); 
//           Keyboard.release(KEY_LEFT_GUI); 
//           Keyboard.release('r'); 
//           delay(50); //give your system time to catch up with these android-speed keyboard presses
//           Keyboard.println("chrome"); delay(500);
//           Keyboard.println("https://www.youtube.com/watch?v=dQw4w9WgXcQ"); 
//           break;
//         case '0': //macro that opens Chrome and goes to my youtube channel!
//           Keyboard.press(KEY_LEFT_GUI); 
//           Keyboard.press('r'); 
//           Keyboard.release(KEY_LEFT_GUI); 
//           Keyboard.release('r'); 
//           delay(50); //give your system time to catch up with these android-speed keyboard presses
//           Keyboard.println("chrome"); delay(500);
//           Keyboard.println("https://www.youtube.com/c/ryanbatesrbg"); 
//           break;
//         case 'A': //minimize all windows (view desktop)
//           Keyboard.press(KEY_LEFT_GUI); 
//           Keyboard.press('m');  
//           break;
//         case 'B':  
//           Keyboard.press(KEY_LEFT_GUI);  //Opens Snip-it
//           Keyboard.release(KEY_LEFT_GUI); delay(25);
//           Keyboard.println("snip");  //type "snip" and press "return" 
//           break;
//       }
//       delay(100); Keyboard.releaseAll(); // this releases the buttons 
//     }
//         break;
//     }
//     delay(1);  // delay in between reads for stability

// }

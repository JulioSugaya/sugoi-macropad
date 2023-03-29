#include <Adafruit_NeoPixel.h>  //inclusion of Adafruit's NeoPixel (RBG addressable LED) library
// NeoPIxels
#define PIN            2 // Which pin on the Arduino is connected to the NeoPixels?
#define NUMPIXELS      13 // How many NeoPixels are attached to the Arduino? 13 total, but they are address from 0,1,2,...12.

// int colorUpdate = 0;   //setting a flag to only update colors once when the mode is switched. 

// // When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// // Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// // example for more information on possible values.
// Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// void ledByKey(char key) {
//   pixels.setPixelColor(key, pixels.Color(0,150,0));
//   pixels.show();                                      //update the color after the button press
// }

// void setColorsMode0(){
//   if (colorUpdate == 0){                                           // have the neopixels been updated?
//       for(int i=0;i<NUMPIXELS;i++){      //  Red,Green,Blue                      // pixels.Color takes RGB values; range is (0,0,0) to (255,255,255)
//         pixels.setPixelColor(i, pixels.Color(150,   0,    0));      // Moderately bright red color.
//         pixels.show();                                             // This pushes the updated pixel color to the hardware.
//         delay(50); }                                               // Delay for a period of time (in milliseconds).
                                               
//       colorUpdate=1;   }                                           // Mark the color flag so neopixels are no longer updated in the loop
// }


// void setColorsMode1(){
//   if (colorUpdate == 0){                                     // have the neopixels been updated?
//       pixels.setPixelColor(0,  pixels.Color( 80,  0,200));    //gradient mix
//       pixels.setPixelColor(1,  pixels.Color( 10,  0,200));    //gradient mix
//       pixels.setPixelColor(2,  pixels.Color( 20,  0,200));
//       pixels.setPixelColor(3,  pixels.Color( 40,  0,200));
//       pixels.setPixelColor(4,  pixels.Color( 60,  0,200));
//       pixels.setPixelColor(5,  pixels.Color( 80,  0,200));
//       pixels.setPixelColor(6,  pixels.Color(100,  0,200));
//       pixels.setPixelColor(7,  pixels.Color(120,  0,200));
//       pixels.setPixelColor(8,  pixels.Color(140,  0,200));
//       pixels.setPixelColor(9,  pixels.Color(160,  0,200));
//       pixels.setPixelColor(10, pixels.Color(180,  0,200));
//       pixels.setPixelColor(11, pixels.Color(200,  0,200));
//       pixels.setPixelColor(12, pixels.Color(220,  0,200));
//       pixels.show();
//       colorUpdate=1;              }                           // neoPixels have been updated. 
//                                                               // Set the flag to 1; so they are not updated until a Mode change
// }

// void setColorsMode2(){
//   if (colorUpdate == 0){                                      // have the neopixels been updated?
//       pixels.setPixelColor(0, pixels.Color( 51,102,  0));
//       pixels.setPixelColor(1, pixels.Color(  0,  0,150)); 
//       pixels.setPixelColor(2, pixels.Color(  0,150, 0));
//       pixels.setPixelColor(3, pixels.Color(150, 0,  0));
//       pixels.setPixelColor(4, pixels.Color(220,  0,200));
//       pixels.setPixelColor(5, pixels.Color(150,  0,150));
//       pixels.setPixelColor(6, pixels.Color(150,  0,150));
//       pixels.setPixelColor(7, pixels.Color( 80,102,  0));
//       pixels.setPixelColor(8, pixels.Color( 80,102,  0));
//       pixels.setPixelColor(9, pixels.Color(  5, 5, 100));
//       pixels.setPixelColor(10,pixels.Color(  5, 5, 100));
//       pixels.setPixelColor(11, pixels.Color(102, 5,  0));
//       pixels.setPixelColor(12, pixels.Color(80,102,  0));
//       pixels.show(); colorUpdate=1;                  }      // neoPixels have been updated. 
//                                                             // Set the flag to 1; so they are not updated until a Mode change
// }

// void setColorsMode3(){
//   if (colorUpdate == 0){                                     // have the neopixels been updated?
//       pixels.setPixelColor(0, pixels.Color(  0,150,150));   // cyan
//       pixels.setPixelColor(1, pixels.Color(  0,150,  0));   // green
//       pixels.setPixelColor(2, pixels.Color(  0,150,150));   // cyan 
//       pixels.setPixelColor(3, pixels.Color(  0,150,  0));   // green
//       pixels.setPixelColor(4, pixels.Color(  0,150,150));   // cyan
//       pixels.setPixelColor(5, pixels.Color(  0,150,150));   // cyan
//       pixels.setPixelColor(6, pixels.Color(  0,150,  0));   // green
//       pixels.setPixelColor(7, pixels.Color(  0,150,150));   // cyan
//       pixels.setPixelColor(8, pixels.Color(  0,150,  0));   // green
//       pixels.setPixelColor(9, pixels.Color(  0,150,  0));   // green
//       pixels.setPixelColor(10, pixels.Color(  0,150,150));  // cyan 
//       pixels.setPixelColor(11, pixels.Color(  0,150,  0));  // green
//       pixels.setPixelColor(12, pixels.Color(  0,150,150));  // cyan 
//       pixels.show(); colorUpdate=1;                 }       // neoPixels have been updated. 
//                                                             // Set the flag to 1; so they are not updated until a Mode change
// }

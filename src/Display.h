#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 18 - Serial clock out (SCLK)
// pin 23 - Serial data out (DIN)
// pin 19 - Data/Command select (D/C)
// pin 5 - LCD chip select (CS)
// pin 14 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(45, 48, 47, 21, 20);
// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

// #define NUMFLAKES 10
// #define XPOS 0
// #define YPOS 1
// #define DELTAY 2
// #define LOGO16_GLCD_HEIGHT 16
// #define LOGO16_GLCD_WIDTH  16

void displayTest() {
  display.clearDisplay();
  display.display();  
  /* Now let us display some text */
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,1);
  display.setTextSize(2);
  display.println("|SUGOI|");
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(22,20);
  display.println("|MacroPad|");
  display.display();
  delay(1000);
}

void sendToScreen(String text) {
  display.clearDisplay();
  display.display();  
  /* Now let us display some text */
  display.setCursor(0,20);
  display.println(text);
  display.display();
  delay(1000);
  displayTest();
}

void displaySetup(void) {
  display.begin();
  display.setContrast(60);
  display.clearDisplay();
  displayTest();
}
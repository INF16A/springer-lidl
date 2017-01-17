#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
extern "C" {
  #include "Algorithm.h"
}
/*
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
*/


void setup() {
  // put your setup code here, to run once:
  /*u8g2.begin();  
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(0,14,"Hello World!");
  } while ( u8g2.nextPage() );*/
  Serial.begin(115200);

  Serial.println("=== Springerproblem (Team Lidl) ===");
  /*printf("%s", "1. Offener Springerpfad\n");
  printf("%s", "2. Geschlossener Springerpfad\n> ");*/

  int choice = 0;
  //scanf("%d", &choice);
  choice = 1;
  
  bool closed;
  if(choice == 1)
      closed = false;
  else if(choice == 2)
      closed = true;

  //Serial.printf("%s", "Startpunkt im Format %d %d eingeben. Linke obere Ecke ist 0 0\n> ");
  int x, y;
  //scanf("%d %d", &x, &y);
  x=0;
  y=0;
  
  //Serial.printf("%s", "Brettgroesse angeben. Format: %d\n> ");
  int boardSize;
  //scanf("%d", &boardSize);
  boardSize = 8;
  knightsTour(boardSize, x, y, closed);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

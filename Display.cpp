#include "Display.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

void lcdInit(int numCols, int numRows, int cursorCol, int cursorRow) {
  lcd.begin(numCols, numRows);
  lcd.setCursor(cursorCol, cursorRow);
  lcd.print("Ready to connect");
} 

void lcdPrintVals(float w, float velX, float velY) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("W     X     Y");
  lcd.setCursor(0, 1); 
  lcd.print(w);
  lcd.print(" ");
  lcd.print(velX);
  lcd.print(" ");
  lcd.print(velY);
} 

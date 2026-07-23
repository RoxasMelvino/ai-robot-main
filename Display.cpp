#include "Display.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

void lcdInit(int numCols, int numRows, int cursorCol, int cursorRow) {
  lcd.begin(numCols, numRows);
  lcd.setCursor(cursorCol, cursorRow);
  lcd.print("Ready to connect");
} 

void lcdPrintVals(float x, float y, float w) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("X    Y    W");
  lcd.setCursor(0, 1); 
  lcd.print(x);
  lcd.print(" ");
  lcd.print(y);
  lcd.print(" ");
  lcd.print(w);
} 

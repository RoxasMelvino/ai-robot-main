/*
1. Get action space  
2. parse the action space using c strings
3. use the kinematic formulas for proper motor rotation speed 
*/

#include "Display.h"


const int BUFFER = 20; 
char actionSpace[BUFFER];


void setup() {
  Serial.begin(115200);  
  lcdInit(); 
}

void loop() {
  // put your main code here, to run repeatedly:

}


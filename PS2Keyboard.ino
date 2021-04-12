  
/* PS2Keyboard Library
PS2Keyboard allows you to use a keyboard for user input.
Download: Included with the Teensyduino Installer
Latest Developments on Github
Hardware Requirements
PS2 Keyboards are easy to interface, requiring only 5 volt power and 2 signals.

The keyboard's clock signal must connect to an interrupt pin. The data signal may connect to any pin, but do not use the pin with an LED connected to ground because the LED current will interfere with the data signal.

Board Data Pin  Clock Pin (IRQ)
Teensy 3.6
Teensy 3.5
Teensy 3.2
Teensy 3.1
Teensy 3.0  Any
except 13 &
analog-only
pins  Any
except 13 &
analog-only
pins
Teensy LC Any
except 13 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
12, 14, 15, 20, 21, 22, 23
Teensy 2.0  Any, except 11  5, 6, 7, 8
Teensy 1.0  Any 0, 1, 2, 3, 4, 6, 7, 16
Teensy++ 2.0  Any, except 6 0, 1, 2, 3, 18, 19, 36, 37
Teensy++ 1.0  Any 0, 1, 2, 3, 18, 19, 36, 37

Caution: PS2 Keyboards contain pullup resistors to 5 volts which can cause damage to 3.3V only boards like Teensy LC and Teensy 3.6. Use of a level shifter circuit is needed to safely use boards which are not 5 volt tolerant.
Basic Usage
PS2Keyboard keyboard;
Create the keyboard object. Even though you could create multiple objects, only a single PS2 keyboard is supported by this library.

keyboard.begin(DataPin, IRQpin)
Begin the receiving keystrokes. DataPin and IRQpin are the pin numbers where you connected the PS2 keyboard's Data and Clock signals.

keyboard.available()
Check if a keystroke has been received. Returns true if at least one keystroke.

keyboard.read()
Read the next keystroke. -1 is returned if no keystrokes have been received. Keystrokes are returned as ASCII characters. Special keys are mapped to control characters.

Example Program
*/
#include <PS2Keyboard.h>

const int DataPin = 4;
const int IRQpin =  2;

PS2Keyboard keyboard;

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Keyboard Test:");
  Serial.println("And also a test line");
}

void loop() {
  if (keyboard.available()) {
    // Serial.println("Available");
    // read the next key
    char c = keyboard.read();
    
    // check for some of the special keys
    if (c == PS2_ENTER) {
      Serial.println();
    } else if (c == PS2_TAB) {
      Serial.print("[Tab]");
    } else if (c == PS2_ESC) {
      Serial.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      Serial.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      Serial.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      Serial.print("[Left]");
    } else if (c == PS2_RIGHTARROW) {
      Serial.print("[Right]");
    } else if (c == PS2_UPARROW) {
      Serial.print("[Up]");
    } else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");
    } else if (c == PS2_DELETE) {
      Serial.print("[Del]");
    } else {
      
      // otherwise, just print all normal characters
      Serial.print(c);
    }
  }
}

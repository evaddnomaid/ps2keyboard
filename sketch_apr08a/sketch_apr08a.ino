#include <PS2Keyboard.h>
#include <Keyboard.h>

const int DataPin = 20;
const int IRQpin = 19;
const int ledPin = 6;
const int buzzPin = 21;


PS2Keyboard PS2Keyboard;

unsigned long buzz_delay;
uint8_t PS2keysdown[6];
uint8_t PS2keysdown224[6];
int ScancodeToKey[500];
int ScancodeToKey224[500];
int PS2ModifierCtrl = 0;
int PS2ModifierRightCtrl = 0;
int PS2ModifierShift = 0;
int PS2ModifierRightShift = 0;
int PS2ModifierAlt = 0;
int PS2ModifierRightAlt = 0;
int PS2ModifierClover = 0;     // aka flower or windoze
int PS2ModifierRightClover = 0; // Not on ML4100
int caught_a_224 = 0;

// Done: Handle a key being held down (typomatic) which sends the same code again and again

void setup() {

  ScancodeToKey[ 0] = 0;
  ScancodeToKey[ 1] = KEY_F9;
  ScancodeToKey[ 2] = KEY_B;
  ScancodeToKey[ 3] = KEY_F5;
  ScancodeToKey[ 4] = KEY_F3;
  ScancodeToKey[ 5] = KEY_F1;
  ScancodeToKey[ 6] = KEY_F2;
  ScancodeToKey[ 7] = KEY_F12;
  ScancodeToKey[ 8] = KEY_B;
  ScancodeToKey[ 9] = KEY_F10;
  ScancodeToKey[10] = KEY_F8;
  ScancodeToKey[11] = KEY_F6;
  ScancodeToKey[12] = KEY_F4;
  ScancodeToKey[13] = KEY_TAB;
  ScancodeToKey[14] = KEY_TILDE;
  ScancodeToKey[15] = KEY_A;
  ScancodeToKey[16] = KEY_B;
  ScancodeToKey[17] = KEY_A; // Alt left (right when preceeded by 224)
  ScancodeToKey[18] = KEY_B; // left shift
  ScancodeToKey[19] = KEY_A;
  ScancodeToKey[20] = KEY_B; // control
  ScancodeToKey[21] = KEY_Q;
  ScancodeToKey[22] = KEY_1;
  ScancodeToKey[23] = KEY_A;
  ScancodeToKey[24] = KEY_B;
  ScancodeToKey[25] = KEY_A;
  ScancodeToKey[26] = KEY_Z;
  ScancodeToKey[27] = KEY_S;
  ScancodeToKey[28] = KEY_A; // Actually "A"
  ScancodeToKey[29] = KEY_W;
  ScancodeToKey[30] = KEY_2;
  ScancodeToKey[31] = KEY_A;
  ScancodeToKey[32] = KEY_A;
  ScancodeToKey[33] = KEY_C;
  ScancodeToKey[34] = KEY_X;
  ScancodeToKey[35] = KEY_D;
  ScancodeToKey[36] = KEY_E;
  ScancodeToKey[37] = KEY_4;
  ScancodeToKey[38] = KEY_3;
  ScancodeToKey[39] = KEY_A;
  ScancodeToKey[40] = KEY_B;
  ScancodeToKey[41] = KEY_SPACE;  // space
  ScancodeToKey[42] = KEY_V;
  ScancodeToKey[43] = KEY_F;
  ScancodeToKey[44] = KEY_T;
  ScancodeToKey[45] = KEY_R;
  ScancodeToKey[46] = KEY_5;
  ScancodeToKey[47] = KEY_A;
  ScancodeToKey[48] = KEY_B;
  ScancodeToKey[49] = KEY_N;
  ScancodeToKey[50] = KEY_B;  // Actually "B"
  ScancodeToKey[51] = KEY_H;
  ScancodeToKey[52] = KEY_G;
  ScancodeToKey[53] = KEY_Y;
  ScancodeToKey[54] = KEY_6;
  ScancodeToKey[55] = KEY_A;
  ScancodeToKey[56] = KEY_B;
  ScancodeToKey[57] = KEY_A;
  ScancodeToKey[58] = KEY_M;
  ScancodeToKey[59] = KEY_J;
  ScancodeToKey[60] = KEY_U;
  ScancodeToKey[61] = KEY_7;
  ScancodeToKey[62] = KEY_8;
  ScancodeToKey[63] = KEY_A;
  ScancodeToKey[64] = KEY_B;
  ScancodeToKey[65] = KEY_COMMA;
  ScancodeToKey[66] = KEY_K;
  ScancodeToKey[67] = KEY_I;
  ScancodeToKey[68] = KEY_O;
  ScancodeToKey[69] = KEY_0;
  ScancodeToKey[70] = KEY_9;
  ScancodeToKey[71] = KEY_A;
  ScancodeToKey[72] = KEY_B;
  ScancodeToKey[73] = KEY_PERIOD;
  ScancodeToKey[74] = KEY_SLASH;
  ScancodeToKey[75] = KEY_L;
  ScancodeToKey[76] = KEY_SEMICOLON;
  ScancodeToKey[77] = KEY_P;
  ScancodeToKey[78] = KEY_MINUS;
  ScancodeToKey[79] = KEY_A;
  ScancodeToKey[80] = KEY_B;
  ScancodeToKey[81] = KEY_A;
  ScancodeToKey[82] = KEY_QUOTE;
  ScancodeToKey[83] = KEY_A;
  ScancodeToKey[84] = KEY_LEFT_BRACE;
  ScancodeToKey[85] = KEY_EQUAL;
  ScancodeToKey[86] = KEY_B;
  ScancodeToKey[87] = KEY_A;
  ScancodeToKey[88] = KEY_B;      // caps lock (left of A key)
  ScancodeToKey[89] = KEY_A;      // right shift
  ScancodeToKey[90] = KEY_ENTER;  // return
  ScancodeToKey[91] = KEY_RIGHT_BRACE;
  ScancodeToKey[92] = KEY_B;
  ScancodeToKey[93] = KEY_BACKSLASH;
  ScancodeToKey[94] = KEY_B;
  ScancodeToKey[95] = KEY_A;
  ScancodeToKey[96] = KEY_B;
  ScancodeToKey[97] = KEY_A;
  ScancodeToKey[98] = KEY_B;
  ScancodeToKey[99] = KEY_A;
  ScancodeToKey[100] = KEY_B;
  ScancodeToKey[101] = KEY_A;
  ScancodeToKey[102] = KEY_BACKSPACE;
  ScancodeToKey[103] = KEY_A;
  ScancodeToKey[104] = KEY_B;
  ScancodeToKey[105] = KEYPAD_1;
  ScancodeToKey[106] = KEY_B;
  ScancodeToKey[107] = KEYPAD_4;
  ScancodeToKey[108] = KEYPAD_7;
  ScancodeToKey[109] = KEY_A;
  ScancodeToKey[110] = KEY_B;
  ScancodeToKey[111] = KEY_A;
  ScancodeToKey[112] = KEYPAD_0;
  ScancodeToKey[113] = KEYPAD_PERIOD;
  ScancodeToKey[114] = KEYPAD_2;
  ScancodeToKey[115] = KEYPAD_5;
  ScancodeToKey[116] = KEYPAD_6;
  ScancodeToKey[117] = KEYPAD_8;
  ScancodeToKey[118] = KEY_ESC;
  ScancodeToKey[119] = KEY_A;
  ScancodeToKey[120] = KEY_F11;
  ScancodeToKey[121] = KEYPAD_PLUS;
  ScancodeToKey[122] = KEYPAD_3;
  ScancodeToKey[123] = KEYPAD_MINUS;
  ScancodeToKey[124] = KEYPAD_ASTERIX;
  ScancodeToKey[125] = KEYPAD_9;
  ScancodeToKey[126] = KEY_SCROLL_LOCK;
  ScancodeToKey[127] = KEY_A;
  ScancodeToKey[128] = KEY_A;
  ScancodeToKey[129] = KEY_A;
  ScancodeToKey[130] = KEY_A;
  ScancodeToKey[131] = KEY_F7;
  ScancodeToKey[132] = KEY_A;
  ScancodeToKey[133] = KEY_A;
  ScancodeToKey[134] = KEY_A;
  ScancodeToKey[135] = KEY_A;
  ScancodeToKey[136] = KEY_A;
  ScancodeToKey[137] = KEY_A;
  ScancodeToKey[138] = KEY_A;
  ScancodeToKey[139] = KEY_A;
  ScancodeToKey[140] = KEY_A;
  ScancodeToKey[141] = KEY_A;
  ScancodeToKey[142] = KEY_A;
  ScancodeToKey[143] = KEY_A;
  ScancodeToKey[144] = KEY_A;
  ScancodeToKey[145] = KEY_A;
  ScancodeToKey[146] = KEY_A;
  ScancodeToKey[147] = KEY_A;
  ScancodeToKey[148] = KEY_A;
  ScancodeToKey[149] = KEY_A;
  ScancodeToKey[150] = KEY_A;
  ScancodeToKey[151] = KEY_A;
  ScancodeToKey[152] = KEY_A;
  ScancodeToKey[153] = KEY_A;
  ScancodeToKey[154] = KEY_A;
  ScancodeToKey[155] = KEY_A;
  ScancodeToKey[156] = KEY_A;
  ScancodeToKey[157] = KEY_A;
  ScancodeToKey[158] = KEY_A;
  ScancodeToKey[159] = KEY_A;
  ScancodeToKey[160] = KEY_A;
  ScancodeToKey[161] = KEY_A;
  ScancodeToKey[162] = KEY_A;
  ScancodeToKey[163] = KEY_A;
  ScancodeToKey[164] = KEY_A;
  ScancodeToKey[165] = KEY_A;
  ScancodeToKey[166] = KEY_A;
  ScancodeToKey[167] = KEY_A;
  ScancodeToKey[168] = KEY_A;
  ScancodeToKey[169] = KEY_A;
  ScancodeToKey[225] = KEY_X;

  ScancodeToKey224[ 1] = KEY_A;
  ScancodeToKey224[ 2] = KEY_A;
  ScancodeToKey224[ 3] = KEY_A;
  ScancodeToKey224[ 4] = KEY_A;
  ScancodeToKey224[ 5] = KEY_A;
  ScancodeToKey224[ 6] = KEY_A;
  ScancodeToKey224[ 7] = KEY_A;
  ScancodeToKey224[ 8] = KEY_A;
  ScancodeToKey224[ 9] = KEY_A;
  ScancodeToKey224[10] = KEY_A;
  ScancodeToKey224[11] = KEY_A;
  ScancodeToKey224[12] = KEY_A;
  ScancodeToKey224[13] = KEY_A;
  ScancodeToKey224[14] = KEY_A;
  ScancodeToKey224[15] = KEY_A;
  ScancodeToKey224[16] = KEY_A;
  ScancodeToKey224[17] = KEY_A;
  ScancodeToKey224[18] = KEY_A;
  ScancodeToKey224[19] = KEY_A;
  ScancodeToKey224[20] = KEY_A;
  ScancodeToKey224[21] = KEY_A;
  ScancodeToKey224[22] = KEY_A;
  ScancodeToKey224[23] = KEY_A;
  ScancodeToKey224[24] = KEY_A;
  ScancodeToKey224[25] = KEY_A;
  ScancodeToKey224[26] = KEY_A;
  ScancodeToKey224[27] = KEY_A;
  ScancodeToKey224[28] = KEY_A;
  ScancodeToKey224[29] = KEY_A;
  ScancodeToKey224[30] = KEY_A;
  ScancodeToKey224[31] = KEY_A;
  ScancodeToKey224[32] = KEY_A;
  ScancodeToKey224[33] = KEY_A;
  ScancodeToKey224[34] = KEY_A;
  ScancodeToKey224[35] = KEY_A;
  ScancodeToKey224[36] = KEY_A;
  ScancodeToKey224[37] = KEY_A;
  ScancodeToKey224[38] = KEY_A;
  ScancodeToKey224[39] = KEY_A;
  ScancodeToKey224[40] = KEY_A;
  ScancodeToKey224[41] = KEY_A;
  ScancodeToKey224[42] = KEY_A;
  ScancodeToKey224[43] = KEY_A;
  ScancodeToKey224[44] = KEY_A;
  ScancodeToKey224[45] = KEY_A;
  ScancodeToKey224[46] = KEY_A;
  ScancodeToKey224[47] = KEY_A;
  ScancodeToKey224[48] = KEY_A;
  ScancodeToKey224[49] = KEY_A;
  ScancodeToKey224[50] = KEY_A;
  ScancodeToKey224[51] = KEY_A;
  ScancodeToKey224[52] = KEY_A;
  ScancodeToKey224[53] = KEY_A;
  ScancodeToKey224[54] = KEY_A;
  ScancodeToKey224[55] = KEY_A;
  ScancodeToKey224[56] = KEY_A;
  ScancodeToKey224[57] = KEY_A;
  ScancodeToKey224[58] = KEY_A;
  ScancodeToKey224[59] = KEY_A;
  ScancodeToKey224[60] = KEY_A;
  ScancodeToKey224[61] = KEY_A;
  ScancodeToKey224[62] = KEY_A;
  ScancodeToKey224[63] = KEY_A;
  ScancodeToKey224[64] = KEY_A;
  ScancodeToKey224[65] = KEY_A;
  ScancodeToKey224[66] = KEY_A;
  ScancodeToKey224[67] = KEY_A;
  ScancodeToKey224[68] = KEY_A;
  ScancodeToKey224[69] = KEY_A;
  ScancodeToKey224[70] = KEY_A;
  ScancodeToKey224[71] = KEY_A;
  ScancodeToKey224[72] = KEY_A;
  ScancodeToKey224[73] = KEY_A;
  ScancodeToKey224[74] = KEY_A;
  ScancodeToKey224[75] = KEY_A;
  ScancodeToKey224[76] = KEY_A;
  ScancodeToKey224[77] = KEY_A;
  ScancodeToKey224[78] = KEY_A;
  ScancodeToKey224[79] = KEY_A;
  ScancodeToKey224[80] = KEY_A;
  ScancodeToKey224[81] = KEY_A;
  ScancodeToKey224[82] = KEY_A;
  ScancodeToKey224[83] = KEY_A;
  ScancodeToKey224[84] = KEY_A;
  ScancodeToKey224[85] = KEY_A;
  ScancodeToKey224[86] = KEY_A;
  ScancodeToKey224[87] = KEY_A;
  ScancodeToKey224[88] = KEY_A;
  ScancodeToKey224[89] = KEY_A;
  ScancodeToKey224[90] = KEY_A;
  ScancodeToKey224[91] = KEY_A;
  ScancodeToKey224[92] = KEY_A;
  ScancodeToKey224[93] = KEY_A;
  ScancodeToKey224[94] = KEY_A;
  ScancodeToKey224[95] = KEY_A;
  ScancodeToKey224[96] = KEY_A;
  ScancodeToKey224[97] = KEY_A;
  ScancodeToKey224[98] = KEY_A;
  ScancodeToKey224[99] = KEY_A;
  ScancodeToKey224[100] = KEY_A;
  ScancodeToKey224[101] = KEY_A;
  ScancodeToKey224[102] = KEY_A;
  ScancodeToKey224[103] = KEY_A;
  ScancodeToKey224[104] = KEY_A;
  ScancodeToKey224[105] = KEY_END;
  ScancodeToKey224[106] = KEY_A;
  ScancodeToKey224[107] = KEY_LEFT;
  ScancodeToKey224[108] = KEY_A;
  ScancodeToKey224[109] = KEY_A;
  ScancodeToKey224[110] = KEY_A;
  ScancodeToKey224[111] = KEY_A;
  ScancodeToKey224[112] = KEY_INSERT;
  ScancodeToKey224[113] = KEY_DELETE;
  ScancodeToKey224[114] = KEY_DOWN;
  ScancodeToKey224[115] = KEY_A;
  ScancodeToKey224[116] = KEY_RIGHT;
  ScancodeToKey224[117] = KEY_UP;
  ScancodeToKey224[118] = KEY_HOME;
  ScancodeToKey224[119] = KEY_A;
  ScancodeToKey224[120] = KEY_A;
  ScancodeToKey224[121] = KEY_A;
  ScancodeToKey224[122] = KEY_PAGE_DOWN;
  ScancodeToKey224[123] = KEY_A;
  ScancodeToKey224[124] = KEY_A;
  ScancodeToKey224[125] = KEY_PAGE_UP;
  ScancodeToKey224[126] = KEY_A;
  ScancodeToKey224[127] = KEY_A;
  ScancodeToKey224[128] = KEY_A;
  ScancodeToKey224[129] = KEY_A;
  ScancodeToKey224[130] = KEY_A;
  ScancodeToKey224[131] = KEY_A;
  ScancodeToKey224[132] = KEY_A;
  ScancodeToKey224[133] = KEY_A;
  ScancodeToKey224[134] = KEY_A;
  ScancodeToKey224[135] = KEY_A;
  ScancodeToKey224[136] = KEY_A;
  ScancodeToKey224[137] = KEY_A;
  ScancodeToKey224[138] = KEY_A;
  ScancodeToKey224[139] = KEY_A;
  ScancodeToKey224[140] = KEY_A;
  ScancodeToKey224[141] = KEY_A;
  ScancodeToKey224[142] = KEY_A;
  ScancodeToKey224[143] = KEY_A;
  ScancodeToKey224[144] = KEY_A;
  ScancodeToKey224[145] = KEY_A;
  ScancodeToKey224[146] = KEY_A;
  ScancodeToKey224[147] = KEY_A;
  ScancodeToKey224[148] = KEY_A;
  ScancodeToKey224[149] = KEY_A;
  ScancodeToKey224[150] = KEY_A;
  ScancodeToKey224[151] = KEY_A;
  ScancodeToKey224[152] = KEY_A;
  ScancodeToKey224[153] = KEY_A;
  ScancodeToKey224[154] = KEY_A;
  ScancodeToKey224[155] = KEY_A;
  ScancodeToKey224[156] = KEY_A;
  ScancodeToKey224[157] = KEY_A;
  ScancodeToKey224[158] = KEY_A;
  ScancodeToKey224[159] = KEY_A;
  ScancodeToKey224[160] = KEY_A;
  ScancodeToKey224[161] = KEY_A;
  ScancodeToKey224[162] = KEY_A;
  ScancodeToKey224[163] = KEY_A;
  ScancodeToKey224[164] = KEY_A;
  ScancodeToKey224[165] = KEY_A;
  ScancodeToKey224[166] = KEY_A;
  ScancodeToKey224[167] = KEY_A;
  ScancodeToKey224[168] = KEY_A;
  ScancodeToKey224[169] = KEY_A;
  ScancodeToKey224[170] = KEY_A;
  ScancodeToKey224[171] = KEY_A;
  ScancodeToKey224[172] = KEY_A;
  ScancodeToKey224[173] = KEY_A;
  ScancodeToKey224[174] = KEY_A;
  ScancodeToKey224[175] = KEY_A;
  ScancodeToKey224[176] = KEY_A;
  ScancodeToKey224[177] = KEY_A;
  ScancodeToKey224[178] = KEY_A;
  ScancodeToKey224[179] = KEY_A;
  ScancodeToKey224[180] = KEY_A;
  ScancodeToKey224[181] = KEY_A;
  ScancodeToKey224[182] = KEY_A;
  ScancodeToKey224[183] = KEY_A;
  ScancodeToKey224[184] = KEY_A;
  ScancodeToKey224[185] = KEY_A;
  ScancodeToKey224[186] = KEY_A;
  ScancodeToKey224[187] = KEY_A;
  ScancodeToKey224[188] = KEY_A;
  ScancodeToKey224[189] = KEY_A;
  ScancodeToKey224[190] = KEY_A;
  ScancodeToKey224[191] = KEY_A;
  ScancodeToKey224[192] = KEY_A;
  ScancodeToKey224[193] = KEY_A;
  ScancodeToKey224[194] = KEY_A;
  ScancodeToKey224[195] = KEY_A;
  ScancodeToKey224[196] = KEY_A;
  ScancodeToKey224[197] = KEY_A;
  ScancodeToKey224[198] = KEY_A;
  ScancodeToKey224[199] = KEY_A;
  ScancodeToKey224[200] = KEY_A;
  ScancodeToKey224[201] = KEY_A;
  ScancodeToKey224[202] = KEY_A;
  ScancodeToKey224[203] = KEY_A;
  ScancodeToKey224[204] = KEY_A;
  ScancodeToKey224[205] = KEY_A;
  ScancodeToKey224[206] = KEY_A;
  ScancodeToKey224[207] = KEY_A;
  ScancodeToKey224[208] = KEY_A;
  ScancodeToKey224[209] = KEY_A;
  ScancodeToKey224[210] = KEY_A;
  ScancodeToKey224[211] = KEY_A;
  ScancodeToKey224[212] = KEY_A;
  ScancodeToKey224[213] = KEY_A;
  ScancodeToKey224[214] = KEY_A;
  ScancodeToKey224[215] = KEY_A;
  ScancodeToKey224[216] = KEY_A;
  ScancodeToKey224[217] = KEY_A;
  ScancodeToKey224[218] = KEY_A;
  ScancodeToKey224[219] = KEY_A;
  ScancodeToKey224[220] = KEY_A;
  ScancodeToKey224[221] = KEY_A;
  ScancodeToKey224[222] = KEY_A;
  ScancodeToKey224[223] = KEY_A;
  ScancodeToKey224[224] = KEY_A;
  ScancodeToKey224[225] = KEY_A;
  ScancodeToKey224[226] = KEY_A;
  ScancodeToKey224[227] = KEY_A;
  ScancodeToKey224[228] = KEY_A;
  ScancodeToKey224[229] = KEY_A;
  ScancodeToKey224[230] = KEY_A;
  ScancodeToKey224[231] = KEY_A;
  ScancodeToKey224[232] = KEY_A;
  ScancodeToKey224[233] = KEY_A;
  ScancodeToKey224[234] = KEY_A;
  ScancodeToKey224[235] = KEY_A;
  ScancodeToKey224[236] = KEY_A;
  ScancodeToKey224[237] = KEY_A;
  ScancodeToKey224[238] = KEY_A;
  ScancodeToKey224[239] = KEY_A;
  ScancodeToKey224[240] = KEY_A;
  ScancodeToKey224[241] = KEY_A;
  ScancodeToKey224[242] = KEY_A;
  ScancodeToKey224[243] = KEY_A;
  ScancodeToKey224[244] = KEY_A;
  ScancodeToKey224[245] = KEY_A;
  ScancodeToKey224[246] = KEY_A;
  ScancodeToKey224[247] = KEY_A;
  ScancodeToKey224[248] = KEY_A;
  ScancodeToKey224[249] = KEY_A;
  ScancodeToKey224[250] = KEY_A;
  ScancodeToKey224[251] = KEY_A;
  ScancodeToKey224[252] = KEY_A;
  ScancodeToKey224[253] = KEY_A;
  ScancodeToKey224[254] = KEY_A;
  ScancodeToKey224[255] = KEY_A;
  ScancodeToKey224[256] = KEY_A;


  // initialize keys down list
  for (int i = 0; i < 6; i++) {
    PS2keysdown[i] = 0;
    PS2keysdown224[i] = 0;
  }

  pinMode(ledPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  delay(400);
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzPin, HIGH);
  delay(400);
  digitalWrite(buzzPin, LOW);
  
  // put your setup code here, to run once:
  delay(1000);
  PS2Keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Hello for keyboard fun!");

}

void loop() {
  // put your main code here, to run repeatedly:
  if (
    PS2ModifierShift || PS2ModifierRightCtrl || PS2ModifierCtrl || PS2ModifierRightShift || PS2ModifierAlt 
    || PS2keysdown[0] || PS2keysdown[1] || PS2keysdown[2] || PS2keysdown[3] || PS2keysdown[4] || PS2keysdown[5]
    ) {
      digitalWrite(ledPin, HIGH);
      if (buzz_delay + 15000 < millis()) {
        digitalWrite(buzzPin, HIGH);
      }
  }
  else {   digitalWrite(ledPin, LOW); digitalWrite(buzzPin, LOW); buzz_delay = millis(); }
  uint8_t scancode = 0;
  //uint8_t releasekey = 0;
  if ((scancode = PS2Keyboard.readScanCode())) {
    Serial.println(scancode);
    if (scancode == 225) {
      // Pause/Break
      // Skip over the 8 additional codes
      for (int i = 1; i < 9; ++i) {
        while ((scancode = PS2Keyboard.readScanCode()) == 0);
        Serial.println(scancode);
      }
      
    }
    if (scancode == 240) {
      // Key release
      while ((scancode = PS2Keyboard.readScanCode()) == 0);
      if (scancode == 224) {
        caught_a_224 = 1;
        while ((scancode = PS2Keyboard.readScanCode()) == 0);
      }
      Serial.print("Releasing code ");
      Serial.println(scancode);
      if (is_modifier_key(scancode) && !caught_a_224) {
          // Modifier key release
          if (scancode == 18) { PS2ModifierShift = 0; }
          if (scancode == 89) { PS2ModifierRightShift = 0; }
          if (scancode == 20) { PS2ModifierCtrl = 0; }
          if (scancode == 88) { PS2ModifierRightCtrl = 0; }
          if (scancode == 17) { PS2ModifierAlt = 0; }

      } else {
        // Ordinary key release
        state_handle_ordinary_key(scancode, 0);
      }
    } else if (scancode == 224) {
      caught_a_224 = 1;
    } else {
      // Key down
      if (is_modifier_key(scancode) && !caught_a_224) {
        // Modifier key down
        if (scancode == 18) { PS2ModifierShift = 1; }
        if (scancode == 89) { PS2ModifierRightShift = 1; }
        if (scancode == 20) { PS2ModifierCtrl = 1; }
        if (scancode == 88) { PS2ModifierRightCtrl = 1; }
        if (scancode == 17) { PS2ModifierAlt = 1; }
      } else {
        // Ordinary key down
        state_handle_ordinary_key(scancode, 1);
      }
    }
    send_state();
  }
}

void send_state() {
  uint8_t modifier_accumulator = 0;
  if (PS2ModifierShift)      { modifier_accumulator = modifier_accumulator | MODIFIERKEY_SHIFT; }
  if (PS2ModifierRightShift) { modifier_accumulator = modifier_accumulator | MODIFIERKEY_RIGHT_SHIFT; }
  if (PS2ModifierCtrl)       { modifier_accumulator = modifier_accumulator | MODIFIERKEY_CTRL; }
  if (PS2ModifierRightCtrl)  { modifier_accumulator = modifier_accumulator | MODIFIERKEY_RIGHT_CTRL; }
  if (PS2ModifierAlt)        { modifier_accumulator = modifier_accumulator | MODIFIERKEY_ALT; }
  if (PS2ModifierRightAlt)   { modifier_accumulator = modifier_accumulator | MODIFIERKEY_RIGHT_ALT; }


  Keyboard.set_key1(PS2keysdown[0] == 224 ? ScancodeToKey224[PS2keysdown224[0]] : ScancodeToKey[PS2keysdown[0]]);
  Keyboard.set_key2(PS2keysdown[1] == 224 ? ScancodeToKey224[PS2keysdown224[1]] : ScancodeToKey[PS2keysdown[1]]);
  Keyboard.set_key3(PS2keysdown[2] == 224 ? ScancodeToKey224[PS2keysdown224[2]] : ScancodeToKey[PS2keysdown[2]]);
  Keyboard.set_key4(PS2keysdown[3] == 224 ? ScancodeToKey224[PS2keysdown224[3]] : ScancodeToKey[PS2keysdown[3]]);
  Keyboard.set_key5(PS2keysdown[4] == 224 ? ScancodeToKey224[PS2keysdown224[4]] : ScancodeToKey[PS2keysdown[4]]);
  Keyboard.set_key6(PS2keysdown[5] == 224 ? ScancodeToKey224[PS2keysdown224[5]] : ScancodeToKey[PS2keysdown[5]]);

  /*
  Keyboard.set_key2(ScancodeToKey[PS2keysdown[1]]);
  Keyboard.set_key3(ScancodeToKey[PS2keysdown[2]]);
  Keyboard.set_key4(ScancodeToKey[PS2keysdown[3]]);
  Keyboard.set_key5(ScancodeToKey[PS2keysdown[4]]);
  Keyboard.set_key6(ScancodeToKey[PS2keysdown[5]]);
  */
  Keyboard.set_modifier(modifier_accumulator);
  Serial.print("Ready to send standard ");
  for (int i = 0; i < 6; ++i) {
    Serial.print(PS2keysdown[i]);
    Serial.print(" ");
  }
  Serial.print(" >224< ");
  for (int i = 0; i < 6; ++i) {
    Serial.print(PS2keysdown224[i]);
    Serial.print(" ");
  }
  Serial.print("<<< ");
  Serial.print(modifier_accumulator);
  Serial.println(">");
  Keyboard.send_now();
}

void state_handle_ordinary_key(uint8_t scan_code_to_handle, int up_or_down) {
  // 1 for down; 0 for up
  int key_handled = 0;
  int i = 0;
  Serial.print("state_handle_ordinary_key ");
  Serial.print(scan_code_to_handle);
  Serial.print(" ");
  Serial.print(up_or_down);
  Serial.println(" < ");
  i = 0;
  while (i < 6 && !key_handled) {
    if (up_or_down) {
      // key down - add the scancode
      if (caught_a_224) {
        if (PS2keysdown224[i] == 0) {
          PS2keysdown224[i] = scan_code_to_handle;
          PS2keysdown[i] = 224;
          caught_a_224 = 0;
          key_handled = 1;
        } else {
          if (PS2keysdown[i] == 224 && PS2keysdown224[i] == scan_code_to_handle) {
            key_handled = 1;
          }
        }
      } else {
        if (PS2keysdown[i] == 0 || PS2keysdown[i] == scan_code_to_handle) {
          PS2keysdown[i] = scan_code_to_handle;
          key_handled = 1;
        }
      }
      de_dup();
    } else {
      // key up - remove an existing scancode
      if (caught_a_224) {
        if (PS2keysdown224[i] == scan_code_to_handle) {
          PS2keysdown224[i] = 0;
          PS2keysdown[i] = 0;
          caught_a_224 = 0;
          key_handled = 1;
        }
      } else {
        if (PS2keysdown[i] == scan_code_to_handle) {
          PS2keysdown[i] = 0;
          key_handled = 1;
        }
      }
    }
    ++i;
  }
}

void de_dup() {
  for (int i = 0; i < 5; ++i) {
    for (int j = i+1; j < 6; ++j) {
      if (PS2keysdown[i] == PS2keysdown[j] && PS2keysdown224[i] == PS2keysdown224[j]) {
        PS2keysdown[j] = PS2keysdown224[j] = 0;
      }
    }
  }
}

int is_modifier_key(uint8_t scancode_in) {
  if (scancode_in == 18) return scancode_in; // 18 left shift
  if (scancode_in == 89) return scancode_in; // 89 right shift
  if (scancode_in == 17) return scancode_in; // 17 left alt (224 then 17 is right alt)
  if (scancode_in == 20) return scancode_in; // 20 key labeled "control"
  if (scancode_in == 88) return scancode_in; // 88 key labeled "caps lock" - using as right control

  return 0;
}

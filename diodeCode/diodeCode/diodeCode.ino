#define LED_0 13 
  #define LED_1 15 
  #define LED_2 2 
  #define LED_3 0 
  #define LED_4 4 // indicates string in tune 
  #define LED_5 16
  #define LED_6 17
  #define LED_7 5
  #define LED_8 18 
  #define LED_LINE_ARRAY_LENGTH 9
#define LED_g 12 
  #define LED_f 14 
  #define LED_d 27 
  #define LED_e 26 
  #define LED_b 25 
  #define LED_a 33
  #define LED_c 32
  #define LED_dp 19 //rest of the GPIOs on this side is input only
  #define LED_CATHODES_ARRAY_LENGTH 8


char ledLineArray[LED_LINE_ARRAY_LENGTH] = {LED_0, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7, LED_8};
char ledCathodesArray[LED_CATHODES_ARRAY_LENGTH] = {LED_g,LED_f,LED_d,LED_e,LED_b,LED_a,LED_c,LED_dp};


void displayIndicatorDiode(char number = LED_4) {
  for (int i = 0; i < LED_LINE_ARRAY_LENGTH; i++) {digitalWrite(ledLineArray[i], LOW);}
  digitalWrite(ledLineArray[number], HIGH);
}

void clearIndicatorDiode() {for (int i = 0; i < LED_LINE_ARRAY_LENGTH; i++) { digitalWrite(ledLineArray[i], LOW); } }

void clearNoteName() { for (int i = 0; i < LED_CATHODES_ARRAY_LENGTH; i++) { digitalWrite(ledCathodesArray[i],HIGH); } }

void displayNoteName(char noteName, bool dpDiodeOn = false) {

  int noteIdx = 0;
  bool ledLettersArray[7][LED_CATHODES_ARRAY_LENGTH] = {
    {HIGH, LOW, LOW, LOW, HIGH, LOW, HIGH, HIGH}, 
    {LOW, HIGH, LOW, LOW, LOW, HIGH, LOW, HIGH},
    {LOW, LOW, LOW, LOW, HIGH, LOW, HIGH, HIGH},
    {LOW, LOW, HIGH, LOW, HIGH, LOW, HIGH, HIGH},
    {HIGH, LOW, LOW, LOW, HIGH, LOW, LOW, HIGH},
    {LOW, LOW, HIGH, LOW, LOW, LOW, LOW, HIGH},
    {LOW, LOW, LOW, LOW, HIGH, HIGH, LOW, HIGH}
  };

  switch (noteName) {
    case 'c':
    case 'C':
      noteIdx = 0;
      break;
    case 'd':
    case 'D':
      noteIdx = 1;
      break;
    case 'e':
    case 'E':
      noteIdx = 2;
      break;
    case 'f':
    case 'F':
      noteIdx = 3;
      break;
    case 'g':
    case 'G':
      noteIdx = 4;
      break;
    case 'a':
    case 'A':
      noteIdx = 5;
      break;
    case 'b':
    case 'B':
      noteIdx = 6;
      break;
    default:
      break;
  }
  clearNoteName();
  if (dpDiodeOn == true) { digitalWrite(ledCathodesArray[(LED_CATHODES_ARRAY_LENGTH - 1)], LOW); }
  for (int i = 0; i < (LED_CATHODES_ARRAY_LENGTH - 1); i++) { digitalWrite(ledCathodesArray[i],ledLettersArray[noteIdx][i]); }
}


void setup() {
  StartLedDisplay();

}


void loop() {
  
}

void StartLedDisplay() {

  for (int i = 0; i < LED_LINE_ARRAY_LENGTH; i++) { pinMode(ledLineArray[i], OUTPUT); } 
  for (int i = 0; i < LED_CATHODES_ARRAY_LENGTH; i++) { pinMode(ledCathodesArray[i],OUTPUT); } 

  delay(100);
  for(int i = 0; i < LED_LINE_ARRAY_LENGTH; i++) {
  delay(20);
  displayIndicatorDiode(i);
  delay(20);
  }
  for(int i = (LED_LINE_ARRAY_LENGTH-1); i >= 0; i--) { 
    delay(20);
    displayIndicatorDiode(i);
    delay(20);
  }
  clearIndicatorDiode();
  clearNoteName();
}



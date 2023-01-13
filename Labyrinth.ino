const int LIGHT_SENSOR_PIN = A0;  // Arduino pin connected to light sensor's  pin
const int LIGHT_THRESHOLD = 40;
const int LIGHT_DEBOUNCE = 5;

bool touch = false;

int state = 0;
int blinkingState = 0;
unsigned long stateStartMs = 0;

// Define which led is lit (1) for each state
word ledStates[] = {
  //1111111000000000  
  //6543210987654321  <- Led number
  0b0000000000000000, // state 0
  0b0000000000000101, // 1
  0b0000000000000110, // 2
  0b0000000000000100, // 3
  0b0000000000001100, // 4
  0b0000000000110000, // 5
  0b0000000000100000, // 6
  0b0000000001100000, // 7
  0b0000000010100000, // 8
  //1111111000000000
  //6543210987654321  <- Led number
};

// Define the transitions between states
// Each line represent a state and contains the possible next state transition
// Must be 2 value. If only one choice is available, put it twice.
byte transitions[][2] = {
  {3, 6}, // state 0 Can go to state 3 or 6
  {0, 0}, // state 1 End of game, back to state 0
  {1, 1}, // state 2 Can go to state 1 only (twice the same)
  {2, 4}, // state 3
  {0, 0}, // state 4 
  {0, 0}, // state 5
  {5, 7}, // state 6
  {8, 8}, // state 7
  {0, 0}, // state 8
};

byte ledPins[] = {
  2, 3, 4, 5, 6, 7, 8, 9
};
int nLeds = sizeof(ledPins);

//int LEDIndex = 0;

void setup() {
  Serial.begin(9600);
  initAllLEDs();

  initialSequence();

  changeState(0);
}

void loop() {


  int light = analogRead(LIGHT_SENSOR_PIN);  // read the input on analog pin
//  Serial.println(light);
  if (light < LIGHT_THRESHOLD && !touch) {
    // We just touched now
    touch = true;
    Serial.println("DOWN");

    // Blinking state becomes the current state
    if (blinkingState >= 0) {
      changeState(blinkingState);
    }

    //digitalWrite(ledPins[LEDIndex], HIGH); // turn on LED
    //toggleNextLED();

  } else if (light > LIGHT_THRESHOLD + LIGHT_DEBOUNCE && touch) {
    touch = false;
    Serial.println("UP");
    //digitalWrite(ledPins[LEDIndex], LOW);  // turn off LED
  }

  // Update leds
  //Serial.println(String("state: ") + state);
  updateBlinkState();

  word stateLeds = ledStates[state];
  word leds = stateLeds;
  if (blinkingState >= 0) {
    word blinkLeds = ledStates[blinkingState];
    leds |= (millis() % 100) < 50 ? blinkLeds : 0;
    //Serial.print(millis() % 4l);
    //    Serial.print("blinkLeds: ");
    //    Serial.print(blinkLeds, BIN);
  }

  //  Serial.print("  leds: ");
  //  Serial.println(leds, BIN);
  for (int i = 0; i < nLeds; i++) {
    digitalWrite(ledPins[i], (leds >> i) & 1);
  }

  delay(10);
}


void initAllLEDs() {
  for (int i = 0; i < nLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

//void powerOnSelectedLEDOnly(int index) {
//  for (int i = 0; i < nLeds; i++) {
//    if (i == index) {
//      digitalWrite(ledPins[i], HIGH);
//    } else {
//      digitalWrite(ledPins[i], LOW);
//    }
//  }
//}

//void toggleNextLED() {
//  LEDIndex++;
//  if (LEDIndex >= nLeds) {
//    LEDIndex = 0;
//  }
//  Serial.println(String("led ") + LEDIndex + " pin " + ledPins[LEDIndex]);
//  powerOnSelectedLEDOnly(LEDIndex);
//}

void changeState(int newState) {
  state = newState;
  stateStartMs = millis();
  Serial.println(String("STATE ") + state);

  updateBlinkState();
}

int updateBlinkState() {
  int stateTime = millis() - stateStartMs;
  int blinkCount = stateTime / 2000;

  // Next blink state
  byte choice1 = transitions[state][0];
  byte choice2 = transitions[state][1];
//  Serial.println(String("") + choice1 + " " + choice2);
  blinkingState = blinkCount % 2 == 0 ? choice1 : choice2;
  
//  switch (state) {
//    case 0: blinkingState = blinkCount % 2 ? 4 : 1; break;
//  }
}

// Say hello and also a way to test the leds and check their order
void initialSequence() {

  // Turn each led ON in turn
  for (int i = 0; i < nLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay (200);
    digitalWrite(ledPins[i], LOW);
  }

  // Blink them all a few times
  for (int n = 0; n < 4; n++) {

    // all leds ON
    for (int i = 0; i < nLeds; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    delay(200);

    // all leds OFF
    for (int i = 0; i < nLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    delay(50);
  }
}

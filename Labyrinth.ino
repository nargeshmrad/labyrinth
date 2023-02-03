// Uncomment only one of these includes
#include "StatesNarges.h"
//#include "StatesPierre.h"

const int LIGHT_SENSOR_PIN = A0;  // Arduino pin connected to light sensor's  pin
const int LIGHT_THRESHOLD = 10;
const int LIGHT_DEBOUNCE = 5;

bool touch = false;

int state = 0;
int blinkingState = 0;
unsigned long stateStartMs = 0;

void setup() {
  Serial.begin(9600);
  initAllLEDs();

  //initialSequence();

  changeState(0);
}

void loop() {


  int light = analogRead(LIGHT_SENSOR_PIN);  // read the input on analog pin
 Serial.println(light);
  if (light < LIGHT_THRESHOLD && !touch) {
    // We just touched now
    touch = true;
    Serial.println("DOWN");

    // Blinking state becomes the current state
    if (blinkingState >= 0) {
      changeState(blinkingState);
    }

  } else if (light > LIGHT_THRESHOLD + LIGHT_DEBOUNCE && touch) {
    touch = false;
    Serial.println("UP");
  }

  // Update leds
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
    delay (1000);
    digitalWrite(ledPins[i], LOW);
  }

  // Blink them all a few times
  for (int n = 0; n < 4; n++) {

    // all leds ON
    for (int i = 0; i < nLeds; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    delay(100);

    // all leds OFF
    for (int i = 0; i < nLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    delay(50);
  }
}

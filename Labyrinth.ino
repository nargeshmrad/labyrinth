const int LIGHT_SENSOR_PIN = A0;  // Arduino pin connected to light sensor's  pin
const int LIGHT_THRESHOLD = 30;
const int LIGHT_DEBOUNCE = 5;

bool touch = false;
float touchDelay = 0.2;

int state = 0;
int blinkingState = 0;

unsigned long stateStart = 0;

word ledStates[] = {
  //1111111000000000
  //6543210987654321
  0b0000000000000000, // state 0
  0b0000000000000010, // 1
  0b0000000000000011, // 2
  0b0000010000000001, // 3
  0b0000000000010001, // 4
  //1111111000000000
  //6543210987654321
};


byte ledPins[] = {
  2, 3, 4, 5, 6, 7, 8, 9
};

int nLeds = sizeof(ledPins);

int LEDIndex = 0;

void setup() {
  Serial.begin(9600);
  initAllLEDs();

  initialSequence();

  changeState(0);
}

void loop() {


  int light = analogRead(LIGHT_SENSOR_PIN);  // read the input on analog pin
  //Serial.println(light);
  if (light < LIGHT_THRESHOLD && !touch) {
    // We just touched now
    touch = true;
    Serial.println("DOWN");
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

void powerOnSelectedLEDOnly(int index) {
  for (int i = 0; i < nLeds; i++) {
    if (i == index) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}

void toggleNextLED() {
  LEDIndex++;
  if (LEDIndex >= nLeds) {
    LEDIndex = 0;
  }
  Serial.println(String("led ") + LEDIndex + " pin " + ledPins[LEDIndex]);
  powerOnSelectedLEDOnly(LEDIndex);
}

void changeState(int newState) {
  state = newState;
  stateStart = millis();

  updateBlinkState();
}

int updateBlinkState() {
  int stateTime = millis() - stateStart;
  int blinkCount = stateTime / 2000;

  // Next blink state
  switch (state) {
    case 0: blinkingState = blinkCount % 2 ? 4 : 1; break;
  }
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
    delay(400);

    // all leds OFF
    for (int i = 0; i < nLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    delay(100);
  }
}

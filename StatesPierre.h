
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

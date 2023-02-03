// Narges States

// Define which led is lit (1) for each state
word ledStates[] = {
  //1111111000000000  
  //6543210987654321  <- Led number
  0b0000000000000000, // state 0
  0b0000000000000001, // 1
  0b0000000000000011, // 2
  0b0000010000000001, // 3
  0b0000000000010001, // 4
  0b0000000000100001, // 5
  0b0000000001000001, // 6
  0b0000000010000001, // 7
  0b0000000100000001, // 8
  0b0000001000000001, // 9
  0b0000100000000001, // 10
  0b0100000000000001, // 11
  0b0001000000000001, // 12
  0b0010000000000001, // 13
  0b0000000000100000, // 14
  0b0000000001100000, // 15
  0b0000000010100000, // 16
  0b0000000100100000, // 17
  0b0000001000100000, // 18
  0b0000000000110000, // 19
  0b0000010000100000, // 20
  0b0000000000100010, // 21
  0b0000000000100100, // 22
  0b0000000000101000, // 23
  //1111111000000000
  //6543210987654321  <- Led number
};

// Define the transitions between states
// Each line represent a state and contains the possible next state transition
// Must be 2 value. If only one choice is available, put it twice.
byte transitions[][2] = {
  {1, 14}, // state 0 Can go to state 1 or 14
  {2, 10}, // state 1 
  {3, 3}, // state 2 Can go to state 3 only (twice the same)
  {4, 4}, // state 3 Can go to state 4 only (twice the same)
  {5, 5}, // state 4 
  {6, 6}, // state 5
  {7, 7}, // state 6
  {8, 8}, // state 7
  {9, 9}, // state 8
  {0, 0}, // state 9 End of game, back to state 0
  {11, 11}, // state 10
  {12, 12}, // state 11
  {13, 13}, // state 12
  {0, 0}, // state 13 End of game, back to state 0
  {15, 19}, // state 14
  {16, 16}, // state 15
  {17, 17}, // state 16
  {18, 18}, // state 17
  {0, 0}, // state 18 End of game, back to state 0
  {20, 20}, // state 19
  {21, 21}, // state 20
  {22, 22}, // state 21
  {23, 23}, // state 22
  {0, 0}, // state 23 End of game, back to state 0
};

byte ledPins[] = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 40, 22,  24 , 26
};
int nLeds = sizeof(ledPins);

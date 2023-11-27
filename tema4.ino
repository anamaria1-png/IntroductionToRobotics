
  const int pinA = 12;
  const int pinB = 10;
  const int pinC = 9;
  const int pinD = 8;
const int pinE = 7;
const int pinF = 6;
  const int pinG = 5;
  const int pinDP = 4;
const int segSize = 8;
  int x = 0;
  int y = 0; 


int s[segSize] = {pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP};const int pinSW = 2; 
  const int pinX = A0; 
  const int pinY = A1; 

//joystick
int c = 1;
int v = 0;
int h= 0;

 const int readingMinThreshold = 250;
 const int readingMaxThreshold = 700;
const int resetMinThreshold = 200;
  const int resetMaxThreshold = 500;
const int centerReferenceValue = 550;

const int blinkInterval = 100;
long lastBlinkToggleTime = 0;
long currentBlinkToggleTime = 0;




int blink[segSize] = {0, 0, 0, 0, 0, 0, 0, 0};
int position = 7; 
int blinkPosition = 7;
int state[segSize] = {0, 0, 0, 0, 0, 0, 0, 0};


 bool press = false; //button press 
const long debounceDelay = 20;
const long longPushDuration = 2500;
bool longPress = false; // long button press 

bool ledState = LOW; // Current state of the LED (ON/OFF)
 bool buttonState = HIGH; // previous state of the button
 bool buttonReading = HIGH; // current reading from the button pin
 long lastDebounceTime = 0; // Keeps track of the last time the button was pressed
 bool startCounter = false; // start debounce counter

void setup() {
  pinMode(pinSW, INPUT_PULLUP); //  pull-up resistor on the push-button 
  
  for (int i = 0; i < segSize; i++) pinMode(s[i], OUTPUT);
  
  for (int i = 0; i < segSize; i++) 
    {
    state[i] = 0;
    blink[i] = 0;
  }
  attachInterrupt(digitalPinToInterrupt(pinSW), handleInterrupt, FALLING);
}

void loop() {
  input();
  move();
  updateBlink(position);
}



void detect() {
  if (press || longPress) {
    if (shouldStartCounter) {
      lastDebounceTime = millis();
      startCounter = false;
    }

    if ((millis() - lastDebounceTime) > debounceDelay && press) {
      buttonReading = digitalRead(pinSW);

      if (buttonReading != buttonState) {
        if (buttonReading == LOW) {
          state[position] = !state[position];
        }
      }

      press = false;
    }

    if (millis() - lastDebounceTime > longPushDuration) {
      buttonReading = digitalRead(pinSW);

      if (buttonReading != buttonState) {
        if (buttonReading == LOW) {
          Serial.println(6666);
          for (int i = 0; i < segSize; i++) {
            state[i] = 0;
            blink[i] = state[i];
          }
          position = 7;
        }
      }

      longPress = false;
    }
  }
}


  // Directional readings:
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  
  if (x> readingMaxThreshold && abs(x-centerReferenceValue) > abs(yValue-centerReferenceValue) && c == 1) {
    v= 1;
    c = 0;
  }
  if (x < readingMinThreshold && abs(x-centerReferenceValue) > abs(y-centerReferenceValue) && c == 1) {
    v = -1;
    c = 0;
  }
  if (y> readingMaxThreshold && abs(y-centerReferenceValue) > abs(x-centerReferenceValue) && c == 1) {
    h = 1;
    c = 0;
  }
  if (y < readingMinThreshold && abs(y-centerReferenceValue) > abs(x-centerReferenceValue) && c == 1) {
    h = -1;
    c = 0;
  }
  if (x >= readingMinThreshold && x <= readingMaxThreshold && y >= readingMinThreshold && y <= readingMaxThreshold) c = 1;
 
  return;
}



  void move() {
  switch (position) { // current position is:
  case 0: // a
    if (h == 1) {
        position = 1; // b
    } else if (h == -1) {
        position = 5; // f
    } else if (v == -1) {
        position = 6; // g
    }
    break; // break position 0 case

  case 1: // b
    if (h == -1) {
        position = 5; // f
    } else if (v == 1) {
        position = 0; // a
    } else if (v == -1) {
        position = 6; // g
    }
    break; // break position 1 case


 case 2: // c
    if (h == 1) {
        position = 7; // dp
    } else if (h == -1) {
        position = 4; // e
    } else if (v == 1) {
        position = 6; // g
    } else if (v == -1) {
        position = 3; // d
    }
    break; // break position 2 case

case 3: // d
    if (h == 1) {
        position = 2; // go to c
    } else if (h == -1) {
        position = 4; // go to e
    } else if (v == 1) {
        position = 6; // go to g
    }
    break; // break position 3 case


  case 4: // e
    if (h == 1) {
        position = 2; // go to c
    } else if (v == 1) {
        position = 6; // go to g
    } else if (v == -1) {
        position = 3; // go to d
    }
    break; // break position 4 case


case 5: // f
    if (h == 1) {
        position = 1; // go to b
    } else if (v == 1) {
        position = 0; // go to a
    } else if (v == -1) {
        position = 6; // go to g
    }
    break; // break position 5 case

case 6: // g
    if (v == 1) {
        position = 0; // go to a
    } else if (v == -1) {
        position = 3; // go to d
    }
    break; // break position 6 case


  case 7:
    if (h == -1) {
        position = 2; // c
    }
    break; // break position 7 case


    if (position != blinkPosition) {lastBlinkToggleTime = millis();
    blink[blinkPosition] = state[blinkPosition];    // set the old blinking led 
  }
  v= 0;
  h= 0;
 
}


  void updateBlink(int newBlinkPosition) {
  currentBlinkToggleTime = millis();
  if (currentBlinkToggleTime - lastBlinkToggleTime > blinkInterval) 

    {
    lastBlinkToggleTime = currentBlinkToggleTime; 
    blink[newBlinkPosition] = !blink[newBlinkPosition];
     }
     

    blinkPosition = newBlinkPosition;
    for (int i = 0; i < segSize; i++)digitalWrite(s[i], blink[i]);
 
  return;
}

void write() {
  for (int i = 0; i < segSize; i++)digitalWrite(s[i], state[i]); 
 
}


// ISR
  void interrupt() {
  press = true; //  button press 
  longPress = true; //  long button press 
  startCounter = true; //  start the debounce counter
}

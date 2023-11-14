#include <Arduino.h>

// Define pin numbers for the 7-segment display
int displayPins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

// Define pin numbers for the buttons
int buttonStart = A0;
int buttonReset = A1;
int buttonLap = A2;

// Variables to track stopwatch state
unsigned long startTime;
unsigned long elapsedTime;
bool isRunning = false;
bool isPaused = false;
bool inResetMode = false;

// Variables for lap functionality
unsigned long lapTimes[4];
int currentLapIndex = 0;

void setup() {
  // Initialize 7-segment display pins as outputs
  for (int i = 0; i < 8; i++) {
    pinMode(displayPins[i], OUTPUT);
  }

  // Initialize button pins as inputs with pull-up resistors
  pinMode(buttonStart, INPUT_PULLUP);
  pinMode(buttonReset, INPUT_PULLUP);
  pinMode(buttonLap, INPUT_PULLUP);

  // Initialize serial communication (for debugging)
  Serial.begin(9600);

  // Initialize lap times to 0
  for (int i = 0; i < 4; i++) {
    lapTimes[i] = 0;
  }

  // Display initial value on the 7-segment display
  displayTime(0);
}

void loop() {
  // Read button states
  bool startState = digitalRead(buttonStart);
  bool resetState = digitalRead(buttonReset);
  bool lapState = digitalRead(buttonLap);

  // Handle Start/Pause button
  if (startState == LOW) {
    if (!isRunning && !inResetMode) {
      // Start the stopwatch
      startTime = millis() - elapsedTime;
      isRunning = true;
    } else if (isRunning && !inResetMode) {
      // Pause the stopwatch
      isRunning = false;
      elapsedTime = millis() - startTime;
    }
    delay(200); // Debounce delay
  }

  // Handle Lap button
  if (lapState == LOW && isRunning && !isPaused && !inResetMode) {
    // Save lap time
    lapTimes[currentLapIndex] = elapsedTime;
    currentLapIndex = (currentLapIndex + 1) % 4;
    delay(200); // Debounce delay
  }

  // Handle Reset button
  if (resetState == LOW) {
    if (!isRunning && !inResetMode) {
      // Reset the stopwatch and laps if not in running or reset mode
      elapsedTime = 0;
      currentLapIndex = 0;
      displayTime(elapsedTime);
    } else if (isRunning && !inResetMode) {
      // Enter reset mode
      inResetMode = true;
      delay(200); // Debounce delay
    } else if (isRunning && inResetMode) {
      // Exit reset mode if in running and reset mode
      inResetMode = false;
      delay(200); // Debounce delay
    }
  }

  // Update the display
  if (isRunning && !isPaused && !inResetMode) {
    elapsedTime = millis() - startTime;
    displayTime(elapsedTime);
  } else if (!isRunning && !isPaused && inResetMode) {
    // Display reset value during reset mode
    displayTime(0);
  } else if (!isRunning && !isPaused && !inResetMode) {
    // Display lap time during lap viewing mode
    displayTime(lapTimes[currentLapIndex]);
  }
}

// Function to display time on the 4-digit 7-segment display
void displayTime(unsigned long time) {
  // Convert time to tenths of a second
  int tenths = (time / 100) % 10;
  int seconds = (time / 1000) % 60;
  int minutes = (time / 60000) % 60;
  int hours = (time / 3600000) % 24;

  // Display on the 7-segment display (assuming common cathode)
  // Code to display on 4-digit 7-segment display goes here...

  // Example: Display tenths on the rightmost digit
  digitalWrite(displayPins[0], (tenths & 0b0001));
  digitalWrite(displayPins[1], (tenths & 0b0010) >> 1);
  digitalWrite(displayPins[2], (tenths & 0b0100) >> 2);
  digitalWrite(displayPins[3], (tenths & 0b1000) >> 3);

  // Update other digits accordingly (minutes, seconds, etc.)
}

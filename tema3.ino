const int elevatorLeds[] = {2,9,4};  // Pinurile pentru LED-urile de la fiecare etaj
const int elevatorButtons[] = {7,8,9};  // Pinurile butoanelor de la fiecare etaj
const int elevatorOperationLed = 5;  // Pinul LED-ului de operare
const int elevatorBuzzerPin = 6;  // Pinul buzzerului

int currentFloor = 0;  // Etajul curent
int targetFloor = -1;  // Etajul țintă
int nextFloor = -1;  // Următorul etaj
bool isMoving = false;  // Indicator dacă liftul se mișcă

unsigned long fadeStartTime;  // Timpul de începere a efectului de fading
unsigned long lastButtonPressTime;  // Timpul ultimului apăsare a butonului
unsigned long lastBlinkTime;  // Timpul ultimei blink-uri

const long buttonDebounceTime = 50;  // Timp de debouncing pentru butoane
const long blinkInterval = 1500;  // Intervalul de blink pentru LED-ul de operare
const int fadeDuration = 1000;  // Durata efectului de fading

void setup() {
  // Inițializarea pinurilor
  for (int i = 0; i < 3; i++) {
    pinMode(elevatorLeds[i], OUTPUT);
    analogWrite(elevatorLeds[i], (i == currentFloor) ? 255 : 0);
    pinMode(elevatorButtons[i], INPUT_PULLUP);
  }
  pinMode(elevatorOperationLed, OUTPUT);
  digitalWrite(elevatorOperationLed, HIGH);
  pinMode(elevatorBuzzerPin, OUTPUT);
}

void loop() {
  // Verificarea butoanelor pentru selectarea etajului
  for (int i = 0; i < 3; i++) {
    if (digitalRead(elevatorButtons[i]) == LOW && millis() - lastButtonPressTime > buttonDebounceTime) {
      lastButtonPressTime = millis();
      if (!isMoving) {
        targetFloor = i;
        if (currentFloor < targetFloor) {
          nextFloor = currentFloor + 1;
        } else if (currentFloor > targetFloor) {
          nextFloor = currentFloor - 1;
        }
        isMoving = true;
        tone(elevatorBuzzerPin, 400);
        fadeStartTime = millis();
      }
    }
  }

  if (isMoving) {
    // Efectul de fading pentru LED-uri
    unsigned long fadeElapsedTime = millis() - fadeStartTime;
    int currentBrightness = 255 - map(fadeElapsedTime, 0, fadeDuration, 0, 255);
    int nextBrightness = map(fadeElapsedTime, 0, fadeDuration, 0, 255);
    analogWrite(elevatorLeds[currentFloor], currentBrightness);
    analogWrite(elevatorLeds[nextFloor], nextBrightness);
    
    if (fadeElapsedTime >= fadeDuration) {
      noTone(elevatorBuzzerPin);
      currentFloor = nextFloor;
      if (nextFloor == targetFloor) {
        isMoving = false;
        digitalWrite(elevatorOperationLed, HIGH);
        tone(elevatorBuzzerPin, 1000, 200);
      } else {
        if (currentFloor < targetFloor) {
          nextFloor = currentFloor + 1;
        } else {
          nextFloor = currentFloor - 1;
        }
        fadeStartTime = millis();
      }
    }
  }

  if (isMoving && millis() - lastBlinkTime >= blinkInterval) {
    // Blink pentru LED-ul de operare în timp ce liftul se mișcă
    digitalWrite(elevatorOperationLed, !digitalRead(elevatorOperationLed));
    lastBlinkTime = millis();
  }
}

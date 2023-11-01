
const int LEDs[] = {2, 3, 4}; // Pinii pentru LED-urile etajelor
const int operationLED = 5; // Pin pentru LED-ul de stare a ascensorului
const int buzzerPin = 6; // Pin pentru buzzer

int currentFloor = 0; // Etajul curent

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(LEDs[i], OUTPUT);
    digitalWrite(LEDs[i], LOW); // Stingem LED-urile la pornire
  }
  pinMode(operationLED, OUTPUT);
  digitalWrite(operationLED, LOW); // Stingem LED-ul de stare a ascensorului la pornire
  pinMode(buzzerPin, OUTPUT); // Configurăm pinul buzzer-ului ca ieșire
}

void loop() {
  for (int i = 0; i < 3; i++) {
    if (digitalRead(i + 6) == LOW) { // Butonul de etaj va fi conectat la pinii 6, 7, 8
      goToFloor(i);
    }
  }
  // Alte acțiuni sau verificări pot fi adăugate aici
}

void goToFloor(int floor) {
  // Opriți LED-ul etajului curent
  digitalWrite(LEDs[currentFloor], LOW);
  // Mutare la noul etaj
  currentFloor = floor;
  // Aprindeți LED-ul pentru noul etaj
  digitalWrite(LEDs[currentFloor], HIGH);

  // Activează LED-ul de stare a ascensorului pentru a indica mișcarea
  digitalWrite(operationLED, HIGH);

  // Sunetul de semnalizare (folosind un buzzer)
  tone(buzzerPin, 1000, 100); // Sunet de 1000 Hz pentru 0.1 secunde

  // Adăugați o pauză pentru a simula mișcarea ascensorului
  delay(2000); // Pauza de 2 secunde pentru mișcare simulată

  // Oprește LED-ul de stare a ascensorului pentru a indica staționarea
  digitalWrite(operationLED, LOW);

  // Sunetul de semnalizare pentru uși (folosind un buzzer)
  tone(buzzerPin, 1500, 100); // Sunet diferit pentru uși
  delay(1000); // Pauza de 1 secundă pentru uși simulate
}


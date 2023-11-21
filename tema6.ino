const int TRIGGER_PIN = 9; // Pinul TRIG
const int ECHO_PIN = 10;   // Pinul ECHO
const int LED_PIN = 11;    // Pinul pentru LED-ul RGB

boolean newData = false;
int thresholdDistance = 0; // Variabila pentru valoarea pragului

int ldrPin = A0; // Pinul analogic la care este conectat senzorul LDR
int ldrThresholdMax = 1023; // Valoarea maximă a pragului pentru senzorul LDR

bool isThresholdSet = false; // Variabilă pentru a ști dacă pragul a fost setat


void setup() {
  Serial.begin(9600);
  // Inițializări pentru pinii și serial
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}


int parseInt(){
  int x = Serial.parseInt();
  while (Serial.available()) { 
      Serial.read();
  }
  return x;
}


int menuState = 0; 

void loop() {
    if(menuState == 0){
      Serial.println("1. Sensor Settings");
      Serial.println("2. Reset Logger Data");

      while(!Serial.available());
      
      int option = parseInt();
      
      if(option == 1){
        menuState = 1;
      } else if(option == 2){
        menuState = 2;
      } else {
        Serial.println("Invalid choice. Please enter a valid option.");
      }
    } else if(menuState == 1){
      Serial.println("    1. Ultrasonic Sensor Sampling Interval");
      Serial.println("    2. Ultrasonic Sensor Alert Threshold");
      Serial.println("    3. LDR Alert Threshold");
      Serial.println("    4. Back");
      
      while(!Serial.available());

      int option = parseInt();

      if(option == 1){
        menuState = 3;
      } else if(option == 2){
        menuState = 4;
      } else if(option == 3){
        menuState = 5;
      } else if(option == 4){
        menuState = 0;
      } else {
        Serial.println("Invalid choice. Please enter a valid option.");
      }
    } else if(menuState == 2){
      Serial.println("Are you sure you want to delete all data?");
      Serial.println("1. Yes");
      Serial.println("2. No");

      while(!Serial.available());

      int option = parseInt();

      if (option == 1) {
        Serial.println("Data has been deleted.");
        menuState = 0;
      } else if (option == 2) {
        Serial.println("Data deletion canceled.");
        menuState = 0;
      } else {
        Serial.println("Invalid choice. Please enter 1 for Yes or 2 for No.");
        menuState = 2;
      }
    } else if(menuState == 3){
      Serial.println("Please enter the threshold distance value:");
      
      while(!Serial.available());

      thresholdDistance = parseInt(); // Citeste valoarea numerica de la serial

      // Dacă valoarea este validă (non-zero), afișează pragul și continuă cu monitorizarea
      if (thresholdDistance != 0) {
        Serial.print("Threshold distance set to: ");
        Serial.println(thresholdDistance);
        Serial.println("Monitoring started...");
        menuState = 1;
      } else {
        Serial.println("Please enter a valid number.");
      }
      // Restul codului pentru monitorizarea distanței și acțiunile ulterioare...
    } else if (menuState == 4) {
      Serial.println("Please enter the threshold distance value:");

      while(!Serial.available());

      thresholdDistance = parseInt(); // Citeste valoarea numerica de la serial

      // Dacă valoarea este validă (non-zero), afișează pragul și continuă cu monitorizarea
      if (thresholdDistance != 0) {
        Serial.print("Threshold distance set to: ");
        Serial.println(thresholdDistance);
        Serial.println("Monitoring started...");
        menuState = 1;
      } else {
        Serial.println("Please enter a valid number.");
      }
    } else if (menuState == 5) {
        Serial.println("Enter the LDR threshold value:");

        while(!Serial.available());

        int userThreshold = parseInt(); // Citirea valorii introduse de utilizator

        // Verificare și actualizare doar dacă valoarea introdusă este sub pragul maxim
        if (userThreshold < ldrThresholdMax && userThreshold > 0) {
          ldrThresholdMax = userThreshold; // Actualizare pragului maxim
          isThresholdSet = true; // Setare că pragul a fost setat

          // Confirmare că pragul maxim a fost setat
          Serial.print("LDR threshold set to: ");
          Serial.println(ldrThresholdMax);
          menuState = 1;
        } else {
          Serial.println("Error! New threshold exceeds or equals the maximum threshold or is below 0.");
        }

        // Așteptare pentru a reveni la introducerea valorii
        delay(1000);
        if (!isThresholdSet) {
          Serial.println("Enter the LDR threshold value:");
        } 

    }
}




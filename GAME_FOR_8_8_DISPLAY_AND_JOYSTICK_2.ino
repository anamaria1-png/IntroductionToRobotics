#include "LedControl.h" // need the library


// Max7219  Display pin Declarations
#define dinPin  12 // pin 12 is connected to the MAX7219 pin 1
#define clockPin  11 // pin 11 is connected to the CLK pin 13
#define loadPin  10 // pin 10 is connected to LOAD pin 12

#define matrixSize  8 // 8x8 as we are only using 1 MAX7219 with single 8x8
byte matrixBrightness = 2;  // Set Brightness of your display
byte MaxRows = 7 ;  // Rows range form 0 - 7 ; 
byte MaxColumns = 7 ;  // Columns range form 0 - 7 ; 

// Joystick Pin Declarations
#define Joystick_Vertical A0 
#define Joystick_Horizontal A1 
#define Joystick_Button A2

// A function that moves the characters on the map according to the passed commands
void CharacterMovement ( String  ,  unsigned char &  ,  unsigned char &  ) ; 
 
// Create an LEDcontrol object which is used to interface and set the Max7219 run 8x8 display using  SPI communication  (handled by the class)
LedControl LC = LedControl(dinPin, clockPin, loadPin, 1); //DIN, CLK, LOAD, No. DRIVER

/* A structure to contain key methods and fields for a character like coloumn and row position and a function to move it in space
Allows for creation of many characters in the game while reusing the same code */

 typedef struct Characters {
    unsigned char RowPosition = 0 ;  
    unsigned char ColumnPosition = 0 ;
    void (*Movementfunction) ( String ,   unsigned char &   , unsigned char & ) ; 
    
    unsigned long pastChronos = 0  ;    // Store the last time the blink function was run 
    unsigned long currentChronos = 0 ; //  Store the millis ( ) time at the current instance in time
    uint8_t Blinkrate = 0 ;  // Set the blink rate of the particular character
 
  }  Characters ; 

 // Create two objects, one for enemy and the player each
   Characters Enemy   =  Characters {  } ; 
   Characters Player  =  Characters {  } ; 
   Characters Bomb  =  Characters {  } ; 


// A 2D array that is used to set obstacles on the 8x8 map space
  byte ObstacleMatrix[matrixSize][matrixSize] = {
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 1, 0},
  {0, 0, 1, 0, 0, 0, 1, 0},
  {0, 0, 1, 0, 0, 0, 1, 0}
    };

 // Variables to interface and hold timer values in order to debounce Joystick Button
  unsigned long CurrentChronos = 0 ; 
  unsigned long PastChronos = 0 ; 
  const int debounceInterval  = 50 ; // set in ms the time the push button must maintain its state to be considered a legitimate press
  bool currentReading = HIGH ; 
  bool PastReading  = HIGH ; 
  bool ButtonState = HIGH ; 

void setup() {
  // put your setup code here, to run once:
  
 Serial.begin(115200); 

  
   LC.shutdown(0, false); // turn off power saving, enables display
   LC.setIntensity(0, matrixBrightness);   
   LC.clearDisplay(0);// clear screen

   CreateObstacles ( ) ;  // Creates obstacles on the map
  
  // Assign the created Character movement function to both the enemy and player objects  
  Enemy.Movementfunction   =   *CharacterMovement ; 
  Player.Movementfunction   =   *CharacterMovement ; 

  // Set the blinkrates in ms of all the characters
   Enemy.Blinkrate =  30 ; 
   Player.Blinkrate =  30 ; 
 
 // Create and sets enemy and player character at their defined default position ( 4 , 0 )  and ( 4 , 7 )
  Enemy.Movementfunction( "DEFAULT_ENEMY" , Enemy.RowPosition ,  Enemy.ColumnPosition  ) ; 
  Player.Movementfunction( "DEFAULT_PLAYER" , Player.RowPosition ,  Player.ColumnPosition  ) ; 
 
 // Configure Joystick Pins as Input
   pinMode( Joystick_Vertical , INPUT );
   pinMode( Joystick_Horizontal , INPUT );
   pinMode( Joystick_Button , INPUT_PULLUP );

}

void loop() {
  // put your main code here, to run repeatedly:
 // delay (5 ) ; 
  
     String MoveCommand  = JoystickInterface (  ) ; 
   
        Enemy.Movementfunction(MoveCommand, Enemy.RowPosition ,  Enemy.ColumnPosition  ) ; 
     
         Player.Movementfunction(MoveCommand, Player.RowPosition ,  Player.ColumnPosition  ) ; 
     
     
        BlinkCharacter ( Enemy ) ; 
        BlinkCharacter ( Player ) ; 


   

  //    delay (500) ;  

  //    Enemy.Movementfunction( "UP" , Enemy.RowPosition ,  Enemy.ColumnPosition  ) ; 
   
  //       delay (500) ;   

  //   Enemy.Movementfunction( "UP" , Enemy.RowPosition ,  Enemy.ColumnPosition  ) ; 

  //  delay (500) ;  
    
  // Enemy.Movementfunction( "UP" , Enemy.RowPosition ,  Enemy.ColumnPosition  ) ; 
 
  //   delay (500) ;   



  
  //   Player.Movementfunction( "UP" , Player.RowPosition ,  Player.ColumnPosition  ) ; 
 

  //       delay (500) ;   

  //   Player.Movementfunction( "UP", Player.RowPosition ,  Player.ColumnPosition  ) ; 
 

  //  delay (500) ;  
 
  //   Player.Movementfunction( "UP" , Player.RowPosition ,  Player.ColumnPosition  ) ; 
 

  //   delay (500) ;   


  // Enemy.Movementfunction( "DOWN" , &Enemy.RowPosition ,  &Enemy.ColumnPosition  ) ; 
  
  //     delay (500) ;   

  //    Enemy.Movementfunction( "DOWN" , &Enemy.RowPosition ,  &Enemy.ColumnPosition  ) ; 
  
  //  delay (500) ;  
  //   Enemy.Movementfunction( "DOWN" , &Enemy.RowPosition ,  &Enemy.ColumnPosition  ) ; 
  
  //   delay (500) ;   

  //  Enemy.Movementfunction( "DOWN" , &Enemy.RowPosition ,  &Enemy.ColumnPosition  ) ; 
  

// SetDisplay ( 7 , 7 , HIGH ) ; 
   

}


 void CreateObstacles (void ) {

   for (int i = 0 ; i < matrixSize ; i ++  ){
    for (int j = 0 ; j < matrixSize ; j++ ) { 
       LC.setLed ( 0 , i ,  j , ObstacleMatrix[ (TranslateDisplayRows(i))][j] )   ;
      } 
   } 

 }


 void CharacterMovement ( String  Direction , unsigned char  & CursorRow , unsigned char & CursorColumn ) {
 
// Clear the current position before changing position
  LC.setLed ( 0 , CursorRow, CursorColumn , LOW )   ;
     
  if (Direction == "RIGHT" )  {
     CursorColumn  =  min  (  CursorColumn + 1 , MaxColumns ) ;   // Execute a movement to the right step

    if (  (ObstacleMatrix [ (TranslateDisplayRows(CursorRow)) ][CursorColumn ] ) == HIGH )  {  // Check if the new position has obstacle in it ? if yes then revert the movement
      CursorColumn = CursorColumn - 1 ; 
      }
   }
  else if (Direction == "LEFT" ) { 
     CursorColumn  =  max  ( CursorColumn - 1 ,  0  ) ; 

    if  (  (ObstacleMatrix [ (TranslateDisplayRows(CursorRow)) ][CursorColumn ] ) == HIGH ) {
    CursorColumn = CursorColumn + 1 ; 
      }
  }  
  else if (Direction == "UP" ) { 
      CursorRow  =   min ( CursorRow + 1 , MaxRows ) ; 

    if  (  (ObstacleMatrix [ (TranslateDisplayRows(CursorRow)) ][CursorColumn ] ) == HIGH ) {  // Check if the new position has obstacle in it ? if yes then revert the movement
      CursorRow = CursorRow - 1 ; 
      }
  }
  
  else if (Direction == "DOWN" ) { 
      CursorRow =   max  (  CursorRow - 1 , 0  ) ; 

    if  (  (ObstacleMatrix [ (TranslateDisplayRows(CursorRow)) ][CursorColumn ] ) == HIGH )  {  // Check if the new position has obstacle in it ? if yes then revert the movement
      CursorRow = CursorRow + 1 ; 
     }
  }

  else if (Direction == "SAME"){
    // Nothing just hold position
  }

  else if (Direction == "DEFAULT_PLAYER"){
    CursorRow = 4 ; 
    CursorColumn= 0 ;
     }

  else if (Direction == "DEFAULT_ENEMY"){
    CursorRow = 4 ; 
    CursorColumn= 7 ;
     } 

  else { 
    CursorRow = 0 ; 
    CursorColumn = 0 ;
  }    

   LC.setLed ( 0 , CursorRow, CursorColumn , HIGH )   ;
    } 

   String JoystickInterface ( ) {  

  // Get the analog value of each joystick axis and map it on 0 - 100  scale. 0 and 100 are readings for the extreme positions , the middle position being around 50 in this scale
    unsigned int  VerticalaxisValue    =   map(  (analogRead(Joystick_Vertical )) , 0 , 1023 , 0 , 100    ) ;
    unsigned int  HorizontalaxisValue  =   map(  (analogRead(Joystick_Horizontal )) , 0 , 1023 , 0 , 100    ) ;
    
     if ( VerticalaxisValue > 60 ) { 
        return "UP" ; 
    }
     if (VerticalaxisValue < 40  ) {
        return "DOWN" ; 
     }
     if (HorizontalaxisValue > 60  ) {
        return "LEFT" ; 
     }
     if (HorizontalaxisValue < 40  ) {
        return "RIGHT" ; 
     }
     else {
      return "SAME" ; 
     }
    
     
     
   }
  

   /* Row Numbers on the 8x8 Display here start from 7 at the top to 0 at the bottom , instead of the increasing from top to bottom as it should.
   The following function tasks a row number in the convention of the display here and translates it to standard form so we can set obstacles matrix with ease. 
   Translate from bottom to up row axis to up to bottom row axis*/
   unsigned char  TranslateDisplayRows (unsigned char row  ) { 
        return  row  = MaxRows - row ;  

   }

  // The following function blinks the a point at 2x of the timer period of the provided blink rate
  // Millis() is used to provide a non blocking timing function

  void BlinkCharacter  ( Characters & character  ) { 
    
    character.currentChronos = millis ( ) ; 

    if (  (   character.currentChronos  -   character.pastChronos ) <= character.Blinkrate ) {   
             LC.setLed ( 0 , character.RowPosition, character.ColumnPosition , HIGH )   ;
  }
    else if (  (( character.currentChronos  -  character.pastChronos ) <= (character.Blinkrate) ) && ((character.currentChronos  -  character.pastChronos ) > (character.Blinkrate) ) ) {
            LC.setLed ( 0 , character.RowPosition, character.ColumnPosition , LOW )   ;
   }
    else {
            character.pastChronos  =  character.currentChronos ;
    }
}

 // Used to place a bomb, uses the time value of a character reserved for bomb
 bool CheckJoystickButton  ( ) { 

     currentReading =  digitalRead( Joystick_Button ) ; 
     CurrentChronos = millis ( ) ; 

     if ( currentReading != PastReading )  { 
        PastChronos = CurrentChronos ; 
        }
     if (  (CurrentChronos - PastChronos)  >= debounceInterval ) {
        if ( currentReading != ButtonState  ) {
           ButtonState = currentReading ;
            if ( ButtonState == LOW ) { 
              return true ; 
            }
        }
     }
     else {
       return false ;
          }
        PastReading  = currentReading ;
 }
  

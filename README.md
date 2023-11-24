# Introduction to Robotics (2023 - 2024)

This repository contains a collection of assignments and projects related to digital electronics and microcontroller programming,  using Arduino boards. These assignments were completed as part of a course  during the 3rd year at the Faculty of Electrical Engineering and Computer Science.
  
## Homework 1
We will  install arduino IDE:https://www.arduino.cc/en/software2 and create a PRIVATE Github repository, according to these specifications: 
it is private, access to the following github users: irikos, danadascalescu00, adiRandom, alexsasu, alexion2001, surdubob, dandi08, radudilirici, vladfxstoader, IoanaLivia  and its name is name  ”IntroductionToRobotics” .
In this repo we will be posting our robotics homework, with code and videos of our work.

## Homework 2

We will use distinct potentiometers to individually manage the Red, Green, and Blue aspects of the RGB LED. This control system should utilize digital electronics, involving the Arduino to acquire potentiometer readings and subsequently assign mapped values to the corresponding LED pins.

WHAT WILL WE NEED?
 1. 1 RGB LED
 2. 3 Potentiometer
 3.Resistors and wires

HOW IT WORKS: https://youtube.com/shorts/1mJRTkr9I-w?feature=share
AND A PICTURE:IMG_20231025_163049746.jpg



## Homework 3
We will create a control system using the Arduino platform to simulate a 3-floor elevator and we will have the follow:

1.LED Indicators: Utilize three LEDs, each representing one of the three floors. The LED corresponding to the current floor should be illuminated. Additionally, another LED should indicate the elevator's operational state. It should blink while the elevator is in motion and remain steady while stationary.
2.Buttons: Integrate three buttons representing call buttons from the three floors. When pressed, the elevator should simulate movement towards the designated floor after a brief delay of 2-3 seconds.
3. Buzzer (optional for Computer Science, mandatory for CTI): Optionally, include a buzzer to emit brief sounds during specific instances: when the elevator arrives at the desired floor (a sound resembling a "cling") and during elevator door closing and movement (potentially using two distinct sounds).
4.State Change & Timers: If the elevator is already positioned at the requested floor, pressing the button for that floor should have no effect. Otherwise, after a button press, the elevator should "wait for the doors to close" and then "move" to the corresponding floor. If the elevator is already in motion, it should either disregard new commands or queue them (e.g., reach the first programmed floor, open the doors, wait, close them, and then proceed to the next desired floor).
5.Debounce: Implement a debounce mechanism for the buttons to prevent unintended repeated button presses.

WHAT WILL WE NEED?
1.LEDs 4
2.Buttons 3 for floor calls
3.Buzzer 1 optional
4.Resistors and wires 

HOW IT WORKS:https://www.youtube.com/shorts/2ulBD_uoUJ0
AND A PICTURE:IMG_20231031_171220514.jpg

## Homework 4
We will use 1 7-segment display, 1 joystick, resistors and wires to control the position of
the segment and  they should jump from the current position
to the other positions nearby, but without passing through ”walls”. When we press the joystick, the segment we are curently on should stop blinking, and then we move to the next step.

The starting position of the system should be at the decimal point (DP). The current position should consistently blink, regardless of whether the segment is active or inactive. Employ a joystick to navigate between adjacent positions (refer to the table for the corresponding movements). A quick press of the button toggles the segment state between ON and OFF. For a long press of the button, the entire display resets by deactivating all segments and relocating the current position to the decimal point. Interrupts are necessary for the CTI (Computer Science and Information Technology) application.

WHAT WILL WE NEED?
1.17-segment display
2.1 joystick
3.resistors and wires

HOW IT WORKS:HOW IT WORKS:https://www.youtube.com/shorts/2ulBD_uoUJ0
AND A PICTURE:![image](https://github.com/anamaria1-png/IntroductionToRobotics/assets/89720718/5bc74516-3339-45f8-8bbb-3ea714b71bc5)

## Homework 5
 We will create a stopwatch timer using a 4-digit 7-segment display along with three buttons. The timer should measure time in tenths of a second and include a feature to save laps, resembling basic stopwatch functions commonly found in mobile phones.The initial value displayed on the 4-digit 7-segment display should be "000.0". The buttons should serve the following functions:

    1.Button 1: Start or pause the timer.
    2.Button 2: Reset the timer if it's in pause mode or clear saved laps if in lap viewing mode.
    3.Button 3: Save a lap (when in counting mode), cycle through the last saved laps (up to 4 laps).

Workflow:

    1.Display Initialization: The display shows "000.0". Upon pressing the Start button, the timer begins counting.
    2.During the timer's operation, each press of the lap button stores that timer's value in memory, allowing up to 4 laps to be saved (or more if needed). Pressing the lap button for the 5th time will overwrite the first saved lap. Pressing the reset button while the timer is running will have no effect, and pressing the pause button stops the timer.
     3.Pause Mode: While the timer is paused, the lap button won't save additional laps. Pressing the reset button during pause mode resets the display to "000.0".
     4.After a reset, pressing the lap button cycles through the saved lap times. Each press of the lap button moves to the next saved lap. Continuously pressing this button cycles through laps. Pressing the reset button in this state clears all saved laps and resets the timer to "000.0".

     WHAT WILL WE NEED?
1.LEDs 4
2.Buttons 3 for floor calls
3.Buzzer 1 optional
4.Resistors and wires 

HOW IT WORKS:https://www.youtube.com/shorts/2ulBD_uoUJ0
AND A PICTURE:IMG_20231031_171220514.jpg

## Homework 6
This is a more ample project, including: Arduino Uno Board•Ultrasonic Sensor (HC-SR04)•LDR (Light-Dependent Resistor) aka Photocell aka Photoresistor aka LightSensor•RGB LED•Resistors as needed•Breadboard and connecting wires. The purpose of the project is to a menu structure , with sensor Settings,  Ultrasonic Alert Threshold and LDR Alert Threshold and then to go back to the menu.Then we need to reset the logger data, with a simple message with options of answear ''yes'' or ''no''.We have also a system Status to check current status and healthL Current Sensor Readings, Current Sensor Settings and  Display Logged Data. We also need to have a system for the RGB LED Control.

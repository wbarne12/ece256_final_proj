# ECE256 Final Project
This is our final project for ECE256: Computer Systems Interfaces.  
Our goal for this project was to make a functional robot arm/leg in hopes of building a fully functional robot.  

## Authors
Barnes, Stanley - wbarne12@vols.utk.edu  
Floyd, David - sfloyd10@vols.utk.edu  

## How it works
Our robotic arm either uses a joystick or computer input to move.    

If you are using the joystick to move the arm, the microcontroller will use both of the built in ADC's. It will then take the raw 
input from the ADC, and translate it to a certain degree and control the servos to move them to the position. 

Using Systick we create delays and togle the signal going to the servo on and off to create our pwm signals. This is a bit messy,
but it works for a small number of servos. Scalling this project would require use of the PWM pins and the PWM functions but this is easier
for quick applicaiton.

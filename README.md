# ECE256 Final Project
This is our final project for ECE256: Computer Systems Interfaces.  
Our goal for this project was to make a functional robot arm/leg in hope of building a fully functional robot.  

## Authors
Barnes, Stanley - wbarne12@vols.utk.edu  
Floyd, David - sfloyd10@vols.utk.edu  

## How it works
Our robotic arm either uses a joystick or computer input to move.    

If you are using the joystick to move the arm, the microcontroller will use both of the built in ADC's. It will then take the raw 
input from the ADC, and translate it to a certain amount of time. That amount of time will then be used to create a pulse to control the servos.  

If you are using the computer to enter movements, then the microcontroller will use UART. The input will be a certain number of degrees to move.
That degree will also get translated into a certain amount of time. From there, it will act the same as the joystick input. 

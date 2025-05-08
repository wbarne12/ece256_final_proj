# ECE256 Final Project
This is our final project for ECE256: Computer Systems Interfaces.  
Our goal for this project was to make a functional robot arm/leg in hopes of building a fully functional robot.  

## Authors
Barnes, Stanley - wbarne12@vols.utk.edu  
Floyd, David - sfloyd10@vols.utk.edu  

## How it works
First, movement is input with a joystick. The joystick creates an analog signal between 0 V and 3.3 V for the x-axis and the y-axis. Both of these signals
are sent to the microcontroller. The microcontroller utalizes the built in ADC's to convert the analog signal to a digital signal. At this point, we are able
internally process the inputs.  

Using Systick we create delays and togle the signal going to the servo on and off to create our pwm signals. This is a bit messy,
but it works for a small number of servos. Scalling this project would require use of the PWM pins and the PWM functions but this is easier
for quick applicaiton.

## How to build project
This project was designed in Keil U-vision, so all compliation should take place on that environment. The code is designed to run on the Tiva C EK-TM4C123GXL board. 

# PCA9685-BB
Simple Code to Allow Beagleboard to control the Adafruit PCA9685

## PCA9685 Info
This is an LED lighting controller that has been pressed into service to drive servos. I think
it's a pretty keen idea.

See [PCA9685 datasheet](https://cdn-shop.adafruit.com/datasheets/PCA9685.pdf)  

## How it works
1. PCA9685.cpp and .h provide an abstraction over the I2C interface and the PCA9685.
2. main.cpp creates an instance of PCA9685 and then invokes it.

## My test setup
This is where I would do fritzing for a later revision of this file.
1. Connect BBB P9-20 to SDA pin on 9685
2. Connect BBB P9-19 to SCL pin on 9685
3. Connect BBB P9-1 to ground on a breadboard
4. Connect BBB P9-3 to one + track on a breadboard. Provides +3.3v to project
5. Connect BBB P9-5 to the other + track on a breadboard. Provides +5v to project
6. Connect the two ground tracks on the breadboard together.
7. Connect V+ on the 9685 to the +5v on the breadboard.
8. Connect GND on the 9685 to the ground on the breadboard.
9. Connect OE on the 9685 to the ground on the breadboard. This pin is active LOW and should have been labelled with a bar over it on the 9685 board.
10. Connect Vcc pm the 9685 to the +3.3v on the breadboard.
11. Connect two servos to the 9685 on servos 15 and 14 (the extreme right of the board)

## Build
`make all`

## Run
`dist/Release/GNU-Linux-x86/sc`

Happy Servo-ing  
grondak

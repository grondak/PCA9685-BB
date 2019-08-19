/* 
 * File:   main.cpp
 * Author: tonyreynolds
 *
 * Created on January 1, 2013, 2:30 PM
 * Found after however long on August 17, 2019, about 2PM
 * See PCA9685 datasheet at https://cdn-shop.adafruit.com/datasheets/PCA9685.pdf  
 */

#include "PCA9685.h"
// 'minimum' pulse length count (out of 4096) (sets servo travel boundary on one side)
#define SERVOMINBOUNDARY 150
// 'maximum' pulse length count (out of 4096) (sets servo travel boundary on the other side)
#define SERVOMAXBOUNDARY 600
// controls how far the servos move each time they are stepped
#define STEPSIZE 50
// I have two servos, 14 & 15, on my board. You should fill in from the highest servo if you
// and work downwards. If you have one servo, put it on 15 and fix LOWESTCONNECTEDSERVO
#define LOWESTCONNECTEDSERVO 14
// pause between each step so you can see the system precisely control the servos
#define PAUSELENGTH 250000
using namespace std;

/*
 * this code will drive servos 14 and 15, connected as in the README.md
 * Each servo turns all the way to one side
 * Each servo turns all the way to the other side
 * this repeats until you hit control-C
 * lots of diagnostic info on STDOUT
 */
int main(int argc, char** argv)
{

    int adapter_nr = 2; /* on the Beaglebone, this is P9 pin 19/20 aka i2c-2 */
    int addr = 0x40; /* The I2C address of the PCA9685 */
    PCA9685 myController(adapter_nr, addr); // create an instance of the abstraction

    myController.reset(); // ensure it is ready to go

    myController.setPWMFreq(60); // defines modulation frequency

    int servonum = LOWESTCONNECTEDSERVO; // initialized to the first servo to work on

    // loop continuously-- hit control-C or someone sent this thing a sigkill.
    // run each servo to the limit and then back again
    while (1)
    {

        for (int pulselen = SERVOMINBOUNDARY; pulselen < SERVOMAXBOUNDARY; pulselen += STEPSIZE)
        {
            myController.setPWM(servonum, 0, pulselen);
                    usleep(PAUSELENGTH);
        }

        for (int pulselen = SERVOMAXBOUNDARY; pulselen > SERVOMINBOUNDARY; pulselen -=STEPSIZE)
        {
            myController.setPWM(servonum, 0, pulselen);
                    usleep(PAUSELENGTH);
        }

        servonum++;
        if (servonum > myController.getMaxServos()) servonum = LOWESTCONNECTEDSERVO;
    }

}


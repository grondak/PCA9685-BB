/* 
 * File:   main.cpp
 * Author: tonyreynolds
 *
 * Created on January 1, 2013, 2:30 PM
 */

#include "PCA9685.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{

    int adapter_nr = 2; /* on the Beaglebone, this is P9 pin 19/20 */
    int addr = 0x40; /* The I2C address of the PCA9685 */
    PCA9685 myController(adapter_nr, addr);

    myController.reset();
    //sleep(1);
    myController.setPWMFreq(60);
    //sleep(1);
    int servonum = 14;

    while (1)
    {
#define SERVOMIN 150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600 // this is the 'maximum' pulse length count (out of 4096)
        for (int pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen += 50)
        {
            myController.setPWM(servonum, 0, pulselen);
                    usleep(250000);
        }

        for (int pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen -=50)
        {
            myController.setPWM(servonum, 0, pulselen);
                    usleep(250000);
        }

        servonum++;
        if (servonum > 15) servonum = 14;
    }

}


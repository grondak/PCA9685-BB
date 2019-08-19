/* 
 * File:   PCA9685.h
 * Author: tonyreynolds
 *
 * Created on January 1, 2013, 7:39 PM
 */

#ifndef PCA9685_H
#define	PCA9685_H

#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

// see PCA9685 datasheet at https://cdn-shop.adafruit.com/datasheets/PCA9685.pdf
class PCA9685 {
public:
    PCA9685(int adapter_number, int address);
    virtual ~PCA9685();
    int reset();
    int getMaxServos();
    char readByte(char reg);
    int writeByte(char reg, char value );
    void setPWMFreq(float freq);
    void setPWM(char num, int on, int off);
      
    static const char PCA9685_MODE1 = 0x0; // control register
    static const char PCA9685_PRESCALE = 0xFE; // modulation register
    static const char LED0_ON_L = 0x6; // the PCA9685 is meant to be a PWM lighting
    static const char LED0_ON_H = 0x7; // controller so the registers are named
    static const char LED0_OFF_L = 0x8; // for controlling lights
    static const char LED0_OFF_H = 0x9;
    static const int MAXSERVOS = 15; // starts at servo 0!!

private:
      int _adapterNumber;
      int _address;
      int _PCA9685file;

      
      
};

#endif	/* PCA9685_H */


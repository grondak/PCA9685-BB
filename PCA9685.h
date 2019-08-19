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

class PCA9685 {
public:
    PCA9685(int adapter_number, int address);
    virtual ~PCA9685();
    int reset();
    char readByte(char reg);
    int writeByte(char reg, char value );
    void setPWMFreq(float freq);
    void setPWM(char num, int on, int off);
      
    static const char PCA9685_MODE1 = 0x0;
    static const char PCA9685_PRESCALE = 0xFE;
    static const char LED0_ON_L = 0x6;
    static const char LED0_ON_H = 0x7;
    static const char LED0_OFF_L = 0x8;
    static const char LED0_OFF_H = 0x9;

private:
      int _adapterNumber;
      int _address;
      int _PCA9685file;

      
      
};

#endif	/* PCA9685_H */


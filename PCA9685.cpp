/* 
 * File:   PCA9685.cpp
 * Author: tonyreynolds
 * 
 * Created on January 1, 2013, 7:39 PM
 */

#include "PCA9685.h"
#include <math.h>

PCA9685::PCA9685(int adapter_number, int address)
{
    char filename[20];
    _adapterNumber = adapter_number;
    _address = address;

    snprintf(filename, 19, "/dev/i2c-%d", _adapterNumber);
    printf("Opening device %s\n", filename);
    _PCA9685file = open(filename, O_RDWR);
    if (_PCA9685file < 0)
    {
        perror("While trying to open the i2c controller");
        exit(1);
    }

    printf("Setting I2C address of slave to 0x%02x\n", _address);
    if (ioctl(_PCA9685file, I2C_SLAVE, _address) < 0)
    {
        perror("While trying to ioctl for the device");
        exit(1);
    }
}

int PCA9685::reset()
{
    writeByte(PCA9685_MODE1, 0x00);
}

void PCA9685::setPWMFreq(float freq)
{
    float prescaleval = 25000000;
    prescaleval /= 4096;
    prescaleval /= freq;
    prescaleval -= 1;

    printf("Estimated prescale: %f\n", prescaleval);
    char prescale = (char) floor(prescaleval + 0.5);
    printf("Final prescale: 0x%02x\n", prescale);
    char oldmode = readByte(PCA9685_MODE1);
    char newmode = (oldmode & 0x7F) | 0x10; // sleep
    writeByte(PCA9685_MODE1, newmode); // go to sleep
    writeByte(PCA9685_PRESCALE, prescale); // set the prescaler
    writeByte(PCA9685_MODE1, oldmode);
}

void PCA9685::setPWM(char num, int on, int off)
{
    writeByte(LED0_ON_L + 4 * num, on);
    writeByte(LED0_ON_H + 4 * num, on >> 8);
    writeByte(LED0_OFF_L + 4 * num, off);
    writeByte(LED0_OFF_H + 4 * num, off >> 8);
}

int PCA9685::writeByte(char reg, char value)
{
    char buff[2];
    printf("Writing register 0x%02x with byte 0x%02x.\n", reg, value);
    memset(buff, '0', sizeof (buff));
    buff[0] = reg;
    buff[1] = value;
    if (write(_PCA9685file, (const void *) buff, 2) != 2)
    {
        perror("While trying to write a byte");
    }
    return errno;
}

char PCA9685::readByte(char reg)
{
    char buffer;
    buffer = reg;
    printf("Sending the read register address of 0x%02x\n", reg);
    if (write(_PCA9685file, (const void *) &buffer, 1) != 1)
    {
        perror("While trying to send the register address");
        exit(1);
    }

    buffer = 0;
    printf("Trying to read 1 byte from address 0x%02x\n", reg);
    if (read(_PCA9685file, (void *) &buffer, 1) != 1)
    {
        perror("While trying to read register 1!");
        exit(1);
    } else
    {
        printf("Register 0x%02x has value: 0x%02x.\n", reg, buffer);
    }
    return buffer;
}

PCA9685::~PCA9685()
{
    close(_PCA9685file);
}
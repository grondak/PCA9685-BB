/* 
 * File:   PCA9685.cpp
 * Author: tonyreynolds
 * see PCA9685 datasheet at https://cdn-shop.adafruit.com/datasheets/PCA9685.pdf  
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

int PCA9685::getMaxServos()
{
  return MAXSERVOS; // fixed by the PCA9685
}

int PCA9685::reset() // per the PCA9685 datasheet, we put Mode Register 1 to 0s
{
    return writeByte(PCA9685_MODE1, 0x00);
}

// manipulates the MODE1 register per the datasheet to
// 1. put the PCA6885 to sleep
// 2. set the prescale regiser to the calculated modulation frequency
// 3. resets the PCA9685 to where the chip was before we called it.
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

// This controls the PWM timing for the given Servo
void PCA9685::setPWM(char servo_num, int on, int off)
{
    writeByte(LED0_ON_L + 4 * servo_num, on);
    writeByte(LED0_ON_H + 4 * servo_num, on >> 8);
    writeByte(LED0_OFF_L + 4 * servo_num, off);
    writeByte(LED0_OFF_H + 4 * servo_num, off >> 8);
}

// Low-level routine to set a PCA9685 register to a given value
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
// Low-level routine to read a specific PCA9685 register
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

// destructor closes the open file on the I2C device
PCA9685::~PCA9685()
{
    close(_PCA9685file);
}

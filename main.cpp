#include "mbed.h"
#include "rtos.h"
#include "QEI.h"
#include "MotorShield.h" 
#include "HardwareSetup.h"

Serial pc(USBTX, USBRX);    // USB Serial Terminal
Timer t;                    // Timer to measure elapsed time of experiment

QEI encoderA(PE_9,PE_11, NC, 1200, QEI::X4_ENCODING);  // MOTOR A ENCODER (no index, 1200 counts/rev, Quadrature encoding)
QEI encoderB(PA_5, PB_3, NC, 1200, QEI::X4_ENCODING);  // MOTOR B ENCODER (no index, 1200 counts/rev, Quadrature encoding)
QEI encoderC(PC_6, PC_7, NC, 1200, QEI::X4_ENCODING);  // MOTOR C ENCODER (no index, 1200 counts/rev, Quadrature encoding)
QEI encoderD(PD_12, PD_13, NC, 1200, QEI::X4_ENCODING);// MOTOR D ENCODER (no index, 1200 counts/rev, Quadrature encoding)

MotorShield motorShield(12000); //initialize the motor shield with a PWM period of 12000 ticks or ~20kHZ

int main (void)
{    
    // Setup experiment
    t.reset();
    t.start();
    encoderA.reset();
    float position;
    float velocity;
    float current;
    motorShield.motorAWrite(0, 0); //turn motor A off
    
    //use the motor shield as follows:
    //motorShield.motorAWrite(DUTY CYCLE, DIRECTION), DIRECTION = 0 is forward, DIRECTION =1 is backwards. 

    // Run experiment for 10 seconds
    while( t.read() < 10 ) {
        // Perform control loop logic
        if (t.read() < 5)
            motorShield.motorAWrite(0.5, 0); //run motor A at 50% duty cycle and in the forward direction for 5 seconds
        else
            motorShield.motorAWrite(0.5, 1); //run motor A at 50% duty cycle and in the reverse direction for 5 seconds
                        
        position = 0; //MODIFY THIS
        velocity = 0; //MODIFY THIS
        current = motorShield.readCurrentA()*(30.0/65536.0)-15; //read current for motor A in amps. Note: this is a slightly different current sensor so its a different conversion than last lab.
        
        pc.printf("Current reading: %f Amps, Velocity: %f, Angle: %f \n\r", current, velocity, position);
        
        wait(.01); //run control loop at 100Hz
    }

    motorShield.motorAWrite(0, 0); //turn motor A off
    
    while(1) {
        //loop forever
    } 

} // end main

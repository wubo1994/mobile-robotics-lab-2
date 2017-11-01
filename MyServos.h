
#include <Servo.h>
#include "MyEncoders.h"
//#include <SShapeParams.h>

#ifndef __MY_SERVOS__
#define __MY_SERVOS__

//NOTE: you are allowed to modify this file as long as the functions
//implement the requested functionality
Servo LServo;
Servo RServo;

float leftCalibrateRPSTable[11] = {0.00,0.06,0.17,0.28,0.39,0.47,0.54,0.60,0.63,0.66,0.68};
float rightCalibrateRPSTable[11] = {0.00,0.04,0.16,0.27,0.37,0.47,0.55,0.60,0.63,0.66,0.67};

float leftCalibrateIPSTable[11] = {0.00,0.51,1.43,2.30,3.18,3.89,4.46,4.92,5.17,5.43,5.53};
float rightCalibrateIPSTable[11] = {0.00,0.36,1.28,2.20,3.07,3.89,4.51,4.92,5.12,5.38,5.48};

//float leftRPSper500Microseconds = 0;
//float rightRPSper500Microseconds = 0;

void calibrate();

//LServo.attach(2);
//RServo.attach(3);

//this function should set the left and right speeds of the wheel
//when both inputs are positive the robot should move forward
//when both inputs are negative the robot should move backward
//microsLeft should encode the left wheel velocity and viceversa
void setSpeeds(int microsLeft, int microsRight)
{
    LServo.attach(2);
    RServo.attach(3);
    LServo.writeMicroseconds(1500+microsLeft);
    RServo.writeMicroseconds(1500-microsRight);
}



//same as the function setSpeeds, but the inputs now indicate 
//the revolutions per secont (rps) at which each wheel should spin

void setSpeedsRPS(float rpsLeft,float rpsRight)
{
    int leftSpeed;
    int rightSpeed;

    bool leftFlag = false;
    bool rightFlag = false;

    if(rpsLeft<0) {
        rpsLeft = (-1) * rpsLeft;
        leftFlag = true;
    }
    if(rpsRight<0) {
        rpsRight = (-1) * rpsRight;
        rightFlag = true;
    }

    for(int i=0;i<=10;i++)
    {
        if(leftCalibrateRPSTable[i]==rpsLeft)
        {
            leftSpeed = 10*i;
            break;
        }
        else if(leftCalibrateRPSTable[i]<rpsLeft)
            ;
        else
        {
            leftSpeed = 10*(i-1)+10*((rpsLeft-leftCalibrateRPSTable[i-1])/(leftCalibrateRPSTable[i]-leftCalibrateRPSTable[i-1]));
            break;
        }
    }
    for(int j=0;j<=10;j++)
    {
        if(rightCalibrateRPSTable[j]==rpsRight)
        {
            rightSpeed = 10*j;
            break;
        }
        else if(rightCalibrateRPSTable[j]<rpsRight)
            ;
        else
        {
            rightSpeed = 10*(j-1)+10*((rpsRight-rightCalibrateRPSTable[j-1])/(rightCalibrateRPSTable[j]-rightCalibrateRPSTable[j-1]));
            break;
        }
    }
    if(leftFlag)
        leftSpeed = (-1)*leftSpeed;
    if(rightFlag)
        rightSpeed = (-1)*rightSpeed;
    setSpeeds(leftSpeed,rightSpeed);
}

//same as the function setSpeeds, but the inputs now indicate 
//the inches per second (ips) at which each wheel should spin
void setSpeedsIPS(float ipsLeft, float ipsRight)
{
    int leftSpeed = 0;
    int rightSpeed = 0;

    bool leftFlag = false;
    bool rightFlag = false;

    if(ipsLeft<0) {
        ipsLeft = (-1) * ipsLeft;
        leftFlag = true;
    }
    if(ipsRight<0) {
        ipsRight = (-1) * ipsRight;
        rightFlag = true;
    }

    for(int i=0;i<=10;i++)
    {
        if (leftCalibrateIPSTable[i] == ipsLeft) {
            leftSpeed = 10 * i;
            break;
        } else if (leftCalibrateIPSTable[i] < ipsLeft)
            ;
        else {
            leftSpeed = 10 * (i - 1) + 10 * ((ipsLeft - leftCalibrateIPSTable[i - 1]) /
                                             (leftCalibrateIPSTable[i] - leftCalibrateIPSTable[i - 1]));
            break;
        }
    }
    for(int j=0;j<=10;j++)
    {
        if(rightCalibrateIPSTable[j]==ipsRight)
        {
            rightSpeed = 10*j;
            break;
        }
        else if(rightCalibrateIPSTable[j]<ipsRight)
            ;
        else
        {
            rightSpeed = 10*(j-1)+10*((ipsRight-rightCalibrateIPSTable[j-1])/(rightCalibrateIPSTable[j]-rightCalibrateIPSTable[j-1]));
            break;
        }
    }
    if(leftSpeed == 0)
        leftSpeed = 100;
    if(rightSpeed == 0)
        rightSpeed = 100;
    
    if(leftFlag)
        leftSpeed = (-1)*leftSpeed;
    if(rightFlag)
        rightSpeed = (-1)*rightSpeed;
    setSpeeds(leftSpeed,rightSpeed);
}


//this function is meant for doing whatever necessary for the 
//functions 'setSpeedsIPS' and 'setSpeedsRPS' to work properly
void calibrate()
{
    int i;
    int left;
    int right;

    for(i = 0;i <= 10;i++)
    {
        setSpeeds(i*10,i*10);
        delay(1000);
        initEncoders();
        delay(5000);
        noInterrupts();
        left = leftTickCounts;
        right = rightTickCounts;
        interrupts();
        leftCalibrateRPSTable[i] = ((float)left/5)/32.00;
        rightCalibrateRPSTable[i] = ((float)right/5)/32.00;
        leftCalibrateIPSTable[i] = ((float)left*((2.61*3.14)/32.00))/5;
        rightCalibrateIPSTable[i] = ((float)right*((2.61*3.14)/32.00))/5;
        resetCounts();
    }

	
    //Serial.println(leftCalibrateRPSTable[5]);
}


//this function should make the robot move with a linear speed of v 
//measured in inches per second, and an angular speed of w
//in rads per second. Positive ws should indicate a counterclockwise spin.
void setSpeedsvw(float v, float w)
{
    float leftV;
    float rightV;

    if(w>=0)
    {
        leftV = w*((v/w)-(3.95/2.00));
        rightV = w*((v/w)+(3.95/2.00));
    }

    if(w<0)
    {
        leftV = (-1)*w*((v/((-1)*w))+(3.95/2.00));
        rightV = (-1)*w*((v/((-1)*w))-(3.95/2.00));
    }
    setSpeedsIPS(leftV,rightV);
}



#endif 

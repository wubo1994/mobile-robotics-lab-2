
#include <PinChangeInt.h>

#ifndef __MY_ENCODERS__
#define __MY_ENCODERS__

//counts[0] is the tickcounts of left wheel
//counts[1] is the tickcounts of right wheel
int leftTickCounts = 0;
int rightTickCounts = 0;
unsigned long LTimePrevious = 0;
unsigned long LTimeLatest = 0;
unsigned long RTimePrevious = 0;
unsigned long RTimeLatest = 0;
float wheelSpeed[2] = {0};

void getSpeeds(float speeds[]);

//This function is to increment the tickcounts
void increaseLeftCounts()
{
    leftTickCounts++;
    //Serial.println(tickCounts[0]);
    LTimePrevious = LTimeLatest;
    LTimeLatest = millis();
    getSpeeds(wheelSpeed);
    //Serial.println(wheelSpeed[0]);
    //Serial.println(tickCounts[0]);
}

void increaseRightCounts()
{
    rightTickCounts++;
    //Serial.println(tickCounts[1]);
    RTimePrevious = RTimeLatest;
    RTimeLatest = millis();
    getSpeeds(wheelSpeed);
    //Serial.println(wheelSpeed[1]);
}

void resetCounts()
{
    leftTickCounts = 0;
    rightTickCounts = 0;
}

//this function should return the left and right tickcounts 
// since either the start of the program or the last
//call to the function resetCounts()
//void getCounts(int counts[])
//{
//    counts[0] = tickCounts[0];
//    counts[1] = tickCounts[1];
//}

//this function should return the instantaneous speeds of the wheels
//meassured in revolutions per second.
void getSpeeds(float speeds[])
{
    wheelSpeed[0] = ((float)(1.00/32.00)/((float)LTimeLatest-(float)LTimePrevious))*1000.00;
    wheelSpeed[1] = ((float)(1.00/32.00)/((float)RTimeLatest-(float)RTimePrevious))*1000.00;
    speeds[0] = wheelSpeed[0];
    speeds[1] = wheelSpeed[1];
}

//this function should include whatever code necessary to initialize this module
void initEncoders()
{
    resetCounts();
    //pinMode(10,INPUT_PULLUP); // set port as input port
    //pinMode(11,INPUT_PULLUP);
    PCintPort::attachInterrupt(10,&increaseLeftCounts,FALLING);
    PCintPort::attachInterrupt(11,&increaseRightCounts,RISING);
    //PCintPort::attachInterrupt(10,&increaseLeftCounts,RISING);
}


#endif
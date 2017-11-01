


#ifndef __MY_SHARP_SENSOR__
#define __MY_SHARP_SENSOR__
int SLRaw[10] = {0};
int SRRaw[10] = {0};
int SFRaw[10] = {0};
int LFRaw[10] = {0};

//this function takes as input the value obtained by a short distance sensor,
//and it should return its respective value in inches
float shortToInches(int value)
{
	float voltage;
	voltage = (float)value*0.0049;
	
	if(voltage>3.04)
	{
		return 0;
	}
	else if((voltage>3) && (voltage<=3.04))
	{
		return ((-2.95)*voltage+10.149);
	}
	else if((voltage>2.73) && (voltage<=3))
	{
		return ((-1.0037)*voltage+4.3101);
	}
	else if((voltage>2.34) && (voltage<=2.73))
	{
		return ((-0.8205)*voltage+3.81);
	}
	else if((voltage>2.01) && (voltage<=2.34))
	{
		return ((-1.4242)*voltage+5.2227);
	}
	else if((voltage>1.78) && (voltage<=2.01))
	{
		return ((-1.7217)*voltage+5.8207);
	}
	else if((voltage>1.57) && (voltage<=1.78))
	{
		return ((-1.8762)*voltage+6.0956);
	}
	else if((voltage>1.4) && (voltage<=1.57))
	{
		return ((-2.0588)*voltage+6.3824);
	}
	else if((voltage>1.27) && (voltage<=1.4))
	{
		return ((-3.3615)*voltage+8.2062);
	}
	else if((voltage>1.06) && (voltage<=1.27))
	{
		return ((-3.7476)*voltage+8.6965);
	}
	else if((voltage>0.93) && (voltage<=1.06))
	{
		return ((-6.0615)*voltage+11.149);
	}
	else if((voltage>0.81) && (voltage<=0.93))
	{
		return ((-6.5667)*voltage+11.619);
	}
	else if((voltage>0.74) && (voltage<=0.81))
	{
		return ((-11.243)*voltage+15.407);
	}
	else if((voltage>0.65) && (voltage<=0.74))
	{
		return ((-8.7444)*voltage+13.558);
	}
	else if((voltage>0.53) && (voltage<=0.65))
	{
		return ((-16.383)*voltage+18.523);
	}
	else if((voltage>0.42) && (voltage<=0.53))
	{
		return ((-17.909)*voltage+19.332);
	}
    else
		return 12;
}

//this function takes as input the value obtained by the long distance sensor,
//and it should return its respective value in inches
float longToInches(int value)
{
	float voltage;
	voltage = (float)value*0.0049;
	
	if(voltage>2.51)
		return 0;
	else if((voltage>2) && (voltage<=2.51))
	{
		return ((-7.7255)*voltage+27.261);
	}
	else if((voltage>1.5) && (voltage<=2))
	{
		return ((-7.88)*voltage+27.57);
	}
	else if((voltage>1.25) && (voltage<=1.5))
	{
		return ((-15.76)*voltage+39.39);
	}
	else if((voltage>1.05) && (voltage<=1.25))
	{
		return ((-19.65)*voltage+44.252);
	}
	else if((voltage>0.9) && (voltage<=1.05))
	{
		return ((-26.267)*voltage+51.2);
	}
	else if((voltage>0.8) && (voltage<=0.9))
	{
		return ((-39.4)*voltage+63.02);
	}
	else if((voltage>0.7) && (voltage<=0.8))
	{
		return ((-39.3)*voltage+62.94);
	}
	else if((voltage>0.65) && (voltage<=0.7))
	{
		return ((-78.8)*voltage+90.59);
	}
	else if((voltage>0.6) && (voltage<=0.65))
	{
		return ((-78.8)*voltage+90.59);
	}
	else if((voltage>0.55) && (voltage<=0.6))
	{
		return ((-78.6)*voltage+90.47);
	}
	else if((voltage>0.5) && (voltage<=0.55))
	{
		return ((-78.8)*voltage+90.58);
	}
	else if((voltage>0.46) && (voltage<=0.5))
	{
		return ((-197)*voltage+149.68);
	}
	else 
		return 60;
}


//the following two functions are meant for combining (taking the mean, median or etc) multiple measurements

//this function should read and store a new measurement taken with sensor given by the parameter 'sensor'
#define SLEFT   0
#define SFRONT 1
#define SRIGHT  2
#define LFRONT   3
void takeNewMeasurement(int sensor)
{
	int analog = analogRead(sensor);
	
	if(sensor == SLEFT)
	{
	    for(int i=0;i<9;i++)
	    {
            SLRaw[i] = SLRaw[i+1];		
	    }
	    SLRaw[9] = analog;
	}
	
	if(sensor == SFRONT)
	{
		for(int i=0;i<9;i++)
		{
			SFRaw[i] = SFRaw[i+1];
		}
		SFRaw[9] = analog;
	}
	
	if(sensor == SRIGHT)
	{
		for(int i=0;i<9;i++)
		{
			SRRaw[i] = SRRaw[i+1];
		}
		SRRaw[9] = analog;
	}
	
	if(sensor == LFRONT)
	{
		for(int i=0;i<9;i++)
		{
			LFRaw[i] = LFRaw[i+1];
		}
		LFRaw[9] = analog;
	}
}


//this function should combine the last N measurement taken with sensor 'sensor' and return the result.
//You are free to chose the value of N
float getCombinedDistance(int sensor)
{
	int total = 0;
	int aveAnalog = 0;
	
	if(sensor == SLEFT)
	{
		for(int i=0;i<10;i++)
		{
			total += SLRaw[i];
		}
		aveAnalog = total/10;
		return shortToInches(aveAnalog);
	}
	
	else if(sensor == SFRONT)
	{
		for(int i=0;i<10;i++)
		{
			total += SFRaw[i];
		}
		aveAnalog = total/10;
		return shortToInches(aveAnalog);
	}
	
	else if(sensor == SRIGHT)
	{
		for(int i=0;i<10;i++)
		{
			total += SRRaw[i];
		}
		aveAnalog = total/10;
		return shortToInches(aveAnalog);
	}
	
	else if(sensor == LFRONT)
	{
		for(int i=0;i<10;i++)
		{
			total += LFRaw[i];
		}
		aveAnalog = total/10;
		return longToInches(aveAnalog);
	}
	
	else
		return -1;
}


#endif

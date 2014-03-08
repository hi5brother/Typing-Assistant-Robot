

/*
SoundFunction
Daniel
Mar 7, 2014

Loud Sound (>???)
Hit spacebar

Soft Sound (<???)
Hit enter key
*/

#define MICROPHONE 2
#define SOUNDTRESH 65
#define AMBIENT 25
int listen();

task main()
{
	
}

int listen()
{
	int dBlevel;		//sound sensor level in decibels
	
	SensorType[MICROPHONE]=sensorSoundDBA;
	
	wait1Msec(500);		//wait 500msec to start recording
	
	while (true)	
	{
		dBlevel=SensorValue[MICROPHONE];
		
		if (dBlevel>SOUNDTHRESH)	//returns a 1 if the sound is above 65 dB (SOUNDTHRESH)
			return 1;
		else if (dBlevel>AMBIENT)		//only returns something if sound is above the ambient room noise
			return 0;w
	}
}


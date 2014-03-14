

/*
SoundFunction
Daniel
Mar 11, 2014

Loud Sound (>???)
Hit spacebar and returns 1

Soft Sound (<???)
Hit enter key and returns 0

function gets passed into the main function
*/

#define MICROPHONE 2
#define SOUNDTHRESH 65
#define AMBIENT 25
int listen();

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
			return 0;
	}
}


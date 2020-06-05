#include <stdafx.h>

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	//Number of channels in buffer is always 2 (stereo)
	const int numChannels = 2;

	//Size of audio buffer in samples remains constant for prototype purposes
	const int numSamples = 5;

	//Initialise stereo buffer array
	//First bracket indicates channel (0 = left), 1 = right)
	//Second bracket indicates a specific sample within the given channel
	//E.g. to set the second value of the right channel to 0.5, use: sBuffer[1][2] = 0.5;
	//First number set is the left channel, Second is the right channel
	float sBuffer[numChannels][numSamples] = { { 0.25, 0.8, 0.1, -0.5, 0.2 },{ 0.1, -0.25, 0.5, -0.5, 0.3 } };

	//Declare user inputted parameters
	float midGainValue;
	float sideGainValue;
	float postGainValue;

	//Declare temporary Mid and Side buffer values
	float midBuffer[numSamples];
	float sideBuffer[numSamples];

	//Prompt user to enter a Mid gain value, Side gain value and Post gain value
	//0.0 = no silence, 1.0 = no change, 2.0 = doubled gain (6db)
	//Endless loop that breaks when valid input is entered
	while (1)
	{
		cout << "Please enter a gain value for the Mid Channel (must be greater than or equal to 0.0): ";
		cin >> midGainValue;

		//Validate that the user's input is greater than or equal to 0.0
		if (midGainValue < 0.0)
		{
			cout << "Sorry, that input was not valid." << endl;
		}
		//If input is valid, break loop
		else break;
	}
	//Repeat process for side gain value
	while (1)
	{
		cout << "Please enter a gain value for the Side Channel (must be greater than or equal to 0.0): ";
		cin >> sideGainValue;

		//Validate that the user's input is greater than or equal to 0.0
		if (sideGainValue < 0.0)
		{
			cout << "Sorry, that input was not valid." << endl;
		}
		//If input is valid, break loop
		else break;
	}
	//Repeat process for post gain value
	while (1)
	{
		cout << "Please enter a post gain value (must be greater than or equal to 0.0): ";
		cin >> postGainValue;

		//Validate that the user's input is greater than or equal to 0.0
		if (postGainValue < 0.0)
		{
			cout << "Sorry, that input was not valid." << endl;
		}
		//if input is valid, break loop
		else break;
	}

	//*****************************************************************************
	//Processing block to: -Encode Left and Right channels to Mid and Side channels
	//					   -Apply user entered gain to Mid and Side channels
	//					   -Decode back to Left and Right channels
	//                     -Apply user entered post-gain
	//*****************************************************************************
	for (int i = 0; i < numSamples; i++)
	{
		//Print old values of left and right channels
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "Old value of Left channel[" << i + 1 << "]: " << sBuffer[0][i] << endl;
		cout << "Old value of Right channel[" << i + 1 << "]: " << sBuffer[1][i] << endl;

		//Mid Encoding: M = L + R
		midBuffer[i] = sBuffer[0][i] + sBuffer[1][i];

		//Side Encoding: S = L - R
		sideBuffer[i] = sBuffer[0][i] - sBuffer[1][i];

		//Scale Mid and Side buffers by the user entered gain values
		midBuffer[i] *= midGainValue;
		sideBuffer[i] *= sideGainValue;

		//Left Decoding: L = (S + M) * 0.5
		sBuffer[0][i] = (sideBuffer[i] + midBuffer[i]) * 0.5;

		//Right Decoding: R = (M - S) * 0.5
		sBuffer[1][i] = (midBuffer[i] - sideBuffer[i]) * 0.5;

		//Apply Post-Gain
		sBuffer[0][i] *= postGainValue;
		sBuffer[1][i] *= postGainValue;

		//Print out new values for left and right channels
		cout << "New value of Left channel[" << i + 1 << "]: " << sBuffer[0][i] << endl;
		cout << "New value of Right channel[" << i + 1 << "]: " << sBuffer[1][i] << endl;
	}

	return 0;
}


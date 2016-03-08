
//Proper github at https://github.com/pkourany/FPS_GT511C3_Library
/* 
	a02-finger.ino - Library example for controlling the GT-511C3 Finger Print Scanner (FPS)
	Created by Josh Hawley, July 23rd 2013
	Licensed for non-commercial use, must include this license message
	basically, Feel free to hack away at it, but just give me credit for my work =)
	TLDR; Wil Wheaton's Law
	This sketch will attempt to identify a previously enrolled fingerprint.
	
	Modified for Particle Photon by Paul Kourany (peekay123), Oct 24, 2015
	updated by Jeremy Ellis, Twitter @rocksetta,  Mar 8th, 2016 
*/

#include "FPS_GT511C3/FPS_GT511C3.h"



// Works fine without serial connection or the IFTTT setup.
// Must use the enrol sketch first.


// using the http://www.robotshop.com/ca/en/jst-sh-jumper-4-wire-assembly-8.html cable
// and the Fingerprint scanner from
// http://www.robotshop.com/ca/en/fingerprint-scanner-5v-ttl.html


//Hardware setup for the photon
/*
My cable is green, yellow, black, red but some cables only have the first wire identified.

Pin   Wire Color       Photon Connection
1        Green          RX
2        Yellow         TX
3        Black          GND
4        Red            Vin (5v)

*/


// Note: on the Arduino you need to be careful with the 5V supply since the FPS uses 3.3 V on the transmission RX,TX wires.
// Not an issue with the Photon.



String nameString = "";



FPS_GT511C3 fps;

void setup()
{
	Serial.begin(9600);
	delay(100);
	fps.Open();
	fps.SetLED(true);
	pinMode(D7, OUTPUT);
	RGB.brightness(255);    // 1=very low light, 255 = max
}

void loop()
{

	// Identify fingerprint test
	if (fps.IsPressFinger())
	{
	    
	    RGB.brightness(1);    // shows it is doing something
		fps.CaptureFinger(false);
		int id = fps.Identify1_N();
		if (id < 200)
		{
			Serial.print("Verified ID:");
			Serial.println(id);
			
			if (id==0){nameString = "Tom's Right Index Finger";}
			if (id==1){nameString = "Mary's Right Index Finger";}
			if (id==2){nameString = "Fred G's Right Index Finger";}
			
			
			
			Particle.publish("my-FPS-verified334", nameString, 60, PUBLIC); // use public when testing then use Private
			//Particle.publish("my-FPS-verified334", nameString, 60, PRIVATE); 
			digitalWrite(D7, HIGH); // slow flash if good
		    delay(1000);
			digitalWrite(D7, LOW);
			delay(1000);			
			digitalWrite(D7, HIGH);
		    delay(1000);
			digitalWrite(D7, LOW);
			delay(1000);
		}
		else
		{
			Serial.println("Finger not found");
			digitalWrite(D7, HIGH);  // fast flash if bad
		    delay(100);
			digitalWrite(D7, LOW);
			delay(100);			
			digitalWrite(D7, HIGH);
		    delay(100);
			digitalWrite(D7, LOW);
			delay(100);
		}
	}
	else
	{
		Serial.println("Please press finger");
	}
	delay(5);
	RGB.brightness(255);    // ready for next finger
}

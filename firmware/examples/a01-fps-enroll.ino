
//Proper github at https://github.com/pkourany/FPS_GT511C3_Library

/* 
	a01-fps-enroll.ino - Library example for controlling the GT-511C3 Finger Print Scanner (FPS)
	Created by Josh Hawley, July 23rd 2013
	Licensed for non-commercial use, must include this license message
	basically, Feel free to hack away at it, but just give me credit for my work =)
	TLDR; Wil Wheaton's Law
	
	Modified for Particle Photon by Paul Kourany (peekay123), Oct 24, 2015
	Updated by Jeremy Ellis, Twitter @rocksetta  Mar 8, 2016
*/


#include "FPS_GT511C3/FPS_GT511C3.h"




// This sketch needs a serial connection to know which ID's you are setting.
// Power up the Photon, connect to your serial client (I use Putty), wait for the photon to breath cyan
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


FPS_GT511C3 fps;

void setup()
{
	Serial.begin(9600);
	delay(100);
	fps.Open();
	fps.SetLED(true);
    pinMode(D7, OUTPUT);
	Enroll();
}


void Enroll()
{
	// Enroll test

	// find open enroll id
	int enrollid = 0;
	bool usedid = true;
	while (usedid == true)
	{
		usedid = fps.CheckEnrolled(enrollid);
		if (usedid==true) enrollid++;
	}
	fps.EnrollStart(enrollid);

	// enroll
	digitalWrite(D7, HIGH);
	Serial.print("Press finger to Enroll #");
	Serial.println(enrollid);
	while(fps.IsPressFinger() == false) delay(100);
	digitalWrite(D7, LOW);
	bool bret = fps.CaptureFinger(true);
	int iret = 0;
	if (bret != false)
	{
		Serial.println("Remove finger");
		fps.Enroll1(); 
		while(fps.IsPressFinger() == true) delay(100);
		
	    digitalWrite(D7, HIGH);
		Serial.println("Press same finger again");
		while(fps.IsPressFinger() == false) delay(100);
	    digitalWrite(D7, LOW);
		bret = fps.CaptureFinger(true);
		if (bret != false)
		{
			Serial.println("Remove finger");
			fps.Enroll2();
			while(fps.IsPressFinger() == true) delay(100);
			
        	digitalWrite(D7, HIGH);
			Serial.println("Press same finger yet again");
			while(fps.IsPressFinger() == false) delay(100);
			
	        digitalWrite(D7, LOW);
			bret = fps.CaptureFinger(true);
			if (bret != false)
			{
				Serial.println("Remove finger");
				iret = fps.Enroll3();
				if (iret == 0)
				{
					Serial.println("Enrolling Successfull");
					
					
	                digitalWrite(D7, HIGH);
	                delay(1000);
	                digitalWrite(D7, LOW);
	                delay(1000);
	                digitalWrite(D7, HIGH);
	                delay(1000);
	                digitalWrite(D7, LOW);
	                delay(1000);
	                digitalWrite(D7, HIGH);
	                delay(1000);
	                digitalWrite(D7, LOW);
				}
				else
				{
					Serial.print("Enrolling Failed with error code:");
					Serial.println(iret);
					digitalWrite(D7, HIGH);
	                delay(200);
	                digitalWrite(D7, LOW);
	                delay(200);
	                digitalWrite(D7, HIGH);
	                delay(200);
	                digitalWrite(D7, LOW);
	                delay(200);
	                digitalWrite(D7, HIGH);
	                delay(200);
	                digitalWrite(D7, LOW);	                
	                delay(200);					
	                digitalWrite(D7, HIGH);
	                delay(200);
	                digitalWrite(D7, LOW);
	                delay(200);
	                digitalWrite(D7, HIGH);
	                delay(200);
	                digitalWrite(D7, LOW);
	                delay(200);
	                digitalWrite(D7, HIGH);
	                delay(200);
	                digitalWrite(D7, LOW);
				}
			}
			else Serial.println("Failed to capture third finger");	
	                digitalWrite(D7, HIGH);
	                delay(200);
	                digitalWrite(D7, LOW);
	                delay(200);
	                digitalWrite(D7, HIGH);
	                delay(200);
	                digitalWrite(D7, LOW);
	                delay(200);
	                digitalWrite(D7, HIGH);
	                delay(200);
	                digitalWrite(D7, LOW);
				            
		}
		else Serial.println("Failed to capture second finger");	

	                digitalWrite(D7, HIGH);
	                delay(200);
	                digitalWrite(D7, LOW);
	                delay(200);
	                digitalWrite(D7, HIGH);
	                delay(200);
	                digitalWrite(D7, LOW);
	}
	else Serial.println("Failed to capture first finger");	


	                digitalWrite(D7, HIGH);
	                delay(200);
	                digitalWrite(D7, LOW);
}


void loop()
{
   Serial.println("Waiting 10 seconds");
   delay(10000);
   Enroll();
}

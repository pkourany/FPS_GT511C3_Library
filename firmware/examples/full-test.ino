

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





// Works fine without serial connection or the IFTTT setup.
// Must use the enrol sketch first.


// using the http://www.robotshop.com/ca/en/jst-sh-jumper-4-wire-assembly-8.html cable
// and the Fingerprint scanner from
// http://www.robotshop.com/ca/en/fingerprint-scanner-5v-ttl.html


//Hardware setup for the photon
/*

//Push button connects D6 to power.
// tap to relight FPS
// hold for 4 seconds to enter each new student



My cable is green, yellow, black, red but some cables only have the first wire identified.

Pin   Wire Color       Photon Connection
1        Green          RX
2        Yellow         TX
3        Black          GND
4        Red            Vin (5v)

*/


// Note: on the Arduino you need to be careful with the 5V supply since the FPS uses 3.3 V on the transmission RX,TX wires.
// Not an issue with the Photon.



//String nameString = "";



FPS_GT511C3 fps;

void setup()
{
	Serial.begin(9600);
	delay(100);
	fps.Open();
	fps.SetLED(true);
	pinMode(D7, OUTPUT);
	pinMode(D6, INPUT_PULLDOWN);
	RGB.brightness(255);    // 1=very low light, 255 = max
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
	while(fps.IsPressFinger() == false) {
	   delay(100);
	  // if (digitalRead(D6) == LOW){break;}  // get out of loop if button off
	   }
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




int myLoops = 0;
int myEnrollLoops = 0;



void loop()
{
    
    myLoops +=1;
    
    if (myLoops >=3000){     // 500 = about 1 minute
	     	fps.SetLED(false);  // turn off FPS led after a delay
    }
    
    if (digitalRead(D6) == HIGH){
        fps.SetLED(true);   // if FPS LED was off turn it back on
	     myLoops = 0;       // restart the delay
	     myEnrollLoops +=1;
         if (myEnrollLoops >= 30){	  // still pressing button call enroll   
             Enroll();
         }
    }
 
    
    
    else {  //D6 not connected to power 
      myEnrollLoops = 0;          // reset loop counter for button
	// Identify fingerprint test
	if (fps.IsPressFinger())
	{
	    fps.SetLED(true);   // if FPS LED was off turn it back on
	    myLoops = 0;       // restart the delay
	    RGB.brightness(1);    // shows it is doing something
		fps.CaptureFinger(false);
		int id = fps.Identify1_N();
		if (id < 200)
		{
			Serial.print("Verified ID:");
			Serial.println(id);
	
		//	Particle.publish("my-FPS-verified334", nameString, 60, PUBLIC); // use public when testing then use Private
			Particle.publish("my-FPS-verified334", String(id), 60, PRIVATE); 
			digitalWrite(D7, HIGH); // slow flash if good
			fps.SetLED(false);      // flash the FPS if good 
		    delay(1000);
			digitalWrite(D7, LOW);
			fps.SetLED(true); 
	
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
			digitalWrite(D7, HIGH);
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
}

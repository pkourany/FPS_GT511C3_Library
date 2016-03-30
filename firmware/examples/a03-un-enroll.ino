
//Proper github at https://github.com/pkourany/FPS_GT511C3_Library

/* 
	a03-un-enroll.ino - Library example for controlling the GT-511C3 Finger Print Scanner (FPS)
	This file helps to delete
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
	delay(5000);    // time to activate the serial connection 
	Serial.begin(9600);
	delay(100);
	fps.Open();
	fps.SetLED(true);
  pinMode(D7, OUTPUT);

}



char inCharArray[3];
int toDelete;

void loop(){

  Serial.println("This sketch only deletes saved fingerprint scans");
  Serial.println("Enter 3 digit number of the scna to delete");
  Serial.println("Example 003,   015,  196");
   
  inCharArray[1] = Serial.read();
  inCharArray[2] = Serial.read();
  inCharArray[3] = Serial.read();
   
  toDelete = atoi(inCharArray)
   
  if (toDelete >=0 && toDelete <= 199){  // fingerprint scan to delete within range 0-199
    if (fps.DeleteID(toDelete)){
      Serial.println("Deleted that entry");  
    } else {Serial.println("Nothing deleted");  }
  }    
  
  
  if (toDelete == 200){
     	fps.SetLED(true);
     	Serial.println("LED true");
  }
  
    
  if (toDelete == 201){
     	fps.SetLED(false);
     	Serial.println("LED false");	
  }
  
    
  if (toDelete == 999){
     if	(fps.DeleteAll()){
     	Serial.println("deleted all scans");
     }   else {Serial.println("Did not delete all scans");}
  }
  
  
   if (toDelete == 333){
     if	(fps.IsPressFinger()){
     	Serial.println("Someones pushing the scaner down");
     }   else {Serial.println("No infomation about pushing the scanner");}
  }
  
   
 	if (fps.IsPressFinger())
	{
     	     Serial.println("Someones pushing the scaner down");
	     	fps.SetLED(false);
	     	DELAY(2000);
	     	fps.SetLED(true);
		
	} 


} 

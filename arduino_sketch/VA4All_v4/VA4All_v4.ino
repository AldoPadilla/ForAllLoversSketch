

/*
 Example: Control a WTV020-SD-16P module to play voices from an Arduino board.
 Created by Diego J. Arevalo, August 6th, 2012.
 Released into the public domain.
 */

#include <Wtv020sd16p.h>
//#include <Servo.h>
#include <VarSpeedServo.h>

const int buttonPin = 11;
const int ledPin = 13;

int buttonState = 0;

boolean canAcceptButtonPress = true;
int millisecondsToWait = 2000;
int startWaitTime = 0;
int resetPin = 2;  // The pin number of the reset pin.
int clockPin = 3;  // The pin number of the clock pin.
int dataPin = 4;  // The pin number of the data pin.
int busyPin = 5;  // The pin number of the busy pin.

/*
Create an instance of the Wtv020sd16p class.
 1st parameter: Reset pin number.
 2nd parameter: Clock pin number.
 3rd parameter: Data pin number.
 4th parameter: Busy pin number.
 */
Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);

long randNumber;

//Servo myservo;
VarSpeedServo myservo;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
    //Initializes the module.
  wtv020sd16p.reset();
  myservo.attach(9);
  Serial.begin(9600);
}

void playa() {
  randNumber = random(0, 16);
     //add code here to do when a 2X tap is sensed
      wtv020sd16p.playVoice(randNumber);
      delay (1000);
  //Plays synchronously an audio file. Busy pin is used for this method.
  //wtv020sd16p.playVoice(0);
  //Plays asynchronously an audio file.
  //wtv020sd16p.asyncPlayVoice(1);
  //Plays audio file number 1 during 2 seconds.
  //delay(5000);
  //Pauses audio file number 1 during 2 seconds.  
  //wtv020sd16p.pauseVoice();
  //delay(5000);
  //Resumes audio file number 1 during 2 seconds.
  //wtv020sd16p.pauseVoice();
  //delay(5000);  
  //Stops current audio file playing.
  //wtv020sd16p.stopVoice();
  //Plays synchronously an audio file. Busy pin is used for this method.  
  //wtv020sd16p.asyncPlayVoice(2);
  //delay(2000);   
  //Mutes audio file number 2 during 2 seconds.
  //wtv020sd16p.mute();
  //delay(2000);
  //Unmutes audio file number 2 during 2 seconds.
  //wtv020sd16p.unmute();
  //delay(2000);    
  //Stops current audio file playing.
  //wtv020sd16p.stopVoice();
}

void loop(){
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH){
    
     startWaitTime = millis();
     
    if(canAcceptButtonPress) {
    
      //DO ALL YOU NEED TO DO HERE
      Serial.println(buttonState);
      digitalWrite(ledPin, HIGH);
      playa();
      myservo.write(90, 25, true);
      delay(100);
      myservo.write(5, 25, true);
      delay(100);
      myservo.write(90, 25, true);
      
      canAcceptButtonPress = false;
    }
    
  }else if(!canAcceptButtonPress) {
    if(millis() - startWaitTime > millisecondsToWait){
      canAcceptButtonPress = true;
    }
  }else{
    digitalWrite(ledPin, LOW);
    myservo.write(5, 30, true);
  }
}

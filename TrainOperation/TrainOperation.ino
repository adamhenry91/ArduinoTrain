



#include <Wire.h>
#include "wiinunchuck.h"
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

const int ledPin =  13;      // the number of the LED pin

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
int loop_cnt=0;
int trainSpeed = 0;

byte accx,accy,zbut,cbut,joyx,joyy;

void setup()
{
    //Serial.begin(19200);
    pinMode(ledPin, OUTPUT);
    nunchuk_setpowerpins();
    nunchuk_init(); // send the initilization handshake
    AFMS.begin();
        
    //Serial.print("WiiChuckDemo ready\n");}
}
void loop()
{
    if( loop_cnt > 100 ) { // every 100 msecs get new data
        loop_cnt = 0;

        nunchuk_get_data();
        accx  = nunchuk_accelx(); // ranges from approx 70 - 182
        //accy  = nunchuk_accely(); // ranges from approx 65 - 173
        zbut = nunchuk_zbutton();
        cbut = nunchuk_cbutton(); 
        joyx = nunchuk_joy_x();
        joyy = nunchuk_joy_y();
           
        //Serial.print("accx: "); Serial.print((byte)accx,DEC);
        //Serial.print("\taccy: "); Serial.print((byte)accy,DEC);
        //Serial.print("\tzbut: "); Serial.print((byte)zbut,DEC);
        //Serial.print("\tcbut: "); Serial.print((byte)cbut,DEC);
        //Serial.print("\joyx: "); Serial.print((byte)joyx,DEC);
        //Serial.print("\joyy: "); Serial.println((byte)joyy,DEC);
        
        
   
  if (zbut ==1)  {
   digitalWrite(ledPin,HIGH);
  
   myMotor->setSpeed(trainSpeed);
   //delay(100);
  }
  else if (cbut ==1)  {
   digitalWrite(ledPin,HIGH); 
   trainSpeed = 0;
   myMotor->run(RELEASE);
   myMotor->setSpeed(trainSpeed);
  }
  else if (joyy < 50) {
   
    digitalWrite(ledPin, HIGH);
    trainSpeed = trainSpeed = trainSpeed + 3;
   trainSpeed = constrain(trainSpeed, 100, 250);
   myMotor->run(BACKWARD);
   myMotor->setSpeed(trainSpeed);
  }
  else if (joyy > 250) {
    
    digitalWrite(ledPin, HIGH);
    trainSpeed = trainSpeed = trainSpeed + 3;
   trainSpeed = constrain(trainSpeed, 100, 250);
   myMotor->run(FORWARD);
   myMotor->setSpeed(trainSpeed);
  }
  else {
   digitalWrite(ledPin,LOW);
   if (trainSpeed > 100) {
     trainSpeed = trainSpeed -3;
   }
   else {
     
    trainSpeed = 0; 
    myMotor->run(RELEASE);
   }
   
   myMotor->setSpeed(trainSpeed);
  }
                
    }
    loop_cnt++;
    delay(1);
}


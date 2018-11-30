/*MOFIZA - The Humanoid Smart Robot made with just Arduino
 * By Ashraf Minhaj  ashraf_minhaj@yahoo.com
 * https://ashrafminhajfb.blogspot.com
 *http://youtube.com/c/fusebatti */
 
#include "ServoTimer2.h"      //declare ServoTimer2 library to run servo with TMRpcm
#include"SD.h"                //declare SD library for SD cards
#define SD_ChipSelectPin 10   //select sd chip select pin 10
#include"TMRpcm.h"            //library to play audio from sd card by arduino
#include"SPI.h"              //create Serial peripheral Interface Communication
TMRpcm tmrpcm;              //name tmrpcm
ServoTimer2 head;           //declare Head servo followed by left right hand servos
ServoTimer2 lhand;
ServoTimer2 rhand;

int in1= 6;               //declare Infrared sensor pins
int in2= 7;
int in3= 8;

void setup() 
{
 head.attach(2);        //attach servos to pins
 lhand.attach(3);
 rhand.attach(4);
 tmrpcm.speakerPin=9;   //Speaker pin 9,audio out pin is 9
 
 Serial.begin(9600);    //initialize Serial communication
 
 if(!SD.begin(SD_ChipSelectPin))   //this runs until SD is connected
 {
  Serial.println("SD FAIL");
  return; 
 }

}

void loop() 
{
  if(!(digitalRead(in3)))          //Chest sensor is low- Say "Hi there.."
  {
   tmrpcm.play("welcome.wav");     //Playing audio saved as 'welcome.wav'
    lhand.write(2500);            //hand up- saying HI
    delay(2000);
    lhand.write(1200);            //hand comes to handshake position
    
    delay(9000);
    
  }
 
  if(!(digitalRead(in1)))       //Sensor on eye gets low play audio -"dont touch my eye"
  {
    tmrpcm.play("dont.wav");     //play file saved as "dont.wav" - dont touch my eye 
    rhand.write(300);            //hand up
    head.write(2000);
    delay(3000);
  }
 
  if(!(digitalRead(in2)))     //Sensor on eye gets low play audio -"dont touch my eye"
  {
    tmrpcm.play("dont.wav");
    lhand.write(2000);
    head.write(1000);
    delay(3000);
  }
 
 else             //No input detected - keep the robot steady.
 {
  
  lhand.write(300);
  rhand.write(1700);
  head.write(1500);
 }
}

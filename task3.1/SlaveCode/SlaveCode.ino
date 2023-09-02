// Slave code

//Include I2C libarary
#include <Wire.h>
//define push buttons pins
#define PushButton_1   2
#define PushButton_2   3

//declare the variables 
	int state,state1,state2;
//declare the function upon request recieved from master
	void sendState();

void setup()
{
  //Initiate I2C communication protocol with slave address 12
  Wire.begin(12);
  Wire.onRequest(sendState);
  //Initiate serial communication with serial monitor
  Serial.begin(9600);
  //Set pin mode of the push buttons to input
  pinMode(PushButton_1, INPUT);
  pinMode(PushButton_2, INPUT);
  
  
}

void loop()
{
  //Read the push buttons state
  state1 = digitalRead(PushButton_1);
  state2 = digitalRead(PushButton_2);
  //if condition to determine the case to send it to master
  if (state1==0 && state2==0 ){
     state = 1 ;
  }
  if (state1==1 && state2==0 ){
     state = 2 ;
  }
   if (state1==0 && state2==1 ){
     state = 3 ;
  }
   if (state1==1 && state2==1 ){
     state = 4 ;
  }
  
  //Send the state of push buttons to the serial monitor
  Serial.println(state);
  delay(50);

}
//Implement function called upon recieving request from master
void sendState()
{
  //Send the state of push buttons via I2C protocol
  Wire.write(state);

}


//Master code

//Include I2C libarary
#include <Wire.h>
//define Led pin
#define Led 3
//declare a variable to store the recieved case
	int Case ;
void setup()
{
  //Initiate I2C communication protocol
  Wire.begin();
  //Initiate serial communication with serial monitor
  Serial.begin(9600);
  //Set pin mode of the Led to output
  pinMode(Led, OUTPUT);
  
}

void loop()
{
  //Request data from address 12 of size 2 bytes
  Wire.requestFrom(12,2);
  //Check if there is available data in the reciever buffer
  if(Wire.available())
  {
    //Read the data and store it in Case
    Case = Wire.read();
    delay (10);
  //switch function to select the suitable case
  switch (Case) {
    case 1:
      //if B1=0 and B2=0 then led brightness =0%
      analogWrite(Led, 0);
      delay(50);
     break;

    case 2:
      //if B1=1 and B2=0 then led brightness =50%
      analogWrite(Led, 128);
      Serial.println("Vector focused");
      delay(50);
     break;

    case 3:
      //if B1=0 and B2=1 then led brightness =75%
      analogWrite(Led, 192);
      Serial.println("Vector distracted");
      delay(50);
     break;

    case 4:
      //if B1=1 and B2=1 then led brightness =100%
     analogWrite(Led, 255);
     Serial.println("Glitch");
     delay(50);
     break;
      
    default:
     break;
  	}
  }
  

}

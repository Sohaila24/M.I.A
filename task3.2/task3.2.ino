//include sensor library
#include <NewPing.h>

//declare variables for Sensor pins
#define TriggerPin_S1 2
#define EchoPin_S1 3
#define TriggerPin_S2 4
#define EchoPin_S2 5
#define TriggerPin_S3 6
#define EchoPin_S3 7
#define TriggerPin_S4 8
#define EchoPin_S4 9
//declare a variable for max distance for each ultrasonic sensor( Maximum distance we want to ping for (in centimeters))
#define MaxDistance 800

//Initiate NewPing setup of pins and maximum distance for each sensor.
NewPing Sensor1(TriggerPin_S1, EchoPin_S1, MaxDistance);
NewPing Sensor2(TriggerPin_S2, EchoPin_S2, MaxDistance);
NewPing Sensor3(TriggerPin_S3, EchoPin_S3, MaxDistance);
NewPing Sensor4(TriggerPin_S4, EchoPin_S4, MaxDistance);

//declare consts float for chamber dimensions in cm
const float chamber_width = 500;
const float chamber_height = 600; 

//delcare a const float for distance between the sensor and the edge of the robot
const float sensor_offset = 5;  

int heading = 0; // current heading of the robot in degrees
float x = 0; // current x position of the robot in cm
float y = 0; // current y position of the robot in cm

void setup() {
  // Open serial monitor at 9600 baud to see ping results.
  Serial.begin(9600);
}

void loop() {
  // measure distances from all four Sensor
  int distance_S1 = Sensor1.ping_cm();
  int distance_S2 = Sensor2.ping_cm();
  int distance_S3 = Sensor3.ping_cm();
  int distance_S4 = Sensor4.ping_cm();

  // calculate x and y position based on the measured distances
  switch (heading) {
    case 0:
      y = distance_S1 - sensor_offset;
      x = chamber_width - distance_S2 - sensor_offset;
      break;
    case 90:
      y = chamber_height - distance_S2 - sensor_offset;
      x = distance_S3 - sensor_offset;
      break;
    case 180:
      y = chamber_height - distance_S3 - sensor_offset;
      x = distance_S4 - sensor_offset;
      break;
    case 270:
      y = distance_S4 - sensor_offset;
      x = chamber_width - distance_S1 - sensor_offset;
      break;
  }

  // print the current position
  Serial.print("Heading: ");
  Serial.print(heading);
  Serial.print(", X: ");
  Serial.print(x);
  Serial.print(", Y: ");
  Serial.println(y);

  // update heading and move the robot forward
  if (heading == 0 || heading == 180) {
    heading += 90;
  } else {
    heading -= 90;
    x += 10; // move the robot forward by 10cm
  }
  
  delay(100);
}
/*Note: I did not know if there is a logical error or 
not because i try to apply this on tinkerCad but there is a problem with NewPing library
*/


// Rotary Encoder Reading and Counting using Interrupts
// Rotary Encoder Pins
#define encoderPinA 2 // Pin 2 is assigned to encoderPinA
#define encoderPinB 3 // Pin 3 is assigned to encoderPinB

// LPF Constants
#define FC 10.0  // Cutoff Frequency in Hz
#define DT 0.01  // Sampling Time in Seconds
#define ALPHA (2 * PI * FC * DT) / (2 * PI * FC * DT + 1)  // LPF Coefficient

// Declare variables to store the encoder counts
volatile long counter = 0; // Variable to store the total count
volatile int lastEncoderA = 0; // Variable to store the previous state of encoderPinA
volatile int lastEncoderB = 0; // Variable to store the previous state of encoderPinB

// Global Variables for LPF
volatile int encoderPos = 0; // Encoder position
int lastEncoderPos = 0; // Last encoder position
float filteredEncoderPos = 0.0; // Filtered encoder position

/* Note :
Volatile is a qualifier that is applied to a variable when it is declared. 
It tells the compiler that the value of the variable may change at any time-without 
any action being taken by the code the compiler finds nearby.
*/


void setup() {
  // Initialize the encoder pins as inputs with internal pull-up resistors enabled
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);

  // Enable interrupts for both encoder pins using attachInterrupt()
  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE);

  // Set up serial communication with a baud rate of 9600
  Serial.begin(9600);
}

void loop() {
  // Print the encoder count every second
  Serial.print("Count: ");
  Serial.println(counter);
  
  // Add a delay of 1 second before printing the next count
  delay(1000);

  // Calculate filtered encoder position using LPF
  filteredEncoderPos = ALPHA * encoderPos + (1 - ALPHA) * lastEncoderPos;

  // Update last encoder position
  lastEncoderPos = filteredEncoderPos;
  
  delay(10); // Sampling time of 10 ms

}

// Define the interrupt service routine for the encoder pins
void updateEncoder() {
  // Read the current state of the encoder pins
  int encoderA = digitalRead(encoderPinA);
  int encoderB = digitalRead(encoderPinB);

  // Update the count based on the direction of rotation
  if (encoderA != lastEncoderA) {
    if (encoderA == encoderB) {
      // Encoder is rotating clockwise, so increment the count
      counter++;
    } else {
      // Encoder is rotating counterclockwise, so decrement the count
      counter--;
    }
  }

  // Save the current state of the encoder pins for the next interrupt
  lastEncoderA = encoderA;
  lastEncoderB = encoderB;
}

# Table of Contant

- [Table of Contant](#table-of-contant)
  - [Rotary Encoder Reading and Counting using Interrupts](#rotary-encoder-reading-and-counting-using-interrupts)
    - [Pins](#pins)
    - [Low-Pass Filter Constants](#low-pass-filter-constants)
    - [Variables](#variables)
    - [Functions Used](#functions-used)
      - [void setup()](#void-setup)
      - [void loop()](#void-loop)
    - [Update Encoder Function](#update-encoder-function)

## Rotary Encoder Reading and Counting using Interrupts

This code uses a rotary encoder to measure the position of a motorized wheel. It implements a low-pass filter to smooth out the readings and reduce noise. The cutoff frequency of the filter is calculated based on the maximum speed of the wheel, the number of pulses per revolution of the encoder, and the radius of the wheel. The filtered encoder position is printed to the serial monitor every 10 ms.

### Pins
---
The rotary encoder pins are defined as follows:
- Pin 2 is assigned to encoderPinA  
  `#define encoderPinA 2`
-  Pin 3 is assigned to encoderPinB  
  `#define encoderPinB 3`

### Low-Pass Filter Constants
---

The cutoff frequency and sampling time of the low-pass filter are defined as follows :

```c++
#define FC 10.0  // Cutoff Frequency in Hz   
#define DT 0.01  // Sampling Time in Seconds
```

The LPF coefficient is calculated as follows:  
`#define ALPHA (2 * PI * FC * DT) / (2 * PI * FC * DT + 1) ` 

To determine the proper cutoff frequency for the LPF, we can use the following formula:  
`fc = Vmax / (2 * PI * PPR * r)`
 
In this case,the cutoff frequency is :   
`fc = 0.5 / (2 * PI * 540 * 0.2) ≈ 10 Hz`  
Therefore, a cutoff frequency of 10 Hz should be appropriate for this application.

### Variables
---
The following variables are declared:
counterVariable to store the total count
- **lastEncoderA**: A variable to store the previous state of encoderPinA
- **lastEncoderB** : A variable to store the previous state of encoderPinB
- **encoderPos** : A variable to store Encoder position
- **lastEncoderPos** : A variable to store the Last encoder position
- **filteredEncoderPos** : A variable to store the filtered encoder position


### Functions Used
---
#### void setup()

The setup function initializes the encoder pins as inputs with internal pull-up resistors enabled. It also enables interrupts for both encoder pins using attachInterrupt(). Finally, it sets up serial communication with a baud rate of 9600.

```c++
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
```

#### void loop()

The loop function prints the encoder count every second using Serial.print() and Serial.println(). It also calculates the filtered encoder position using the LPF and updates the last encoder position. Finally, it adds a delay of 10 ms for sampling time.

```C++
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
```


### Update Encoder Function

The `updateEncoder()` function is called whenever an interrupt is triggered by a change in the state of either encoder pin. It reads the current state of the encoder pins and updates the count based on the direction of rotation. It also saves the current state of the encoder pins for the next interrupt.

```C++
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
```
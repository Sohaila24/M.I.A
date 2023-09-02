#include <stdio.h>
#include <stdlib.h>

#define NumSamples 100

// Function to calculate the weighted average of two sensor measurements
float kalman_filter(float sensor1[], float sensor2[]) {
    float measurement[NumSamples];
    float weight1 = 0.79; // Accuracy of sensor 1
    float weight2 = 0.92; // Accuracy of sensor 2

    for (int i = 0; i < NumSamples; i++) //for loop to get the measurements in array
    {

        measurement[i] = (weight1 * sensor1[i] + weight2 * sensor2[i]) / (weight1 + weight2); // calculate the average measurement

    }
    return measurement; // I did not know how to return an array
}


int main() {
    float mpu6050[10] = {0.0, 11.68, 18.95, 23.56, 25.72, 25.38, 22.65, 18.01, 10.14, -0.26};
    float bno55[10] = {0.0,9.49, 16.36, 21.2, 23.16, 22.8, 19.5, 14.85, 6.79, -2.69};

    char measurement = kalman_filter(sensor1, sensor2);

    printf("Kalman filter output: %f\n", measurement);

    return 0;
}

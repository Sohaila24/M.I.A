
/* Header Files */
#include <stdio.h>  // Standard I/O functions
#include <stdlib.h> // Standard library functions

/* Main Function */
int main()
{
    int number; // variable declaration
    printf("Enter the number :");
    scanf("%d",&number); //take number from user
    if (number > 0){ // check if the input number is a positive number

            for (int i=number;i>0;i--){ //loop for countdown from the input number to zero
            printf("%d\n",i);
            sleep (1); // delay one sec (BONUS)
            }
            printf("\nBlast off to the moon!\n");
    }
    else{   //if the input number is a negative number print this message
        printf("\n Please enter a positive integer number ^-^\n");
        }

    return 0;
}

/* Header Files */
#include <stdio.h>  // Standard I/O functions
#include <stdlib.h> // Standard library functions
#include <string.h> // Library for manipulating strings

#define MaxTasks 1000 //Define max number of tasks = 1000

/* Function Declarations */

/** AddTask
 * @brief The function take the input task and add it to tasks array
 * @param none
 * @return none
 */

 /** ViewTasks
 * @brief The function show tasks array
 * @param none
 * @return none
 */

/** RemoveTask
 * @brief The function take the input task and remove it from tasks array
 * @param none
 * @return none
 */

//Defining a struct for the input task
struct Task {
    int id;     //Id
    char description[100]; //Description
};

//Declaring an array for input tasks
struct Task tasks[MaxTasks];
int numTasks = 0;


void AddTask() {
    struct Task task; //declaring a struct for the input task
    printf("Task ID: ");
    scanf("%d", &task.id);  //Take task id
    for (int i = 0; i < numTasks; i++) { //for loop to put the input task in tasks array
        if (tasks[i].id == task.id) {
            //if the user input id is exist print this message
            printf("Task id %d already exists.\n", task.id);
            return;
        }
    }
    printf("Task description: ");
    scanf(" %[^\n]", task.description); //take task description
    tasks[numTasks++] = task;   //shift to the next task
    printf("\tTask added successfully!\n");
}

void ViewTasks() {
    if (numTasks == 0) {
    //if number of tasks =0 print "No tasks found"
        printf("No tasks found.\n");
        return;
    }
    else{
        //print exixt tasks in a table format
        printf("Current Tasks:\nTask_Number\tID\tDescription\t\t\n");
        printf("------------------------------------\n");
    for (int i = 0; i < numTasks; i++)
    {
        //for loop to print the exist tasks (task number'starting from one' ,task id, task description )
        printf("   %d\t\t%d\t%-30s\t\n",i+1,tasks[i].id, tasks[i].description);
    }
    }
}

void RemoveTask() {
  int id;   //declare a variable for the removed task id
    printf("Task ID:");
    scanf("%d", &id);
    getchar(); // consume newline character

    int index = -1; //declaring and initializing index
    for (int i = 0; i < numTasks; i++) { //for loop to check if the input id is existed
        if (tasks[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Task not found.\n");
        return;
    }

    for (int i = index; i < numTasks - 1; i++) { // for loop to remove the task
        tasks[i] = tasks[i + 1];    //put the next task in the removed task index
    }

    numTasks--; //reduce one fron=m number of tasks
    printf("\tTask removed successfully!\n");
}



int main() {
    printf("Minions Task Manager:\n1.Add task\n2.View tasks\n3.Remove task\n4.Exit\n\n");

    int choice;    //declaring a variable for user choice
    do {

        printf("\nSelect an option: ");
        scanf("%d", &choice); //switch function for tasks list
        switch (choice) {
            case 1:
                AddTask();
                break;
            case 2:
                ViewTasks();
                break;
            case 3:
                RemoveTask();
                break;
            case 4:
                printf("Exiting Minions Task Manager. Have a great day!\n");
                break;
            default:
                printf("Invalid choice.\n"); // if the user put a different choice than 1,2,3 or 4 print "invalid choice"
                break;
        }
    } while (choice != 4);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudoku.h"
#include "admin.h"

#define ADMIN_PASSWORD "admin123"  


int main() {
    menuSudoku();  

    char enteredPassword[50];
    int attempts = 3; 

    while (attempts > 0) {
        printf("\n\n\n\n\n\t\t\t\t\t\t Enter the admin password to access the admin menu: ");
        scanf("%49s", enteredPassword);  

        if (strcmp(enteredPassword, ADMIN_PASSWORD) == 0) {
            printf("\nAccess granted.\n");
            menuAdmin();  
            break;
        } else {
            attempts--;
            printf("\nIncorrect password. You have %d attempt(s) left.\n", attempts);
            if (attempts == 0) {
                printf("Access denied. Exiting program.\n");
                return 0;  
            }
        }
    }

    return 0;
}

//    gcc -Wall -Wextra -g3 main.c sudoku.c partie.c admin.c -o output/main.exe




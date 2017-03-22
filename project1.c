#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"


/*****************************************************************
*
* NAME: Oliver Sou
*
* HOMEWORK: project1
*
* CLASS: ICS 212
*
* INSTRUCTOR: Ravi Narayan
*
* DATE: March 9, 2017
*
* FILE: project1.c
*
* DESCRIPTION: This file contains the main to execute project1
*
*****************************************************************/


int debugmode = 0;

int main(int argc, char * argv[])
{
    int i;
    struct record * start = NULL;
    char name[25];
    char address[80];
    int boolean = 1;
    int option;
    int accountNo = 0;
    int sizeOfAddress = 80;
    start = NULL;

    if (argc != 1 && strcmp(argv[1] , "debug") == 0) {
        debugmode = 1;
        printf("MAIN: DEBUG MODE IS ON\n");
    } else if (argc != 1 && strcmp(argv[1] , "debug") != 0) {
        printf("No such mode or file. Please enter a valid option such as: ./project1 debug\n");
        boolean = 0;
    }


    do {
        readfile(*start, "data.txt");
        
		printf("\n*********** MENU **********\n");
		printf("Select an option by entering its respective number\n");
		printf("1 : Add a new record      \n");
		printf("2 : Print record          \n");
		printf("3 : Modify a record       \n");
		printf("4 : Print all records     \n");
		printf("5 : Delete a record       \n");
		printf("6 : Quit the program      \n");
		printf("\nEnter your choice: ");

        scanf("%d" , &option);

	    switch (option) {
			case 1:
                printf("Enter your account number: ");
                scanf("%d" , &accountNo);
                printf("Enter your name: ");
                i = strlen(name) - 1;
                if(name[i] == '\n')
                {
                name[i] = '\0';
                }
                fflush(stdin);
                fgets(name , 25, stdin);
                printf("Enter your address: \n");
                getaddress(address, sizeOfAddress);
                addRecord(&start, accountNo, name, address);
                break;

            case 2:
                printf("Enter account number: ");
                scanf("%d" , &accountNo);
                printf("Enter new address: \n");
                getaddress(address, sizeOfAddress);
                modifyRecord(start, accountNo, address);
                break;

            case 3:
                printf("Enter account number: ");
                scanf("%d", &accountNo);
                printf("Printing record\n");
                printRecord(start, accountNo);
                break;

            case 4:
                printf("Printing all records\n");
                printAllRecords(start);
                break;

            case 5:
                printf("Enter account number: ");
                scanf("%d", &accountNo);
                printf("Deleting record\n");
                deleteRecord(&start, accountNo);
                break;

            case 6:
                writefile(start, "data.txt");
                boolean = 0;
                break;

            default:
                printf("Option is not valid. Please enter a valid number. \n");
                break;
	        }
	  } while(option != 6);

	  return 0;
}

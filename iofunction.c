/*****************************************************************
*
* HOMEWORK: project1
*
* CLASS: ICS 212
*
* FILE: iofunction.c
*
* DESCRIPTION: This file contains data base fucntion defenitions for project1
*
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
#include "prototype.h"

extern int debugmode;

/*****************************************************************
*
* Function name: getaddress
*
* DESCRIPTION: Obtains address from the user, output in a single line
*
* Notes:
*
* Parameters: char address[ ], int sizeOfAddress
*
*****************************************************************/

void getaddress (char address[ ], int sizeOfAddress)
{
    char c;
    int boolean = 1;
    int i = 0;
    printf("After you have typed in your address enter a dollar sign '$'  \n");
    while(boolean == 1){
        c = fgetc(stdin);
        if(c == '$') {
            break;
        }
        address[i] = (char) c;
        i++;
    }
    address[i] = '\0';
    if(debugmode == 1){
        printf("The getaddress function is being called. The parameters being passed are address(character array, address: %p, size: %lu, value: %s) and sizeOfAddress(int, address: %p, size: %lu, value: %d). \n", (void*)&address, sizeof(&address), address, (void*)&sizeOfAddress, sizeof(sizeOfAddress), sizeOfAddress);
    }
}

/*****************************************************************
*
* Function name: addRecord
*
* DESCRIPTION: Adds a new record to the beginning of the database
*
* Parameters: struct record **:    pointer to next null entry for new record
*             int accnum:          account numer for the new record
*             char name[]:         name for the new record
*             char addr[]:         address for the new record
*
* Return values: 1:    success
*                0:    failure
*
*****************************************************************/

int addRecord (struct record **start,  int accountno, char name[], char address[])
    {
        struct record *previous, *current, *newrecord;
        int sucess;

        newrecord = (struct record *)malloc(sizeof(struct record));
        sucess = 0;
        newrecord->accountno = accountno;
        strcpy(newrecord->name, name);
        strcpy(newrecord->address, address);
        current = *start;
        previous = NULL;

    	/*printf("add start is %p\n",*start);*/

    	if (debugmode == 1)
        {
            printf("\n********DEBUG MODE********\n");
            printf("Called function addRecord\nParameters passed:\nstruct record is %p\naccount number: %d\nname: %s\naddress is %s\n", (void*)&start, accountno, name, address);
            printf("***************************\n\n");
    	}


        /*printf("new number to add is %d\n",newrecord->accountno);*/

    /*add to an empty list*/
        if(*start == NULL)
        {
            newrecord->next = NULL;
            *start=newrecord;
            sucess = 1;
    		/*printf("/add to an empty list/\n");*/
            /*printf("next is %p\n",newrecord->next);*/
        }
        else
        {
            while(current != NULL && sucess == 0)
            {
                /*printf("current acount number is %d\n", current->accountno);*/
                if(newrecord->accountno <= current->accountno)
                {
                    newrecord->next = current;
                    /*printf("current record is %p\n",current);
                    printf("new record next accountno is %d\n",newrecord->next->accountno);*/
    /*add to begining*/
                    if(previous == NULL)
                    {
                        *start=newrecord;
                        sucess = 1;
    					/*printf("/add to begining/\n");*/
                        /*printf("next is %p\n",current->next);*/
                    }
    /*add to in front of*/
                    else
                    {
                        previous->next = newrecord;
                        sucess = 1;
    					/*printf("/add to in front of/\n");*/
                    }
                }
                else if(/*newrecord->accountno > current->accountno &&*/ current->next == NULL)
                {
    /*insert between two record or to the end if next field is NULL*/
    				/*printf("/insert between two record or to the end if next field is NULL/\n");*/
                    /*printf("current acount number is %d\n", current->accountno);*/
                    newrecord->next = current->next;
                    current->next = newrecord;
                    sucess = 1;
                }
    /*step or point previous and current to the next node*/
    			else
    			{
                    /*printf("before move current acount number is %d\n", current->accountno);
                    printf("before move next accountno is %d\n",current->next->accountno);
                    printf("MOVE\n");*/
    				previous = current;
    				current=previous->next;
                    /*printf("after move current acount number is %d\n", current->accountno);*/
    			}
            }
        }
        return sucess;
}

/*****************************************************************
*
* Function name: printRecord
*
* DESCRIPTION: Prints out a record based on the account number given and starting data base pointer
*
* Parameters: struct record *:     header pointer
*             int accnum:          account numer to search for
*
* Return values: 1:    success
*                0:    failure
*
*****************************************************************/

int printRecord (struct record *start, int accountno)
{
    int sucess;
    int printaccount;
    struct record *previous, *current;
    sucess = 0;
    printaccount = accountno;
    current = start;
    previous = NULL;

    if (debugmode == 1)
    {
        printf("\n********DEBUG MODE********\n");
        printf("Function called: printRecord\nParameters passed:\nrecord is %p\naccountno is %d\n", (void*)&start, accountno);
        printf("***************************\n\n");
    }

/*list is empty*/

    if (start == NULL)
    {
        printf("List contains no records\n");
    }

    while(current != NULL)
    {
        if(current->accountno == printaccount)
        {
            printf("Printing records matching account number %d\n",printaccount);
            printf("%d\n%s\n%s\n",current->accountno,current->name,current->address);
			previous = current;
			current=previous->next;
            sucess = 1;
        }
        else
        {
            previous = current;
			current=previous->next;
        }
    }
    return sucess;
}

/*****************************************************************
*
* Function name: modifyRecord
*
* DESCRIPTION: modify record based on account number given
*
* Parameters: struct record **:    header pointer address
*             int accnum:          account numer to search for
*             char name[]:         name to change in the record
*
* Return values: 1:    success
*                0:    failure
*
*****************************************************************/

int modifyRecord (struct record *start, int accountno, char name[ ])
{
    int sucess;
    int modifyaccount;
    struct record *previous, *current;
    sucess = 0;
    modifyaccount = accountno;
    current = start;
    previous = NULL;

    if (debugmode == 1)
    {
        printf("\n********DEBUG MODE********\n");
        printf("Function called: modifyRecord\nParameters passed:\nrecord is %p\naccountno is %d\nname is %s\n", (void*)&start, accountno, name);
        printf("***************************\n\n");
    }

/*list is empty*/

    if (start == NULL)
    {
        printf("List contains no records\n");
    }

    while(current != NULL)
    {
        if(current->accountno == modifyaccount)
        {
            strcpy(current->name, name);
            previous = current;
			current=previous->next;
            sucess = 1;
        }
        else
        {
            previous = current;
			current=previous->next;
        }
    }
    return sucess;
}

/*****************************************************************
*
* Function name: printAllRecord
*
* DESCRIPTION: print all records of the given address book
*
* Parameters:  struct record *:    pointer to the address book header
*
* Return values: N/A
*
*****************************************************************/

void printAllRecords(struct record *start)
{
    struct record *previous, *current;
    current = start;
    previous = NULL;

    if (debugmode == 1)
    {
        printf("\n********DEBUG MODE********\n");
        printf("Function called: printAllRecords\nParameters passed:\nrecord is %p\n", (void*)&start);
        printf("***************************\n\n");
    }

/*list is empty*/

    if (start == NULL)
    {
        printf("List contains no records\n");
    }
    else
    {
        printf("Printing all records\n");
        while(current != NULL)
        {
            printf("%d\n%s\n%s\n",current->accountno,current->name,current->address);
            previous = current;
            current=previous->next;
        }
    }
}

/*****************************************************************
*
* Function name: deleteRecord
*
* DESCRIPTION: delete a record from the address book for the account number given
*
* Parameters: struct record **:    pointer to address book header
*             int accnum:          account numer to searc for
*
* Return values: 1:    success
*                0:    failure
*
*****************************************************************/

int deleteRecord(struct record ** start, int accountno)
{
    struct record *previous, *current, *delete;
    int deleteaccount, sucess;

    sucess = 0;
    deleteaccount = accountno;
    current = *start;
    previous = NULL;

    if (debugmode == 1)
    {
        printf("\n********DEBUG MODE********\n");
        printf("Function called: deletRecord\nParameters passed:\nrecord is %p\naccountno is %d\n", (void*)&start, accountno);
        printf("***************************\n\n");
    }

	/*printf("delete start is %p\n",*start);
	printf("start account is %d\n", *start->accountno);
	printf("current account is %d\n", current->accountno);

    printf("in delete: account number is %d\n", current->accountno);*/
/*list is empty*/

    if (*start == NULL)
    {
        printf("List contains no records\n");
    }
    else
    {
        while(current != NULL)
        {
            /*printf("enter delete while, acount number at current is %d\n", current->accountno);*/
            if(current->accountno == deleteaccount)
            {
                /*printf("delete match found\n");*/
/*delete only node*/
                if(previous == NULL && current->next == NULL)
                {
                    free(current);
                    current = NULL;
                    *start = NULL;
                    sucess = 1;
                    /*printf("/delete only node/\n");*/
                }
/*delete first node*/
                else if(previous == NULL && current->next != NULL)
                {
                    delete = current;
                    *start = current->next;
                    current = current->next;
                    free(delete);
                    sucess = 1;
                    /*printf("/delete first node/\n");*/
                }
/*delete a node in the middle*/
                else if(previous != NULL)
                {
                    previous->next = current->next;
                    delete = current;
                    current = current->next;
                    free(delete);
                    sucess = 1;
                    /*printf("/delete a node in the middle/\n");*/
                }
            }
            else
            {
/*step previous and current to the next node if not nodes were deleted*/
                previous = current;
                current=previous->next;
            }
        }
    }
    return sucess;
}

/*****************************************************************
*
* Function name: readfile
*
* DESCRIPTION: loads the data file
*
* Parameters:  **start , filename
*
* Return values: int
*
*****************************************************************/

int readfile( struct record **start, char filename[ ] )
{
    int i;
    int j = 1;
    char line[150];
    FILE * fPointer;
    struct record *temp;
    temp = *start;
    fPointer = fopen(filename, "r");

    if(fPointer != NULL) {
        while(!feof(fPointer)) {
            for(i = 1; fgets(line, sizeof(line), fPointer); i++){
                    switch(i % 3) {
                        case 0:
                            fscanf(fPointer, "%s", temp ->accountno);
                            printf("Customer: %d, AccountNo: %8.2f\n", j, temp ->accountno);
                            j++;
                            break;

                        case 1:
                            fscanf(fPointer, "%s", temp ->name);
                            printf("Customer: %d, Name: %s\n", j, temp ->name);
                            break;

                        case 2:
                            fscanf(fPointer, "%s", temp ->address);
                            printf("Customer: %d, Address: %s\n", j, temp ->address);
                            break;

                        default:
                            fprintf(fPointer, "%s", "Error");
                            break;
                    }
            }
        }
    }
    else
        printf("ERROR. No file found");

    fclose(fPointer);
    return 0;
}

/*****************************************************************
*
* Function name: writefile
*
* DESCRIPTION: saves the data file
*
* Parameters:  **start , filename
*
* Return values: int
*
*****************************************************************/


void writefile( struct record * start, char filename[ ] )
{
    FILE * fPointer;
    struct record *temp;
    temp = start;
    fPointer = fopen(filename, "w");

    if (fPointer == NULL) {
      fprintf(stderr, "Can't open output file %s!\n", filename);
      exit(1);
    }

    while(temp != NULL)
    {
        //printf("%s %d\n",accarray->name, accarray->accountno);
        fprintf(fPointer, "AccNo: %i, Name: %s, Address: %s\n", temp ->accountno, temp ->name, temp ->address);
        temp = temp->next;
    }
    printf("CLOSING THE FILE\n");
    fclose(fPointer);
}

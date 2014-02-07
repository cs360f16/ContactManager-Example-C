/****************************************************************************
File name:	main.c
Author:		chadd williams
Date: 		2/6/2014
Class: 		CS 360, Fall 2014
Assignment: Example Open Source Development with Git
Purpose: 	This file contains the main function and driver for the project.
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/EntryData.h"

/****************************************************************************
Function: 	getField
Description:ask the user which field they want and return that Field
Parameters:	none

Returned: 	the field the user selects
****************************************************************************/
Field getField()
{
	Field theField;

	printf("\n0. First Name\n");
	printf("1.Last Name\n");
	printf("2. Email\n");
	scanf("%d", &theField);
	return theField;
}

/****************************************************************************
Function: 	getString
Description:ask the user for a string based on the fieldParameters:	none
Parameters:	pBuf the string to return
						theField - the field to request

Returned: 	none
****************************************************************************/

void getString(char* pBuf, Field theField)
{
	printf("What string in the field ");
	switch(theField)
	{
		case 0:
			printf("First Name");
			break;
		case 1:
			printf("Last Name");
			break;
		case 2:
			printf("Email");
			break;
	}
	printf(" do you want to search for? ");
	scanf("%1024s",pBuf);
}

/****************************************************************************
Function: 	getNewContact
Description:ask the user for a full contact
Parameters:	psFName - the first name
						psLName - the last name
						psEmail - the email

Returned: 	none
****************************************************************************/
void getNewContact(char* psFName, char* psLName, char* psEmail)
{
	printf("First Name: ");
	scanf("%1024s", psFName);

	printf("Last Name: ");
	scanf("%1024s", psLName);

	printf("Email: ");
	scanf("%1024s", psEmail);

}

/****************************************************************************
Function: 	getFilename
Description:ask the user for a filename
Parameters:	psFilename - the filename
Returned: 	none
****************************************************************************/
void getFilename(char *psFilename)
{
	printf("File Name: ");
	scanf("%1024s", psFilename);
}

/****************************************************************************
Function: 	prinMainMenu
Description:display the main menu
Parameters:	none

Returned: 	none
****************************************************************************/
void printMainMenu()
{
	printf("\n\n");
	printf("1. Print to screen\n");
	printf("2. Search\n");
	printf("3. Add Contact\n");
	printf("4. Delete Contact\n");
	printf("5. Write to file\n");
	printf("6. Quit\n");
	printf("\n");
}

/****************************************************************************
Function: 	main
Description:main driver for the project
Parameters:	none

Returned: 	EXIT_SUCCESS on success, anything else on failure
****************************************************************************/
int main()
{
	EntryData allData;
	int choice;
	Field theField;
	char buffer[1024];
	char psFName[1024], psLName[1024], psEmail[1024];
	char psFilename[1024];
	int index;
	int continueLooping = 1;
	int pResults[1024];

	edInitData(&allData);
	edReadData(&allData,"data/contacts.txt");

	while(continueLooping)
	{
		do
		{
			printMainMenu();
			scanf("%d", &choice);
		}while( choice < 1 || choice > 6);

		switch(choice)
		{
			case 1:
				edPrintEachContactToStdout(&allData);
				break;
			case 2:
				theField = getField();
				getString(buffer, theField);
				index = edSearchData(&allData, buffer, theField, pResults, 1024);
				if( index > 0)
				{
					edPrintContactToStdout(&allData, index);
				}
				else
				{
					printf("Not Found.\n");
				}
				break;
			case 3:
				getNewContact(psFName, psLName, psEmail);
				edAddContact(&allData, psFName, psLName, psEmail);
				break;
			case 4:
				theField = getField();
				getString(buffer, theField);
				index = edSearchData(&allData, buffer, theField, pResults, 1024);
				if( index > 0)
				{
					edDeleteContact(&allData, index);
				}
				else
				{
					printf("Not Found.\n");
				}
				break;
			case 5:
				getFilename(psFilename);
				edWriteData(&allData, psFilename);
				break;
			case 6:
				continueLooping = 0;
				break;
			default:
				break;
		}
	}
	edDeleteData(&allData);
	return EXIT_SUCCESS;
}

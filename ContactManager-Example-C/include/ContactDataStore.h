/****************************************************************************
File name:  ContactDataStore.h

Author: 	chadd

Date: 		Feb 7, 2014

Class:

Assignment:

Purpose:
****************************************************************************/


/****************************************************************************
Function: 

Description: 

Parameters: 

Returned: 
****************************************************************************/
#ifndef CONTACTDATASTORE_H_
#define CONTACTDATASTORE_H_

#include "../include/ContactEntry.h"
#include <stdlib.h>

typedef struct ContactDataStore
{
	ContactEntry *pArray;
	int numberOfUsedContacts;
	int numberOfContacts;
	int current;
} ContactDataStore;

int dsInit(ContactDataStore *pData);
int dsDelete(ContactDataStore *pData);
int dsAddEntry(ContactDataStore *pData, ContactEntry *pEntry);
int dsDeleteEntry(ContactDataStore *pData);
int dsGetEntry(ContactDataStore *pData, ContactEntry *pEntry, int index);
int dsEditEntry(ContactDataStore *pData, ContactEntry *pEntry);
int dsGetNumberOfContacts(ContactDataStore *pData);

int dsFirst(ContactDataStore *pData);

int dsNext(ContactDataStore *pData);

int dsCurrent(ContactDataStore *pData, ContactEntry *pEntry);

#endif /* CONTACTDATASTORE_H_ */

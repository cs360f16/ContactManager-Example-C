/****************************************************************************
File name:  ContactDataStore.c

Author: 	chadd

Date: 		Feb 7, 2014

Class:

Assignment:

Purpose:
****************************************************************************/
#include "../include/ContactDataStore.h"
#include "../include/EntryData.h"
#include <string.h>

const int INITIAL_CONTACTS = 10;
static const int ED_ERROR = -1;

/****************************************************************************
Function: 

Description: 

Parameters: 

Returned: 
****************************************************************************/

int dsInit(ContactDataStore *pData)
{
	if( NULL == pData )
	{
		return ED_ERROR;
	}

	pData->pArray = calloc(INITIAL_CONTACTS, sizeof(EntryData) );

	pData->numberOfContacts = INITIAL_CONTACTS;
	pData->numberOfUsedContacts = 0;
	pData->current = -1;

	return pData->numberOfContacts;
}

int dsDelete(ContactDataStore *pData)
{
	int i;
	for(i = 0; i< pData->numberOfUsedContacts; i++)
	{
		free(pData->pArray[i].psEmail);
		free(pData->pArray[i].psFName);
		free(pData->pArray[i].psLName);
	}
	free(pData->pArray);

	pData->pArray = NULL;
	pData->numberOfContacts = 0;
	pData->numberOfUsedContacts = 0;

	return 1;
}

int dsAddEntry(ContactDataStore *pData, ContactEntry *pEntry)
{
	if( (pData->numberOfUsedContacts+1) > pData->numberOfContacts )
	{
		//realloc is magic
		pData->pArray = realloc(pData->pArray,
				(pData->numberOfContacts * 2) * sizeof(ContactEntry));
		pData->numberOfContacts = pData->numberOfContacts * 2;
	}

	pData->pArray[pData->numberOfUsedContacts].psFName =
			calloc(strlen(pEntry->psFName) + 1, sizeof(char));
	memcpy(pData->pArray[pData->numberOfUsedContacts].psFName,
			pEntry->psFName, strlen(pEntry->psFName));

	pData->pArray[pData->numberOfUsedContacts].psLName =
			calloc(strlen(pEntry->psLName) + 1, sizeof(char));
	memcpy(pData->pArray[pData->numberOfUsedContacts].psLName,
			pEntry->psLName, strlen(pEntry->psLName));

	pData->pArray[pData->numberOfUsedContacts].psEmail =
			calloc(strlen(pEntry->psEmail) + 1, sizeof(char));
	memcpy(pData->pArray[pData->numberOfUsedContacts].psEmail,
			pEntry->psEmail, strlen(pEntry->psEmail));


	pData->current = pData->numberOfUsedContacts;

  pData->numberOfUsedContacts++;

	return pData->numberOfUsedContacts;
}

int dsDeleteEntry(ContactDataStore *pData)
{
	int i;

	free(pData->pArray[pData->current].psEmail);
	free(pData->pArray[pData->current].psFName);
	free(pData->pArray[pData->current].psLName);

	for(i=pData->current;i<pData->numberOfUsedContacts-1;i++)
	{
		// since we are just copying pointers we can
		// use a struct copy
		pData->pArray[i] = pData->pArray[i+1];
	}

	pData->numberOfUsedContacts --;
	pData->current = 0;
	return pData->numberOfUsedContacts;
}

int dsGetEntry(ContactDataStore *pData, ContactEntry *pEntry, int index)
{
	int retVal = -1;
	if( index < pData->numberOfUsedContacts)
	{
		memcpy(pEntry, &( pData->pArray[index]), sizeof(ContactEntry));
		retVal = index;
	}
	return retVal;
}

int dsEditEntry(ContactDataStore *pData, ContactEntry *pEntry);

int dsFirst(ContactDataStore *pData)
{
	pData->current = 0;
	return pData->current;
}

int dsNext(ContactDataStore *pData)
{
	int result = 0;
	pData->current ++;
	if( pData->current < pData->numberOfUsedContacts)
	{
		result = 1;
	}
	return result;
}

int dsCurrent(ContactDataStore *pData, ContactEntry *pEntry)
{
	memcpy(pEntry, &(pData->pArray[pData->current]), sizeof(ContactEntry));
	return pData->current;
}
int dsGetNumberOfContacts(ContactDataStore *pData)
{
	return pData->numberOfUsedContacts;
}

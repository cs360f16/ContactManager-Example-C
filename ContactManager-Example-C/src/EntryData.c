/****************************************************************************
File name:  EntryData.c

Author: 	chadd

Date: 		Feb 6, 2014

Class: 		CS 360, Fall 2014
Assignment: Example Open Source Development with Git


Purpose:
****************************************************************************/

#include "../include/EntryData.h"
#include "../include/ContactDataStore.h"
#include <stdio.h>
#include <string.h>

static const int ED_ERROR;

/****************************************************************************
Function: 		edInitData

Description: 	Initialize the data in pData.
							allocate a small number of contacts and set the counters
							correctly.  The user must eventually call edDeleteData to
							free all memory.

Parameters: 	pData - struct containing the data

Returned: 		number of contacts allocated, -1 on error
****************************************************************************/
int edInitData(EntryData *pData)
{
	pData->pDataStore = calloc(1, sizeof(ContactDataStore));
	return dsInit(pData->pDataStore);
}

/****************************************************************************
Function: 		edDeleteData

Description: 	Free all the dynamic memory held by this data object.

Parameters: 	pData - struct containing the data

Returned: 		1 on success, -1 on failure.
****************************************************************************/

int edDeleteData(EntryData *pData)
{
	int i;

	if( NULL == pData )
	{
		return ED_ERROR;
	}

	i = dsDelete(pData->pDataStore);
	free(pData->pDataStore);

	return i;
}

/****************************************************************************
Function:		edReadData

Description:	Read data from the file psFilename into pData.  The format of
							the file is:
							number of contacts
							fname,lname,email
							<repeat>

							Each line can be at most 1024 characters

Parameters: 	pData the data to fill.  edInitData must have been called on this
							data previously.
							psFilename the file to read from.

Returned:			int - number of contacts read or -1 on error.
****************************************************************************/
int edReadData(EntryData *pData, char *psFilename)
{
	FILE *pFile;
	char *pSavePtr;
	char *pToken;
	int i;

	int count;
	const int MAX_BUF_SIZE=1024;
	char buf[MAX_BUF_SIZE];

	ContactEntry entry;

	if (NULL == pData || NULL == psFilename)
	{
		return ED_ERROR;
	}
	pFile = fopen(psFilename, "r");
	if(NULL == pFile )
	{
		return ED_ERROR;
	}

	// read the number of contacts
	fgets(buf, MAX_BUF_SIZE, pFile);
	count = atoi(buf);

	// read each contact
	for(i=0; i< count; i++)
	{
		fgets(buf, MAX_BUF_SIZE, pFile);
		pToken = strtok_r(buf,",\n",&pSavePtr);
		entry.psFName = calloc(strlen(pToken) + 1, sizeof(char));
		memcpy(entry.psFName, pToken, strlen(pToken));

		pToken = strtok_r(NULL,",\n",&pSavePtr);
		entry.psLName = calloc(strlen(pToken) + 1, sizeof(char));
		memcpy(entry.psLName, pToken, strlen(pToken));


		pToken = strtok_r(NULL,",\n",&pSavePtr);
		entry.psEmail = calloc(strlen(pToken) + 1, sizeof(char));
		memcpy(entry.psEmail, pToken, strlen(pToken));

		dsAddEntry(pData->pDataStore, &entry);

		free(entry.psFName);
		free(entry.psLName);
		free(entry.psEmail);
	}
	fclose(pFile);

	return count;
}

/****************************************************************************
Function:		edWriteData

Description:	Write contact data back to a file

Parameters:	pData the data to write
						psFilename the file to write to

Returned:		int - number of contacts written or -1 on error.
****************************************************************************/
int edWriteData(EntryData *pData, char *psFilename)
{
	int i;
	int result = 1;
	FILE *pFile;
	const int MAX_BUF_SIZE = 1024;
	char buf[MAX_BUF_SIZE];
	ContactEntry entry;

	if (NULL == pData || NULL == psFilename)
	{
		return ED_ERROR;
	}
	pFile = fopen(psFilename, "w");
	if(NULL == pFile )
	{
		return ED_ERROR;
	}

	int count = dsGetNumberOfContacts(pData->pDataStore);
	// write the number of contacts
	sprintf(buf, "%d\n",count);
	fwrite(buf, sizeof(char), strlen(buf), pFile);

	dsFirst(pData->pDataStore);
	// write each contact
	for( i=0; i< count && result == 1; i++)
	{
		dsCurrent(pData->pDataStore, &entry);

		sprintf(buf, "%s,%s,%s\n", entry.psFName,
				entry.psLName, entry.psEmail);
		fwrite(buf, sizeof(char), strlen(buf), pFile);
		result = dsNext(pData->pDataStore);
	}

	fclose(pFile);
	return count;
}

/****************************************************************************
Function:

Description:

Parameters:

Returned:
****************************************************************************/
int edSortData(EntryData *pData, Field sortType)
{
	return 1;
}

/****************************************************************************
Function: 	edAddContact

Description:	Add a contact to the end of the list

Parameters:	pData - the list of contacts
						psFName, psLName, psEmail, the data on this new contact

Returned:		new total number of contacts on success, -1 otherwise
****************************************************************************/
int edAddContact(EntryData *pData, char *psFName, char *psLName, char *psEmail)
{
	ContactEntry entry;
	if( NULL == pData || NULL == psFName || NULL == psLName || NULL == psEmail )
	{
		return ED_ERROR;
	}

	entry.psEmail = strdup(psEmail);
	entry.psFName = strdup(psFName);
	entry.psLName = strdup(psLName);

	dsAddEntry(pData->pDataStore, &entry);
	free(entry.psFName);
	free(entry.psLName);
	free(entry.psEmail);


	return dsGetNumberOfContacts(pData->pDataStore);
}

/****************************************************************************
Function:		edDeleteContact

Description:	delete a contact at the given index.  Any associated dynamic
							memory is freed.

Parameters:	pData the list of contacts
						index the index of the contact to delete

Returned:		the index of the deleted contact on success, -1 otherwise
****************************************************************************/
int edDeleteContact(EntryData *pData, int index)
{
	int i;
	ContactEntry entry;
	int result=1;
	if( NULL == pData || index >= dsGetNumberOfContacts(pData->pDataStore))
	{
		return ED_ERROR;
	}

	dsFirst(pData->pDataStore);
	// write each contact
	for( i=0; i< index && result == 1; i++)
	{
		dsCurrent(pData->pDataStore, &entry);
		result = dsNext(pData->pDataStore);
	}

	dsDeleteEntry(pData->pDataStore);

	return index;
}

/****************************************************************************
Function:

Description:

Parameters:

Returned:
****************************************************************************/
int edSearchData(EntryData *pData, char *psPattern, Field field, int *pResults, int maxResults)
{
	return 1;
}
/****************************************************************************
Function:		edVisitEachContact

Description:	This function will visit each contact and call VisitFunction
							on each contact. Order is not guaranteed.  The function may
						 	edit the string data but NOT reallocate pointers
						 	and NOT delete the contact.

Parameters:	pData all of the contact data.
						VisitFunction a function pointer to the visitor function.

Returned:		number of contacts visited successfully
****************************************************************************/
int edVisitEachContact(EntryData *pData, VisitFunction func)
{
	int result = 1;
	ContactEntry entry;
	if (NULL == pData || NULL == func)
	{
		return ED_ERROR;
	}

	dsFirst(pData->pDataStore);
	// write each contact
	while(1 == result)
	{
		dsCurrent(pData->pDataStore, &entry);
		func(&(entry));

		result = dsNext(pData->pDataStore);
	}

	return dsGetNumberOfContacts(pData->pDataStore);
}


static void* printerVisitor(ContactEntry *pContact)
{
	if(NULL == pContact)
	{
		return NULL;
	}

	printf("%25s %25s: %25s\n",
			pContact->psFName, pContact->psLName, pContact->psEmail);

	return NULL;
}

int edPrintContactToStdout(EntryData *pData, int index)
{
	ContactEntry entry;
	dsGetEntry(pData->pDataStore, &entry, index);

	printerVisitor(&(entry));
	return index;
}

/****************************************************************************
Function:		edPrintEachContactToStdout

Description:	This function will print each contact to stdout.  Order is not
							guaranteed.

Parameters:	pData all of the contact data.

Returned:		number of contacts printed successfully
****************************************************************************/
int edPrintEachContactToStdout(EntryData *pData)
{
	if (NULL == pData )
	{
		return ED_ERROR;
	}

	edVisitEachContact(pData, printerVisitor);
	return dsGetNumberOfContacts(pData->pDataStore);
}


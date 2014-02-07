/****************************************************************************
File name:  EntryData.h

Author: 	chadd

Date: 		Feb 6, 2014

Class: 		CS 360, Fall 2014
Assignment: Example Open Source Development with Git

Purpose:
****************************************************************************/

#ifndef ENTRYDATA_H_
#define ENTRYDATA_H_

#include "ContactEntry.h"
#include "ContactDataStore.h"
#include <stdlib.h>

typedef struct EntryData
{
	ContactDataStore *pDataStore;
/*	ContactEntry *pArray;
	int numberOfUsedContacts;
	int numberOfContacts;*/
} EntryData;

typedef enum Field {FName, LName, Email} Field;
typedef void*(*VisitFunction)(ContactEntry *);

int edInitData(EntryData *pData);
int edDeleteData(EntryData *pData);

int edReadData(EntryData *pData, char *psFilename);
int edWriteData(EntryData *pData, char *psFilename);

int edSortData(EntryData *pData, Field sortType);

int edAddContact(EntryData *pData, char *psFName, char *psLName, char *psEmail);
int edDeleteContact(EntryData *pData, int index);

int edSearchData(EntryData *pData, char *psPattern, Field field, int *pResults, int maxResults);

int edVisitEachContact(EntryData *pData, VisitFunction );

int edPrintEachContactToStdout(EntryData *pData);

int edPrintContactToStdout(EntryData *pData, int index);

#endif /* ENTRYDATA_H_ */

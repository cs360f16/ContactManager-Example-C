###############################################################################
# File:		Makefile
# Author:	chadd williams
# Date:		2/6/2013
# Class:	CS 360 Fall 2014
# Assignment: Example Open Source Development with Git
# Purpose:	Build the system completely
###############################################################################

.PHONY: clean all

CFLAGS=-Wall -g 
INCLUDES=include/ContactEntry.h include/EntryData.h include/ContactDataStore.h
all: bin/cmanager

bin/cmanager: bin/main.o bin/EntryData.o bin/ContactDataStore.o
	gcc ${CFLAGS} bin/main.o bin/EntryData.o bin/ContactDataStore.o -o bin/cmanager

bin/main.o: src/main.c ${INCLUDES}
	gcc ${CFLAGS} src/main.c -c -o bin/main.o
	
bin/EntryData.o: src/EntryData.c ${INCLUDES}
	gcc ${CFLAGS} src/EntryData.c -c -o bin/EntryData.o
	
bin/ContactDataStore.o: src/ContactDataStore.c ${INCLUDES}
	gcc ${CFLAGS} src/ContactDataStore.c -c -o bin/ContactDataStore.o
	
clean:
	rm -rf bin/*.o bin/cmanager
	 
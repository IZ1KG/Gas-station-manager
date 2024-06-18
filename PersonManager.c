#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "PersonManager.h"
#include "General.h"
#include "fileHelper.h"

//Function that initializes person manager
void initPersonManager(PersonManager* pMang)
{
	pMang->personArr = NULL;
	pMang->countPerson = 0;
}

//Function to add new person to person manager
int addPerson(PersonManager* pMang)
{
	int id;
	Person* pPer = NULL;
	printPersonManager(pMang);
	do
	{
		if (pPer != NULL)
			printf("Person id already exists!\n");
		getPersonID(&id);
		pPer = getPersonByID(pMang->personArr, pMang->countPerson, id);
	} while (pPer != NULL);
	pPer = (Person*)malloc(sizeof(Person));
	if (!pPer)
	{
		ALLOCATION_ERROR
	}
	pPer->id = id;
	initPersonNoID(pPer);
	pMang->personArr = (Person**)realloc(pMang->personArr, sizeof(Person*) * (pMang->countPerson + 1));
	if (!pMang->personArr)
	{
		free(pPer);
		ALLOCATION_ERROR
	}
	pMang->personArr[pMang->countPerson++] = pPer;
	return id;
}

//Function to print person manager
void printPersonManager(const PersonManager* pMang)
{
	printf("There are %d people:\n", pMang->countPerson);
	generalArrayFunction(pMang->personArr, pMang->countPerson, sizeof(Person*), printPerson);
}

//Function to free person manager
void freePersonManager(PersonManager* pMang)
{
	generalArrayFunction(pMang->personArr, pMang->countPerson, sizeof(Person*), freePerson);
	free(pMang->personArr);
}

//Function to write person manager to binary file
int writePersonManager(const PersonManager* pMang, FILE* fp)
{
	if (fwrite(&(pMang->countPerson), sizeof(int), 1, fp) != 1)
		return 0;
	for (int i = 0; i < pMang->countPerson; i++)
	{
		if (!writePersonToFile(pMang->personArr[i], fp))
			return 0;
	}
	return 1;
}

//Function that reads person manager from binary file
int readPersonManagerFromFile(PersonManager* pManager, FILE* fp)
{
	if (!readIntFromFile(&pManager->countPerson, fp, "Error reading person count\n"))
		return 0;
	if (pManager->countPerson > 0)
	{
		pManager->personArr = (Person**)malloc(sizeof(Person*) * pManager->countPerson);
		if (!pManager->personArr)
		{
			ALLOCATION_ERROR
		}
	}
	else
		pManager->personArr = NULL;
	for (int i = 0; i < pManager->countPerson; i++)
	{
		pManager->personArr[i] = (Person*)malloc(sizeof(Person));
		if (!pManager->personArr[i])
		{
			free(pManager->personArr);
			ALLOCATION_ERROR
		}
		if (!readPersonFromFile(pManager->personArr[i], fp))
		{
			printf("Error reading person array\n");
			free(pManager->personArr);
			return 0;
		}
	}
	return 1;
}

//Function that reads person manager from text file
int loadPersonManagerText(PersonManager* pPerMan, FILE* fp)
{
	if (!pPerMan)
		return 0;
	fscanf(fp, "%d", &pPerMan->countPerson);
	//clean the buffer
	fgetc(fp);
	pPerMan->personArr = (Person**)malloc(sizeof(Person*) * pPerMan->countPerson);
	if (!pPerMan->personArr)
	{
		ALLOCATION_ERROR
	}
	Person* pPer;
	for (int i = 0; i < pPerMan->countPerson; i++)
	{
		pPer = (Person*)calloc(1, sizeof(Person));
		if (!pPer)
		{
			ALLOCATION_ERROR
		}
		if (!loadPersonText(pPer, fp))
		{
			printf("Error reading person\n");
			return 0;
		}
		pPerMan->personArr[i] = pPer;
	}
	return 1;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "General.h"
#include "fileHelper.h"
#include "Person.h"

//Function that initializes person without id
void initPersonNoID(Person* pPer)
{
	char temp[MAX_STR_LEN];
	printf("Enter person name\n");
	myGets(temp, MAX_STR_LEN, stdin);
	pPer->name = getDynStr(temp);
	printf("Enter person birth date:\n");
	getCorrectDate(&pPer->dateOfBirth);
}

//Function that initializes person
void initPerson(Person* pPer)
{
	initPersonNoID(pPer);
	getPersonID(&(pPer->id));
}

//Function to get person id from user
void getPersonID(int* ID)
{
	int res = 0;
	do
	{
		printf("Enter ID - valid number with %d digits:", INT_LEN);
		scanf("%d", ID);
		if (*ID < MIN_INT || *ID > MAX_INT)
			printf("The number inserted is out of range!\n");
		else
			res = 1;
	} while (!res);
}

//Function to print person
void printPerson(const void* pPer)
{
	Person* tPer = *(Person**)pPer;
	printf("Birth ");
	printDate(&tPer->dateOfBirth);
	printf("Name: %-15s, ID: %-15d\n", tPer->name, tPer->id);
}

//Function to free person
void freePerson(void* pPer)
{
	Person* tPer = *(Person**)pPer;
	free(tPer->name);
}

//Function that compares person by name
int comparePersonByName(const void* pPer1, const void* pPer2)
{
	Person* temp1 = (Person*)pPer1;
	Person* temp2 = (Person*)pPer2;
	return (strcmp(temp1->name, temp2->name));
}

//Function that compares person by id number
int comparePersonByID(const void* e1, const void* e2)
{
	Person* t1 = (Person*)e1;
	Person* t2 = (Person*)e2;
	return t1->id - t2->id;
}

//Function to read person from binary file
int readPersonFromFile(Person* pPer, FILE* fp)
{
	pPer->name = readStringFromFile(fp, "Error read person name\n");
	if (!pPer->name)
		return 0;
	if (fread(&pPer->id, sizeof(int), 1, fp) != 1
		|| !readDateFromFile(fp, &pPer->dateOfBirth))
	{
		free(pPer->name);
		return 0;
	}
	return 1;
}

//Function to write person to binary file
int writePersonToFile(const Person* pPers, FILE* fp)
{
	if (!writeStringToFile(pPers->name, fp, "Error write person name\n")
		|| fwrite(&pPers->id, sizeof(int), 1, fp) != 1
		|| !saveDateToFile(fp, &pPers->dateOfBirth))
		return 0;
	return 1;
}

//Function to write person to text file
int savePersonText(Person* pPer, FILE* fp)
{
	if (!pPer)
		return 0;
	saveDateText(&pPer->dateOfBirth, fp);
	fprintf(fp, "%d\n", pPer->id);
	fprintf(fp, "%s\n", pPer->name);
	return 1;
}

//Function to read person from text file
int loadPersonText(Person* pPer, FILE* fp)
{
	if (!pPer)
		return 0;
	loadDateText(&pPer->dateOfBirth, fp);
	fscanf(fp, "%d", &pPer->id);
	//clean the buffer
	fgetc(fp);
	char temp[MAX_STR_LEN];
	myGets(temp, MAX_STR_LEN, fp);
	pPer->name = getDynStr(temp);
	return 1;
}

//Function to find person by id
Person* getPersonByID(Person** personArr, int count, int id)
{
	for (int i = 0; i < count; i++)
	{
		if (personArr[i]->id - id == 0)
			return personArr[i];
	}
	return NULL;
}
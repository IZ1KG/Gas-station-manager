#ifndef __Person__
#define __Person__

#include "Date.h"
#include "General.h"

typedef struct
{
	char* name;
	int id;
	Date dateOfBirth;
}Person;

void initPersonNoID(Person* pPer);
void initPerson(Person* pPer);
void getPersonID(int* ID);
void printPerson(const void* pPer);
void freePerson(void* pPer);
int comparePersonByName(const void*, const void*);
int comparePersonByID(const void* e1, const void* e2);
int readPersonFromFile(Person* pPer, FILE* fp);
int writePersonToFile(const Person* pPers, FILE* fp);
int savePersonText(Person* pPer, FILE* fp);
int loadPersonText(Person* pPer, FILE* fp);
Person* getPersonByID(Person** personArr, int count, int id);

#endif
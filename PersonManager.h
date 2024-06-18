#ifndef __PERSON_MANAGER__
#define __PERSON_MANAGER__

#include "Person.h"

typedef struct
{
	Person** personArr;
	int countPerson;
}PersonManager;

void initPersonManager(PersonManager* pMang);
int addPerson(PersonManager* pMang);
void printPersonManager(const PersonManager* pMang);
void freePersonManager(PersonManager* pMang);
int writePersonManager(const PersonManager* pMang, FILE* fp);
int readPersonManagerFromFile(PersonManager* pManager, FILE* fp);
int loadPersonManagerText(PersonManager* pPerMan, FILE* fp);

#endif
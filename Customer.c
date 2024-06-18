#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "Customer.h"
#include "General.h"
#include "fileHelper.h"

//Function tha initializes customer
void initCustomer(Customer* pCust)
{
	initPerson(pCust->person);
	initCustomerNoPerson(pCust);
}

//Function to print customer
void printCustomer(const void* pCust)
{
	Customer* tCust = (Customer*)pCust;
	printf("Custumer details:\n");
	printPerson(&tCust->person);
	printCar(&(tCust->car));
	printf("Expenses: %d\n", tCust->expenses);
}

//Function to make a puchase with a customer
void customerPurchase(Customer* pCust)
{
	int random = rand() % 100 + 1;
	pCust->expenses += random;
}

//Function that initializes customer without person data
void initCustomerNoPerson(Customer* pCust)
{
	printf("Enter customer vehicle details\n");
	initCar(&pCust->car, NULL, 0);
	pCust->expenses = 0;
}

//
int compareCustomerByID(const void* e1, const void* e2)
{
	Customer t1 = *(Customer*)e1;
	Customer t2 = *(Customer*)e2;
	return t1.person->id - t2.person->id;
}

//Function to read customer from binary file
int readCustomerFromFile(Customer* pCust, Person** personArr, int count, FILE* fp)
{
	int id;
	if (fread(&id, sizeof(int), 1, fp) != 1)
		return 0;
	pCust->person = getPersonByID(personArr, count, id);
	if (!pCust->person)
		return 0;
	if (fread(&pCust->expenses, sizeof(int), 1, fp) != 1
		|| fread(&pCust->car, sizeof(Car), 1, fp) != 1)
		return 0;
	return 1;
}

//Function to read customer to binary file
int writeCustomerToFile(const Customer* pCust, FILE* fp)
{
	if (fwrite(&pCust->person->id, sizeof(int), 1, fp) != 1
		|| fwrite(&pCust->expenses, sizeof(int), 1, fp) != 1
		|| fwrite(&pCust->car, sizeof(Car), 1, fp) != 1)
		return 0;
	return 1;
}

//Function that writes customer array to binary file
int writeCustomersToFile(const Customer* customerArr, const  int count, FILE* fp)
{
	if (fwrite(&count, sizeof(int), 1, fp) != 1)
		return 0;
	for (int i = 0; i < count; i++)
	{
		if (!writeCustomerToFile(&customerArr[i], fp))
			return 0;
	}
	return 1;
}

//Function to write customer to text file
int saveCustomerText(Customer* pCust, FILE* fp)
{
	if (!pCust)
		return 0;
	saveCarText(&pCust->car, fp);
	fprintf(fp, "%d\n", pCust->expenses);
	fprintf(fp, "%d\n", pCust->person->id);
	return 1;
}

//Function to read customer from text file
int loadCustomerText(Customer* pCust, Person** personArr, int count, FILE* fp)
{
	if (!pCust)
		return 0;
	if (!loadCarText(&pCust->car, fp))
		return 0;
	fscanf(fp, "%d", &pCust->expenses);
	//clean the buffer
	fgetc(fp);
	int temp;
	fscanf(fp, "%d", &temp);
	//clean the buffer
	fgetc(fp);
	pCust->person = getPersonByID(personArr, count, temp);
	if (!pCust->person)
		return 0;
	return 1;
}
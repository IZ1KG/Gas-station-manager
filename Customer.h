#ifndef __CUSTOMER__
#define __CUSTOMER__

#include "Person.h"
#include "Car.h"

typedef struct
{
	int expenses;
	Car car;
	Person* person;
}Customer;

void initCustomerNoPerson(Customer* pCust);
void initCustomer(Customer* pCust);
void printCustomer(const void* pCust);
void customerPurchase(Customer* pCust);
int compareCustomerByID(const void* e1, const void* e2);
int readCustomerFromFile(Customer* pCust, Person** personArr, int count, FILE* fp);
int writeCustomerToFile(const Customer* pCust, FILE* fp);
int writeCustomersToFile(const Customer* customerArr, const  int count, FILE* fp);
int saveCustomerText(Customer* pCust, FILE* fp);
int loadCustomerText(Customer* pCust, Person** personArr, int count, FILE* fp);

#endif
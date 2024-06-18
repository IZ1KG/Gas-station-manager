#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Station.h"
#include "General.h"
#include "fileHelper.h"

//Function to initialize station
int initStation(Station** stationArr, int count, Station* pStation)
{
	getStationNameUnique(stationArr, count, &pStation->name);
	pStation->city = getStrExactName("Enter Station city:");
	pStation->countOfCustomers = 0;
	pStation->countOfEmployees = 0;
	pStation->countOfPumps = 0;
	pStation->customerArr = NULL;
	pStation->employeeArr = NULL;
	pStation->pumpsArr = NULL;
	pStation->employeeSortOpt = 0;
	return 1;
}

//Function that returns is the name is the same of the station 
int	isStationName(const Station* pStation, const char* name)
{
	if (!pStation)
		return 0;
	if (strcmp(pStation->name, name) == 0)
		return 1;
	return 0;
}

//Function that gets the station's profits 
int getStationProfits(Station* pSta)
{
	int sum = 0;
	for (int i = 0; i < pSta->countOfCustomers; i++)
	{
		sum += pSta->customerArr[i].expenses;
	}
	for (int i = 0; i < pSta->countOfEmployees; i++)
	{
		sum -= pSta->employeeArr[i].salary;
	}
	return sum;
}

//Function that prints station
void printStation(const void* pSta)
{
	Station* tSta = *(Station**)pSta;
	printf("Station name:%-20s\n", tSta->name);
	printf("City: %-20s\n", tSta->city);
	printf("Number of pumps: %-20d\n", tSta->countOfPumps);
	generalArrayFunction(tSta->pumpsArr, tSta->countOfPumps, sizeof(Pump), printPump);
	printf("Number of employees: %-20d\n", tSta->countOfEmployees);
	generalArrayFunction(tSta->employeeArr, tSta->countOfEmployees, sizeof(Employee), printEmployee);
	printf("Number of customers: %-20d\n", tSta->countOfCustomers);
	generalArrayFunction(tSta->customerArr, tSta->countOfCustomers, sizeof(Customer), printCustomer);
}

//Function that adds a pump to station
int addPumpToStation(Station* pSta)
{
	generalArrayFunction(pSta->pumpsArr, pSta->countOfPumps, sizeof(Pump), printPump);
	Pump pump;
	initPump(pSta->pumpsArr, pSta->countOfPumps, &pump);
	pSta->pumpsArr = (Pump*)realloc(pSta->pumpsArr,
		sizeof(Pump) * (size_t)(pSta->countOfPumps + 1));
	if (!pSta->pumpsArr)
	{
		ALLOCATION_ERROR
	}
	pSta->pumpsArr[pSta->countOfPumps++] = pump;
	return 1;
}

//Function that gets a unique name for station
void getStationNameUnique(Station** stationArr, int stationCount, char** name)
{
	Station* pSta = NULL;
	do {
		getStationName(name);
		pSta = getStationByName(stationArr, stationCount, *name);
		if (pSta != NULL)
			printf("Please choose a name that is not in use.\n");
	} while (pSta != NULL);
}

//Function to get station name from user
void getStationName(char** name)
{
	char temp[MAX_STR_LEN];
	printf("Enter station name\n");
	myGets(temp, MAX_STR_LEN, stdin);
	*name = getDynStr(temp);
}

//Function to free station
void freeStation(void* pStation)
{
	Station* tSta = *(Station**)pStation;
	free(tSta->city);
	free(tSta->name);
	free(tSta->employeeArr);
	free(tSta->customerArr);
	free(tSta->pumpsArr);
}

//Function that sorts employees based on user input
void sortEmployees(Station* pSta)
{
	pSta->employeeSortOpt = showSortMenu();
	int(*compare)(const void* air1, const void* air2) = NULL;

	switch (pSta->employeeSortOpt)
	{
	case eID:
		compare = compareEmployeeByID;
		break;
	case eAge:
		compare = compareEmployeeByAge;
		break;
	case eSalary:
		compare = compareEmployeeBySalary;
		break;
	}

	if (compare != NULL)
		qsort(pSta->employeeArr, pSta->countOfEmployees, sizeof(Employee), compare);
}

//Function that makes sales for station from every customer
void makeSaleInStation(Station* pSta)
{
	for (int i = 0; i < pSta->countOfCustomers; i++)
		customerPurchase(&pSta->customerArr[i]);
}

//Function to add customer to station
int addCustomerToStation(Station* pStation, Person* pPer)
{
	if (!pPer)
		return 0;
	Customer cust;
	initCustomerNoPerson(&cust);
	customerPurchase(&cust);
	cust.person = pPer;
	int index = findInArray(pStation->customerArr, pStation->countOfCustomers,
		sizeof(Customer), &cust,compareCustomerByID);
	if (index == -1)
	{
		pStation->customerArr = (Customer*)realloc(pStation->customerArr,
			(int)sizeof(Customer) * (size_t)(pStation->countOfCustomers + 1));
		if (!pStation->customerArr)
		{
			ALLOCATION_ERROR
		}
		pStation->customerArr[pStation->countOfCustomers++] = cust;
		printf("The customer have added succesfully.\n");
		return 1;
	}
	else
	{
		printf("The customer is already in the system.\n");
		return 0;
	}
}

//Function that adds employees to station
int addEmployeeToStation(Station* pStation, Person* pPer)
{
	if (!pPer)
		return 0;
	Employee emp = { 0 };
	emp.person = pPer;
	initEmployeeNoPerson(&emp);
	int index = findInArray(pStation->employeeArr, pStation->countOfEmployees,sizeof(Employee), &emp, compareEmployeeByID);
	if (index == -1)
	{
		pStation->employeeArr = (Employee*)realloc(pStation->employeeArr,
			sizeof(Employee) * (size_t)(pStation->countOfEmployees + 1));
		if (!pStation->employeeArr)
		{
			ALLOCATION_ERROR
		}
		pStation->employeeArr[pStation->countOfEmployees++] = emp;
		printf("The employee have added succesfully.\n");
		return 1;
	}
	printf("The employee is already in the system.\n");
	return 0;
}

//Function that writes station to binary file
int writeStationToFile(const Station* pSta, FILE* fp)
{
	if (!writeStringToFile(pSta->name, fp, "Error write station name\n")
		|| !writeStringToFile(pSta->city, fp, "Error write station city\n")
		|| !writePumpsToFile(pSta->pumpsArr, pSta->countOfPumps, fp)
		|| !writeEmployeesToFile(pSta->employeeArr, pSta->countOfEmployees, fp)
		|| !writeCustomersToFile(pSta->customerArr, pSta->countOfCustomers, fp))
		return 0;
	return 1;
}

//Function that reads station from file
int readStationFromFile(Station* pSta, Person** personArr, int count, FILE* fp)
{
	pSta->name = readStringFromFile(fp, "Error read station name\n");
	if (!pSta->name)
		return 0;
	pSta->city = readStringFromFile(fp, "Error read station city\n");
	if (!pSta->city)
	{
		free(pSta->name);
		return 0;
	}
	if (!readPumpsFromFile(pSta, fp)
		|| !readEmployeesFromFile(pSta, personArr, count, fp)
		|| !readCustomersFromFile(pSta, personArr, count, fp))
	{
		free(pSta->city);
		free(pSta->name);
		return 0;
	}
	return 1;
}

//Function that reads customer from binary file
int readCustomersFromFile(Station* pSta, Person** personArr, int count, FILE* fp)
{
	if (fread(&(pSta->countOfCustomers), sizeof(int), 1, fp) != 1)
		return 0;
	pSta->customerArr = (Customer*)malloc(sizeof(Customer) * pSta->countOfCustomers);
	if (!pSta->customerArr)
	{
		ALLOCATION_ERROR
	}
	for (int i = 0; i < pSta->countOfCustomers; i++)
	{
		if (!readCustomerFromFile(&(pSta->customerArr[i]), personArr, count, fp))
		{
			free(pSta->customerArr);
			return 0;
		}
	}
	return 1;
}

//Function that reads pump array from binary file
int readPumpsFromFile(Station* pSta, FILE* fp)
{
	if (fread(&(pSta->countOfPumps), sizeof(int), 1, fp) != 1)
		return 0;
	pSta->pumpsArr = (Pump*)malloc(sizeof(Pump) * pSta->countOfPumps);
	if (!pSta->pumpsArr)
	{
		ALLOCATION_ERROR
	}
	for (int i = 0; i < pSta->countOfPumps; i++)
	{
		if (!readPumpFromFile(&pSta->pumpsArr[i], fp))
		{
			free(pSta->pumpsArr);
			return 0;
		}
	}
	return 1;
}

//Function that reads employees from binary file
int readEmployeesFromFile(Station* pSta,Person** personArr, int count, FILE* fp)
{
	if (fread(&(pSta->countOfEmployees), sizeof(int), 1, fp) != 1)
		return 0;
	pSta->employeeArr = (Employee*)malloc(sizeof(Employee) * pSta->countOfEmployees);
	if (!pSta->employeeArr)
	{
		ALLOCATION_ERROR
	}
	for (int i = 0; i < pSta->countOfEmployees; i++)
	{
		if (!readEmployeeFromFile(&pSta->employeeArr[i], personArr, count, fp))
		{
			free(pSta->employeeArr);
			return 0;
		}
	}
	return 1;
}

//Function to choose sort option from user
eSortOption showSortMenu()
{
	int opt;
	printf("Base on what field do you want to sort?\n");
	do {
		for (int i = 1; i < eNofSortOpt; i++)
			printf("Enter %d for %s\n", i, sortOptStr[i]);
		scanf("%d", &opt);
	} while (opt < 0 || opt >= eNofSortOpt);

	return (eSortOption)opt;
}

//Function that finds employee based on user sort choice
void findEmployee(const Station* pSta)
{
	int(*compare)(const void* air1, const void* air2) = NULL;
	Employee e = { 0 };
	Person p = { 0 };
	e.person = &p;
	Employee* pEmp = &e;

	switch (pSta->employeeSortOpt)
	{
	case eID:
		printf("%s\t", "ID:");
		getPersonID(&e.person->id);
		compare = compareEmployeeByID;
		break;

	case eSalary:
		printf("%s\t", "Salary:");
		getSalary(pEmp);
		compare = compareEmployeeBySalary;
		break;

	case eAge:
		getCorrectDate(&e.person->dateOfBirth);
		compare = compareEmployeeByAge;
		break;
	}

	if (compare != NULL)
	{
		Employee* pE = bsearch(&pEmp, pSta->employeeArr, pSta->countOfEmployees, sizeof(Employee), compare);
		if (pE == NULL)
			printf("Employee was not found\n");
		else {
			printf("Employee found, ");
			printEmployee(pE);
		}
	}
	else {
		printf("The search cannot be performed, array not sorted\n");
	}
}

//Function to save station to text file
int saveStationText(const Station* pSta, FILE* fp)
{
	if (!pSta)
		return 0;
	fprintf(fp, "%s\n", pSta->city);
	fprintf(fp, "%d\n", pSta->countOfCustomers);
	for (int i = 0; i < pSta->countOfCustomers; i++)
	{
		if (!saveCustomerText(&pSta->customerArr[i], fp))
		{
			printf("Error write customer\n");
			return 0;
		}
	}
	fprintf(fp, "%d\n", pSta->countOfEmployees);
	for (int i = 0; i < pSta->countOfEmployees; i++)
	{
		if (!saveEmployeeText(&pSta->employeeArr[i], fp))
		{
			printf("Error write employee\n");
			return 0;
		}
	}
	fprintf(fp, "%d\n", pSta->countOfPumps);
	for (int i = 0; i < pSta->countOfPumps; i++)
	{
		if (!savePumpText(&pSta->pumpsArr[i], fp))
		{
			printf("Error write pump\n");
			return 0;
		}
	}
	fprintf(fp, "%s\n", pSta->name);
	return 1;
}

//Function that gets a station according to the name, return null if station not found
Station* getStationByName(Station** stationArr, int count, char* name)
{
	for (int i = 0; i < count; i++)
	{
		if (strcmp(stationArr[i]->name, name) == 0)
			return stationArr[i];
	}
	return NULL;
}


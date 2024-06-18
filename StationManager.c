#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "StationManager.h"
#include "General.h"
#include "fileHelper.h"

//Function to initialize station manager
void initStationManager(StationManager* pStaMan, PersonManager* pManager)
{
	initStationManagerNoPerson(pStaMan);
	pStaMan->pManager = pManager;
}

//Function to initialize station manager without person manager
void initStationManagerNoPerson(StationManager* pStaMan)
{
	pStaMan->stationArr = NULL;
	pStaMan->countOfStations = 0;
}

//Function to choose station and sort it's employees
void getStationAndSort(StationManager* pStaMan)
{
	Station* pSta = chooseStation(pStaMan, "Error unable to perform sort\n",
		"Please choose by name the station that you want to sort the employee array at:\n",
		"The name is not in the system please try again, choose again\n");
	if (pSta)
	{
		sortEmployees(pSta);
		printStation(&pSta);
	}
}

//Function to choose a station and find employee in the station
void binarySearchEmployee(StationManager* pStaMan)
{
	Station* pSta = chooseStation(pStaMan, "Error unable to perform search\n",
		"Please choose by name the station you want to the search in:\n",
		"There is no station with this name in the system, choose again\n");
	if (pSta)
		findEmployee(pSta);
}

//Function to get a station from user
Station* chooseStation(StationManager* pStaMan, char* errorMsg, char* msg, char* errorMsg2)
{
	if (!pStaMan || pStaMan->countOfStations == 0)
	{
		printf("%s", errorMsg);
		return NULL;
	}
	int index = -1;
	char* temp;
	generalArrayFunction(pStaMan->stationArr, pStaMan->countOfStations, sizeof(Station*), printStation);
	do
	{
		printf("%s", msg);
		getStationName(&temp);
		index = findNameIndex(pStaMan->stationArr, pStaMan->countOfStations, temp);
		if (index == -1)
			printf("%s", errorMsg2);
		else
			return pStaMan->stationArr[index];
	} while (index == -1);
}

//Function to choose a station and add pump to it
void addPump(StationManager* pStaMan)
{
	Station* pSta = chooseStation(pStaMan, "Unable to add pump!\n",
		"Please choose by name the station you want add a pump at:\n",
		"There is no station with this name in the system, choose again\n");
	if (pSta)
		addPumpToStation(pSta);
}

//Function that returns the most profitable station
void showBestStation(StationManager* pStaMan)
{
	if (!pStaMan || pStaMan->countOfStations == 0)
	{
		printf("No stations in the system!\n");
		return;
	}
	int index = 0, max = getStationProfits(pStaMan->stationArr[0]);
	for (int i = 1; i < pStaMan->countOfStations; i++)
	{
		int res = getStationProfits(pStaMan->stationArr[i]);
		if (max < res)
		{
			max = res;
			index = i;
		}
	}
	printf("Station with the most profits in the system, with %d in profits:\n", max);
	printStation(pStaMan->stationArr[index]);
}

//Function to choose a station and make a purchase with each of it's clients
void makeSales(StationManager* pStaMan)
{
	Station* pSta = chooseStation(pStaMan, "No stations in the system!\n",
		"Enter name of a station you wish to add sales to from the list: \n",
		"There is no station with this name in the system, choose again\n");
	if (pSta)
	{
		if (pSta->countOfCustomers == 0)
		{
			printf("No customers in the station!\n");
			return;
		}
		makeSaleInStation(pSta);
	}
}

//Function to choose a station and add a new employee to it
int addEmployee(StationManager* pStaMan)
{
	Station* pSta = chooseStation(pStaMan, "Unable to add employee\n",
		"Enter name of a station you wish to add employee to from the list: \n",
		"There is no station with this name in the system, choose again\n");
	if (pSta)
	{
		if (pStaMan->pManager->countPerson == 0)
			return addEmployeeNew(pStaMan->pManager, pSta);
		char ch = getCharExistNew("Would you like to assign an employee from existing person or add new?\n");
		if (ch == 'e')
			return addEmployeeExisting(pStaMan->pManager, pSta);
		return addEmployeeNew(pStaMan->pManager, pSta);
	}
	return 0;
}

//Function that adds an employee to a station from a person already in the system
int addEmployeeExisting(PersonManager* pPerMan, Station* pStation)
{
	Person* pPer;
	pPer = (Person*)malloc(sizeof(Person));
	if (!pPer)
		return 0;
	printPersonManager(pPerMan);
	int temp;
	do
	{
		printf("Enter valid person id to choose person: \n");
		scanf("%d", &temp);
		pPer = getPersonByID(pPerMan->personArr, pPerMan->countPerson, temp);
	} while (!pPer);
	return addEmployeeToStation(pStation, pPer);
}

//Function to add an employee to station, adding a new person to the system
int addEmployeeNew(PersonManager* pPerMan, Station* pStation)
{
	Person* pPer;
	int temp;
	do
	{
		temp = addPerson(pPerMan);
	} while (!temp);
	pPer = getPersonByID(pPerMan->personArr, pPerMan->countPerson, temp);
	return addEmployeeToStation(pStation, pPer);
}

//Function to choose a station and add a new customer to it
int addCustomer(StationManager* pStaMan)
{
	Station* pSta = chooseStation(pStaMan, "Unable to add customer\n",
		"Enter name of a station you wish to add customer to from the list:\n",
		"There is no station with this name in the system, choose again\n");
	if (pSta)
	{
		if (pStaMan->pManager->countPerson == 0)
			return addCustomerNew(pStaMan->pManager, pSta);
		char ch = getCharExistNew("Would you like to assign a customer from existing person or add new?\n");
		if (ch == 'e' || ch == 'E')
			return addCustomerExisting(pStaMan->pManager, pSta);
		return addCustomerNew(pStaMan->pManager, pSta);
	}
	return 0;
}

int findNameIndex(const Station** stationArr, int count, char* name)
{
	for (int i = 0; i < count; i++)
	{
		if (strcmp(stationArr[i]->name, name) == 0)
			return i;
	}
	return -1;
}

//Function that adds a customer to a station from a person already in the system
int addCustomerExisting(PersonManager* pPerMan, Station* pStation)
{
	Person* pPer;
	pPer = (Person*)malloc(sizeof(Person));
	if (!pPer)
		return 0;
	printPersonManager(pPerMan);
	int temp;
	do
	{
		printf("Enter valid person id to choose person: \n");
		scanf("%d", &temp);
		pPer = getPersonByID(pPerMan->personArr, pPerMan->countPerson, temp);
	} while (!pPer);
	return addCustomerToStation(pStation, pPer);
}

//Function to add an customer to station, adding a new person to the system
int addCustomerNew(PersonManager* pPerMan, Station* pStation)
{
	Person* pPer;
	int temp;
	do
	{
		temp = addPerson(pPerMan);
	} while (!temp);
	pPer = getPersonByID(pPerMan->personArr, pPerMan->countPerson, temp);
	return addCustomerToStation(pStation, pPer);
}

//Function that return if two stations are the same, based on the name
int compareStation(const void* e1, const void* e2)
{
	Station* t1 = (Station*)e1;
	Station* t2 = (Station*)e2;
	return strcmp(t1->name, t2->name);
}

//Function to add a station to station manager
int addStation(StationManager* pStaMan)
{
	Station* temp;
	temp = (Station*)malloc(sizeof(Station));
	if (!temp)
	{
		ALLOCATION_ERROR
	}
	initStation(pStaMan->stationArr, pStaMan->countOfStations, temp);
	pStaMan->stationArr = (Station**)realloc(pStaMan->stationArr,
		sizeof(Station*) * (size_t)(pStaMan->countOfStations + 1));
	if (!pStaMan->stationArr)
	{
		free(temp);
		ALLOCATION_ERROR
	}
	pStaMan->stationArr[pStaMan->countOfStations++] = temp;
	return 1;
}

//Function to print station manager
void printStationManager(const StationManager* pStaMan)
{
	printf("There are %d station in the system:\n\n", pStaMan->countOfStations);
	generalArrayFunction(pStaMan->stationArr, pStaMan->countOfStations, sizeof(Station*), printStation);
}

//Function to free station manager
void freeStationManager(StationManager* pStaMan)
{
	freePersonManager(pStaMan->pManager);
	generalArrayFunction(pStaMan->stationArr, pStaMan->countOfStations, sizeof(Station*), freeStation);
	free(pStaMan->stationArr);
}

//Function to read station manager from binary file
int readStationManagerFromFile(StationManager* pStaMan, FILE* fp)
{
	if (!readPersonManagerFromFile(pStaMan->pManager, fp))
	{
		printf("Error reading person manager\n");
		return 0;
	}
	if (!readIntFromFile(&pStaMan->countOfStations, fp, "Error reading station count\n"))
		return 0;
	if (pStaMan->countOfStations > 0)
	{
		pStaMan->stationArr = (Station**)malloc(sizeof(Station*) * pStaMan->countOfStations);
		if (!pStaMan->stationArr)
		{
			ALLOCATION_ERROR
		}
	}
	else
		pStaMan->stationArr = NULL;
	for (int i = 0; i < pStaMan->countOfStations; i++)
	{
		pStaMan->stationArr[i] = (Station*)malloc(sizeof(Station));
		if (!pStaMan->stationArr[i])
		{
			ALLOCATION_ERROR
		}
		if (!readStationFromFile(pStaMan->stationArr[i], pStaMan->pManager->personArr, pStaMan->pManager->countPerson, fp))
		{
			free(pStaMan->stationArr);
			printf("Error reading station array\n");
			return 0;
		}
	}
	return 1;
}

//Function to write station manager to binary file
int writeStationManagerToFile(const StationManager* stationManager, FILE* fp)
{
	if (!writePersonManager(stationManager->pManager, fp))
		return 0;
	if (fwrite(&(stationManager->countOfStations), sizeof(int), 1, fp) != 1)
		return 0;
	for (int i = 0; i < stationManager->countOfStations; i++)
	{
		if (!writeStationToFile(stationManager->stationArr[i], fp))
			return 0;
	}
	return 1;
}

//Function that writes station manager to text file
int saveStationManagerText(StationManager* pStaMan, FILE* fp)
{
	fprintf(fp, "%d\n", pStaMan->pManager->countPerson);
	for (int i = 0; i < pStaMan->pManager->countPerson; i++)
	{
		if (!savePersonText(pStaMan->pManager->personArr[i], fp))
		{
			printf("Error write person\n");
			return 0;
		}
	}
	fprintf(fp, "%d\n", pStaMan->countOfStations);
	for (int i = 0; i < pStaMan->countOfStations; i++)
	{
		if (!saveStationText(pStaMan->stationArr[i], fp))
		{
			printf("Error write station");
			return 0;
		}
	}
	return 1;
}

//Function that reads station manager from text file
int loadStationManagerText(StationManager* pStaMan, FILE* fp)
{
	if (!pStaMan)
		return 0;
	pStaMan->pManager = (PersonManager*)malloc(sizeof(PersonManager));
	if (!pStaMan->pManager)
	{
		ALLOCATION_ERROR
	}
	loadPersonManagerText(pStaMan->pManager, fp);
	fscanf(fp, "%d", &pStaMan->countOfStations);
	//clean the buffer
	fgetc(fp);
	pStaMan->stationArr = (Station**)malloc(sizeof(Station*) * pStaMan->countOfStations);
	if (!pStaMan->stationArr)
	{
		ALLOCATION_ERROR
	}
	for (int i = 0; i < pStaMan->countOfStations; i++)
	{
		pStaMan->stationArr[i] = (Station*)malloc(sizeof(Station));
		if (!pStaMan->stationArr[i])
		{
			ALLOCATION_ERROR
		}
		if (!loadStationText(pStaMan->stationArr[i], pStaMan->pManager->personArr, pStaMan->pManager->countPerson, fp))
		{
			printf("Error load station\n");
			return 0;
		}
	}
	return 1;
}

//Function to read station from text file
int loadStationText(Station* pSta, Person** pPersonArr, int count, FILE* fp)
{
	if (!pSta)
		return 0;
	char temp[MAX_STR_LEN];
	myGets(temp, MAX_STR_LEN, fp);
	pSta->city = getDynStr(temp);
	fscanf(fp, "%d", &pSta->countOfCustomers);
	//clean the buffer
	fgetc(fp);
	pSta->customerArr = (Customer*)malloc(pSta->countOfCustomers * sizeof(Customer));
	if (!pSta->customerArr)
	{
		ALLOCATION_ERROR
	}
	for (int i = 0; i < pSta->countOfCustomers; i++)
	{
		if (!loadCustomerText(&pSta->customerArr[i], pPersonArr, count, fp))
		{
			printf("Error read customer\n");
			return 0;
		}
	}
	fscanf(fp, "%d", &pSta->countOfEmployees);
	//clean the buffer
	fgetc(fp);
	pSta->employeeArr = (Employee*)malloc(pSta->countOfEmployees * sizeof(Employee));
	if (!pSta->employeeArr)
	{
		ALLOCATION_ERROR
	}
	for (int i = 0; i < pSta->countOfCustomers; i++)
	{
		if (!loadEmployeeText(&pSta->employeeArr[i], pPersonArr, count, fp))
		{
			printf("Error read employee\n");
			return 0;
		}
	}
	fscanf(fp, "%d", &pSta->countOfPumps);
	//clean the buffer
	fgetc(fp);
	pSta->pumpsArr = (Pump*)calloc(pSta->countOfPumps, sizeof(Pump));
	if (!pSta->pumpsArr)
	{
		ALLOCATION_ERROR
	}
	for (int i = 0; i < pSta->countOfCustomers; i++)
	{
		if (!loadPumpText(&pSta->pumpsArr[i], fp))
		{
			printf("Error read pump\n");
			return 0;
		}
	}
	myGets(temp, MAX_STR_LEN, fp);
	pSta->name = getDynStr(temp);
	return 1;
}
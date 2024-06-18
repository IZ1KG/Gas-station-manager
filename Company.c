#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Company.h"
#include "General.h"
#include "fileHelper.h"

//Functiont that initializes company
int	initCompany(Company* pCompany)
{	
	pCompany->name = getStrExactName("Please enter the company name:");
	pCompany->stationManager = (StationManager*)malloc(sizeof(StationManager));
	if (!pCompany->stationManager)
	{
		ALLOCATION_ERROR
	}
	pCompany->stationManager->pManager = (PersonManager*)malloc(sizeof(PersonManager));
	if (!pCompany->stationManager->pManager)
	{
		ALLOCATION_ERROR
	}
	initPersonManager(pCompany->stationManager->pManager);
	initStationManager(pCompany->stationManager, pCompany->stationManager->pManager);
	pCompany->truckArr = NULL;
	pCompany->countOfTrucks = 0;
	pCompany->refineryArr = NULL;
	pCompany->countOfRefinarys = 0;
	L_init(&pCompany->deliverysList);
	return 1;
}

//Function to add car to company
int addCarToCompany(Company* pComp)
{
	Car tCar;
	printf("Enter vehicle details:\n");
	initCar(&tCar,pComp->truckArr,pComp->countOfTrucks);
	pComp->truckArr = (Car*)realloc(pComp->truckArr,
		sizeof(Car) * (size_t)(pComp->countOfTrucks + 1));
	if (!pComp->truckArr)
	{
		ALLOCATION_ERROR
	}
	pComp->truckArr[pComp->countOfTrucks++] = tCar;
	return 1;
}

//Function to insert new delivery at the end of the list
void insertDeliveryToList(Delivery* pDeli, LIST* pList)
{
	NODE* pN = &pList->head;
	while (pN->next != NULL && compareDate(&((Delivery*)(pN->key))->date, &pDeli->date) > 0)
	{
		pN = pN->next;
	}
	L_insert(pN, pDeli);
}

//Function to add delivery to list by date
void addDeliveryToListByDate(Company* pComp)
{
	Delivery* tDel = (Delivery*)malloc(sizeof(Delivery));
	if (!tDel)
		return;
	Car* tCar = getCarFromArr(pComp->truckArr,pComp->countOfTrucks);
	if (!tCar)
		return;
	if (!initDelivery(tDel, tCar, pComp->stationManager->stationArr, pComp->stationManager->countOfStations
		, pComp->refineryArr, pComp->countOfRefinarys))
		return;
	NODE* pN = &pComp->deliverysList.head;
	while (pN->next != NULL && compareDate(&((Delivery*)(pN->key))->date,&tDel->date))
	{
		pN = pN->next;
	}
	L_insert(pN, tDel);
}

int addRefinery(Company* pComp)
{
	Refinery temp;
	pComp->refineryArr = (Refinery*)realloc(pComp->refineryArr,
		sizeof(Refinery) * (size_t)(pComp->countOfRefinarys + 1));
	if (!pComp->refineryArr)
	{
		ALLOCATION_ERROR
	}
	initRefinery(&temp, pComp->refineryArr, pComp->countOfRefinarys);
	pComp->refineryArr[pComp->countOfRefinarys++] = temp;
	return 1;
}

//Function to print company
void printCompany(Company* pComp)
{
	printf("Company details:\n\n");
	printf("Name: %s\n", pComp->name);
	printStationManager(pComp->stationManager);
	printf("\nThere are %d refineries in the company:\n", pComp->countOfRefinarys);
	generalArrayFunction(pComp->refineryArr, pComp->countOfRefinarys, sizeof(Refinery), printRefinery);
	printf("\nThere are %d deliveries in the company:\n", nodeCounter(&pComp->deliverysList));
	L_print(&pComp->deliverysList, printDelivery);
	printf("\nThere are %d vehicle in the company:\n", pComp->countOfTrucks);
	generalArrayFunction(pComp->truckArr, pComp->countOfTrucks, sizeof(Car), printCar);
}

//Function to free company
void freeCompany(Company* pComp)
{
	free(pComp->name);
	freeStationManager(pComp->stationManager);
	free(pComp->refineryArr);
	free(pComp->truckArr);
	L_free(&pComp->deliverysList, free);
}

//Function to read delivery list from binary file
int readDeliveriesFromFile(Company* pComp, FILE* fp)
{
	int count;
	Delivery* tDel = (Delivery*)malloc(sizeof(Delivery));
	if (!tDel)
	{
		ALLOCATION_ERROR
	}
	NODE* p = &pComp->deliverysList.head;
	if (fread(&count, sizeof(int), 1, fp) != 1)
	{
		printf("Error reading list size\n");
		return 0;
	}
	for (int i = 0; i < count; i++)
	{
		if (!readDeliveryFromFile(tDel, pComp->stationManager->stationArr,
			pComp->stationManager->countOfStations, pComp->refineryArr, pComp->countOfRefinarys, fp))
		{
			printf("Error reading delivery list\n");
			return 0;
		}
		L_insert(p, tDel);
		p = p->next;
	}
	return 1;
}
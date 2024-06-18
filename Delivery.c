#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Delivery.h"
#include "General.h"
#include "fileHelper.h"

//Function to initializes delivery
int initDelivery(Delivery* pDelivery, Car* theCar, Station** stationArr,int count1, Refinery* refineryArr, int count2)
{
	if (!getRefinery(pDelivery, refineryArr, count2))
		return 0;
	if (!getStation(pDelivery, stationArr, count1))
		return 0;
	printf("Please enter the delivery date:\n");
	getCorrectDate(&pDelivery->date);
	pDelivery->truck = *theCar;
	return 1;
}

//Function to get refinery from user
int getRefinery(Delivery* pDelivery, Refinery* refineryArr, int count)
{
	if (count == 0)
	{
		printf("No refineries!\n");
		return 0;
	}
	int res = 0;
	generalArrayFunction(refineryArr, count, sizeof(Refinery), printRefinery);
	do
	{
		char* temp;
		getRefineryName(&temp);
		pDelivery->origin = getRefineryByName(refineryArr, count, temp);
		if (pDelivery->origin)
			res = 1;
		else
			printf("Refinery name does not exist, choose again\n");
	} while (!res);
	return 1;
}

//Function to get station from user
int getStation(Delivery* pDelivery, Station** stationArr, int count)
{
	if (count == 0)
	{
		printf("No stations!\n");
		return 0;
	}
	int res = 0;
	generalArrayFunction(stationArr, count, sizeof(Station*), printStation);
	do
	{
		char* temp;
		getStationName(&temp);
		pDelivery->dest = getStationByName(stationArr, count, temp);
		if (pDelivery->dest)
			res = 1;
		else
			printf("Station name does not exist, choose again\n");
	} while (!res);
	return 1;
}

//Function to check if delivery is from refinery by name
int	isDeliveryFromSourceRefinery(const Delivery* pDelivery, const char* name)
{
	return strcmp(pDelivery->origin->name, name);
	
}

//Function to check if delivery is to station by name
int	isDeliveryToDestStation(const Delivery* pDelivery, const char* name)
{
	return strcmp(pDelivery->dest->name, name);
}

//Function to print delivery
void printDelivery(const void* pDeli)
{
	Delivery* tDel = (Delivery*)pDeli;
	printf("Delivery details:\n");
	printDate(&tDel->date);
	printf("\nOrigin refinery:\t%s\n", tDel->origin->name);
	printf("\nDestination station:\t%s\n", tDel->dest->name);
	printf("\nVehicle details:\n");
	printCar(&tDel->truck);
}

//Function to write delivery list to binary file
int writeDeliveryListToFile(const LIST* pLs, FILE* fp)
{
	int len = nodeCounter(pLs);
	if (fwrite(&len, sizeof(int), 1, fp) != 1)
		return 0;
	NODE* p = pLs->head.next;
	while (p != NULL)
	{
		if (!writeDeliveryToFile(((Delivery*)(p->key)), fp))
			return 0;
		p = p->next;
	}
	return 1;
}

//Function to write delivery to binary file
int writeDeliveryToFile(const Delivery* pDel, FILE* fp)
{
	if (!writeStringToFile(pDel->origin->name, fp, "Error write refinery name\n")
		|| !writeStringToFile(pDel->dest->name, fp, "Error write station name\n")
		|| !saveDateToFile(fp, &pDel->date)
		|| fwrite(&pDel->truck, sizeof(Car), 1, fp) != 1)
		return 0;
	return 1;
}

//Function to read delivery from binary file
int readDeliveryFromFile(Delivery* pDel, Station** stationArr, int countSta, Refinery* refineryArr, int countRef, FILE* fp)
{
	char* temp = readStringFromFile(fp, "Error reading refinery name\n");
	if (!temp)
		return 0;
	pDel->origin = getRefineryByName(refineryArr, countRef, temp);
	temp = readStringFromFile(fp, "Error reading station name\n");
	if (!temp)
		return 0;
	pDel->dest = getStationByName(stationArr, countSta, temp);
	if (!readDateFromFile(fp, &pDel->date)
		|| fread(&pDel->truck, sizeof(Car), 1, fp) != 1)
		return 0;
	return 1;
}

//Function to print delivery
void genericPrintDelivery(const void* pF)
{
	Delivery* pDeli = (Delivery*)pF;
	printDelivery(pDeli);
}

//Function to free delivery
void freeDelivery(Delivery* pDeli)
{
	//nothing to free
}

//Function to save delivery to text file
int saveDeliveryToText(const Delivery* pDeli, FILE* fp)
{
	if (!pDeli)
		return 0;
	saveDateText(&pDeli->date, fp);
	fprintf(fp, "%s\n", pDeli->origin->name);
	fprintf(fp, "%s\n", pDeli->dest->name);
	if (!saveCarText(&pDeli->truck, fp))
		return 0;
	return 1;
}

//Function to read delivery from text file
int loadDeliveryText(Delivery* pDeli, Refinery* refineryArr, int countRef, Station** stationArr, int countSta, FILE* fp)
{
	if (!pDeli)
		return 0;
	loadDateText(&pDeli->date, fp);
	char temp[MAX_STR_LEN];
	myGets(temp, MAX_STR_LEN, fp);
	char* dynTemp = getDynStr(temp);
	pDeli->origin = getRefineryByName(refineryArr, countRef, dynTemp);
	if (!pDeli->origin)
		return 0;
	myGets(temp, MAX_STR_LEN, fp);
	dynTemp = getDynStr(temp);
	pDeli->dest = getStationByName(stationArr, countSta, dynTemp);
	if (!pDeli->dest)
		return 0;
	if (!loadCarText(&pDeli->truck, fp))
		return 0;
	return 1;
}

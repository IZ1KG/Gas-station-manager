#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CompanyFile.h"
#include "General.h"
#include "fileHelper.h"

//Function that initializes the company from a binary file
int initCompanyfromFile(Company* pComp, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "rb");
	if (!fp)
	{
		printf("Error open company file\n");
		return 0;
	}
	pComp->name = readStringFromFile(fp, "Error reading company name\n");
	if (!pComp->name)
	{
		ERROR_FILE
	}
	pComp->stationManager = (StationManager*)malloc(sizeof(StationManager));
	if (!pComp->stationManager)
	{
		free(pComp->name);
		printf("Allocation error\n");
		ERROR_FILE
	}
	initStationManagerNoPerson(pComp->stationManager);
	PersonManager* pPerMan = (PersonManager*)malloc(sizeof(PersonManager));
	if (!pPerMan)
	{
		printf("Allocation error\n");
		ERROR_FREE_ALLOCATED_STATION_MAN
	}
	initPersonManager(pPerMan);
	pComp->stationManager->pManager = pPerMan;
	if (!readStationManagerFromFile(pComp->stationManager, fp))
	{
		free(pComp->stationManager->pManager);
		ERROR_FREE_ALLOCATED_STATION_MAN
	}

	if (!readIntFromFile(&pComp->countOfRefinarys, fp, "Error reading refinery count\n"))
	{
		ERROR_FREE_STATION_MANAGER
	}
	if (!createRefineryArr(pComp))
	{
		printf("Allocation error\n");
		ERROR_FREE_STATION_MANAGER
	}
	for (int i = 0; i < pComp->countOfRefinarys; i++)
	{
		if (!readRefineryFromFile(&pComp->refineryArr[i], fp))
		{
			ERROR_FREE_REFINERY
		}
	}
	L_init(&pComp->deliverysList);
	if (!readDeliveriesFromFile(pComp, fp))
	{
		ERROR_FREE_REFINERY
	}

	if (!readIntFromFile(&pComp->countOfTrucks, fp, "Error reading car count\n"))
	{
		ERROR_FREE_LIST
	}
	if (!createCarArr(pComp))
	{
		ERROR_FREE_LIST
	}
	if (fread(pComp->truckArr, sizeof(Car), pComp->countOfTrucks, fp) != pComp->countOfTrucks)
	{
		printf("Error read vehicle array\n");
		free(pComp->truckArr);
		ERROR_FREE_LIST
	}
	SUCCESS_FILE
}

//Function that saves the company to a binary file
int writeCompanyToFile(const Company* pComp, const char* fileName)
{
	if (!pComp)
		return 0;
	FILE* fp = fopen(fileName, "wb");
	if (!fp)
	{
		printf("Error open copmpany file to write\n");
		return 0;
	}
	if (!writeStringToFile(pComp->name, fp, "Error writing company name\n"))
	{
		ERROR_FILE
	}
	if (!writeStationManagerToFile(pComp->stationManager, fp))
	{
		ERROR_FILE
	}
	if (!writeRefineriesToFile(pComp->refineryArr, pComp->countOfRefinarys, fp))
	{
		ERROR_FILE
	}
	if (!writeDeliveryListToFile(&(pComp->deliverysList), fp))
	{
		ERROR_FILE
	}

	if (fwrite(&pComp->countOfTrucks, sizeof(int), 1, fp) != 1)
	{
		ERROR_FILE
	}
	if (fwrite(pComp->truckArr, sizeof(Car), pComp->countOfTrucks, fp) != pComp->countOfTrucks)
	{
		ERROR_FILE
	}
	SUCCESS_FILE
}

//Function that saves the company to a text file
int saveCompanyToText(const Company* pComp, const char* fileName)
{
	FILE* fp;

	fp = fopen(fileName, "w");
	if (!fp)
	{
		printf("Error open company file to write\n");
		return 0;
	}

	fprintf(fp, "%s\n", pComp->name);
	if (!saveStationManagerText(pComp->stationManager, fp))
	{
		printf("Error writing station manager");
		ERROR_FILE
	}

	fprintf(fp, "%d\n", pComp->countOfRefinarys);
	for (int i = 0; i < pComp->countOfRefinarys; i++)
	{
		if (!saveRefineryText(&pComp->refineryArr[i], fp))
		{
			printf("Error write refinery\n");
			ERROR_FILE
		}
		
	}
	int count = nodeCounter(&pComp->deliverysList);
	fprintf(fp, "%d\n", count);
	if (count > 0)
	{
		NODE* pN = pComp->deliverysList.head.next;
		Delivery* pTemp;

		while (pN != NULL)
		{
			pTemp = (Delivery*)pN->key;
			if (!saveDeliveryToText(pTemp, fp))
			{
				printf("Error write delivery\n");
				ERROR_FILE
			}
			pN = pN->next;
		}
	}

	fprintf(fp, "%d\n", pComp->countOfTrucks);
	for (int i = 0; i < pComp->countOfTrucks; i++)
	{
		if (!saveCarText(&pComp->truckArr[i], fp))
		{
			printf("Error write car\n");
			ERROR_FILE
		}
	}
	SUCCESS_FILE
}

//Function that initializes company from a text file
int loadCompanyFromText(Company* pComp, const char* fileName)
{
	FILE* fp;

	fp = fopen(fileName, "r");
	if (!fp)
	{
		printf("Error open company file\n");
		return 0;
	}
	char temp[MAX_STR_LEN];

	myGets(temp, MAX_STR_LEN, fp);
	pComp->name = getDynStr(temp);
	if (!pComp->name)
	{
		ERROR_FILE
	}
	pComp->stationManager = (StationManager*)malloc(sizeof(StationManager));
	if (!pComp->stationManager)
	{
		free(pComp->name);
		printf("Allocation error\n");
		ERROR_FILE
	}
	initStationManagerNoPerson(pComp->stationManager);
	PersonManager* pPerMan = (PersonManager*)malloc(sizeof(PersonManager));
	if (!pPerMan)
	{
		ERROR_FREE_ALLOCATED_STATION_MAN
	}
	initPersonManager(pPerMan);
	pComp->stationManager->pManager = pPerMan;
	if (!loadStationManagerText(pComp->stationManager, fp))
	{
		printf("Error loading station manager\n");
		free(pComp->stationManager->pManager);
		ERROR_FREE_ALLOCATED_STATION_MAN
	}
	
	fscanf(fp, "%d", &pComp->countOfRefinarys);
	//clean the buffer
	fgetc(fp);
	pComp->refineryArr = (Refinery*)malloc(sizeof(Refinery) * pComp->countOfRefinarys);
	if (!pComp->refineryArr)
	{
		printf("Allocation error\n");
		ERROR_FREE_STATION_MANAGER
	}
	for (int i = 0; i < pComp->countOfRefinarys; i++)
	{
		if (!loadRefineryText(&pComp->refineryArr[i], fp))
		{
			printf("Error loading refinery\n");
			ERROR_FREE_REFINERY
		}
	}
	L_init(&pComp->deliverysList);
	int count;
	fscanf(fp, "%d", &count);
	//clean the buffer
	fgetc(fp);
	Delivery* pDeli;
	for (int i = 0; i < count; i++)
	{
		pDeli = (Delivery*)calloc(1, sizeof(Delivery));
		if (!pDeli)
			break;
		if (!loadDeliveryText(pDeli, pComp->refineryArr, pComp->countOfRefinarys, pComp->stationManager->stationArr, pComp->stationManager->countOfStations, fp))
		{
			printf("Error loading airport from file\n");
			ERROR_FREE_REFINERY
		}
		insertDeliveryToList(pDeli, &pComp->deliverysList);
	}
	fscanf(fp, "%d", &pComp->countOfTrucks);
	//clean the buffer
	fgetc(fp);
	pComp->truckArr = (Car*)malloc(sizeof(Car) * pComp->countOfTrucks);
	if (!pComp->truckArr)
	{
		printf("Allocation error\n");
		L_free(&pComp->deliverysList, free);
		ERROR_FREE_REFINERY
	}
	for (int i = 0; i < pComp->countOfTrucks; i++)
	{
		if (!loadCarText(&pComp->truckArr[i], fp))
		{
			printf("Error load car\n");
			free(pComp->truckArr);
			L_free(&pComp->deliverysList, free);
			ERROR_FREE_REFINERY
		}
	}
	SUCCESS_FILE;
}

int createCarArr(Company* pComp)
{
	pComp->truckArr = (Car*)malloc(sizeof(Car) * pComp->countOfTrucks);
	if (!pComp->truckArr)
	{
		ALLOCATION_ERROR
	}
	return 1;
}

int createRefineryArr(Company* pComp)
{
	pComp->refineryArr = (Refinery*)malloc(sizeof(Refinery) * pComp->countOfRefinarys);
	if (!pComp->refineryArr)
	{
		ALLOCATION_ERROR
	}
	return 1;
}
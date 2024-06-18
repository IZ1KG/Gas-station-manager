#include <stdio.h>
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <time.h>
#include "General.h"

int main()
{
	Company comp;
	srand((unsigned int)time(NULL));
	if (!initCompanyChoice(&comp))
	{
		printf("Init error\n");
		return 0;
	}
	int option;
	int stop = 0;
	do
	{
		option = menu();
		switch (option)
		{
		case eShowAll:
			printCompany(&comp);
			break;
		case eShowStations:
			generalArrayFunction(comp.stationManager->stationArr, comp.stationManager->countOfStations, sizeof(Station*), printStation);
			break;
		case eShowRefineries:
				generalArrayFunction(comp.refineryArr, comp.countOfRefinarys, sizeof(Refinery), printRefinery);
				break;
		case eShowDeliveris:
			L_print(&comp.deliverysList, printDelivery);
			break;
		case eShowVehicels:
			generalArrayFunction(comp.truckArr, comp.countOfTrucks, sizeof(Car), printCar);
			break;
		case eAddStation:
			addStation(comp.stationManager);
			break;
		case eAddPump:
			addPump(comp.stationManager);
			break;
		case eAddRefinery:
			addRefinery(&comp);
			break;
		case eAddDelivery:
			addDeliveryToListByDate(&comp);
			break;
		case eAddVehicle:
			addCarToCompany(&comp);
			break;
		case eAddCustomer:
			addCustomer(comp.stationManager);
			break;
		case eAddEmployee:
			addEmployee(comp.stationManager);
			break;
		case eAddPerson:
			addPerson(comp.stationManager->pManager);
			break;
		case eSort:
			getStationAndSort(comp.stationManager);
			break;
		case eFind:
			binarySearchEmployee(comp.stationManager);
			break;
		case eSales:
			makeSales(comp.stationManager);
			break;
		case eProfits:
			showBestStation(comp.stationManager);
			break;
		case eSaveToBinary:
			writeToBinary(&comp);
			break;
			break;
		case eSaveToText:
			writeToText(&comp);
			break;
		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			freeCompany(&comp);
			break;
		default:
			printf("Wrong value\n");
			break;
		}
	}while (!stop);
	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofOptions; i++)
		printf("%d - %s\n", i, str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	char tav;
	scanf("%c", &tav);
	return option;
}

int initMenu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofInitOptions; i++)
		printf("%d - %s\n", i, str2[i]);
	scanf("%d", &option);
	char tav;
	scanf("%c", &tav);
	return option;
}

//initalize company from binary file
int initCompanyFromBianryFile(Company* pCompany)
{
	if (!initCompanyfromFile(pCompany, COMPANY_BINARY_FILE_NAME))
		return 0;
	return 1;
}

//initalize company from text file
int initCompanyFromTextFile(Company* pCompany)
{
	if (!loadCompanyFromText(pCompany, COMPANY_TEXT_FILE_NAME))
		return 0;
	return 1;
}

//Save company to binary file
void writeToBinary(Company* pComp)
{
	if (!writeCompanyToFile(pComp, COMPANY_BINARY_FILE_NAME))
		printf("write binary unsuccsecful\n");
}

//Save company to text file
void writeToText(Company* pComp)
{
	if (!saveCompanyToText(pComp, COMPANY_TEXT_FILE_NAME))
		printf("write text unsuccsecful\n");
}

int initCompanyChoice(Company* pComp)
{
	int option;
	do
	{
		option = initMenu();
		switch (option)
		{
		case eInitFromBinary:
			return initCompanyFromBianryFile(pComp);
		case eInitFromText:
			return initCompanyFromTextFile(pComp);
		default:
			printf("Wrong value\n");
			break;
		}
	} while (1);
}
#ifndef __COMPANY__
#define __COMPANY__

#include "List.h"
#include "Station.h"
#include "Refinery.h"
#include "Car.h"
#include "StationManager.h"
#include "Delivery.h"

typedef struct
{
	char* name;
	StationManager* stationManager;
	LIST deliverysList;
	Refinery* refineryArr;
	int countOfRefinarys;
	Car* truckArr;
	int countOfTrucks;
}Company;

int	initCompany(Company* pCompany);
int addCarToCompany(Company* pComp);
void addDeliveryToListByDate(Company* pComp);
int addRefinery(Company* pComp);
void printCompany(Company* pComp);
void freeCompany(Company* pComp);
int readDeliveriesFromFile(Company* pComp, FILE* fp);
void insertDeliveryToList(Delivery* pDeli, LIST* pList);

#endif
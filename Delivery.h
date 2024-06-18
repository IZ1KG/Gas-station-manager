#ifndef __DELIVERY__
#define __DELIVERY__

#include "Date.h"
#include "Car.h"
#include "Station.h"
#include "Refinery.h"
#include "General.h"

typedef struct
{
	Station* dest;
	Refinery* origin;
	Date date;
	Car truck;
}Delivery;

int initDelivery(Delivery* pDelivery, Car* theCar, Station** stationArr, int count1, Refinery* refineryArr, int count2);
int getRefinery(Delivery* pDelivery, Refinery* refineryArr, int count);
int getStation(Delivery* pDelivery, Station** stationArr, int count);
int	isDeliveryFromSourceRefinery(const Delivery* pDelivery, const char* name);
int	isDeliveryToDestStation(const Delivery* pDelivery, const char* name);
void printDelivery(const void* pDelivery);
int writeDeliveryListToFile(const LIST* pLs, FILE* fp);
int writeDeliveryToFile(const Delivery* pDel, FILE* fp);
int readDeliveryFromFile(Delivery* pDel, Station** stationArr, int countSta, Refinery* refineryArr, int countRef, FILE* fp);
void genericPrintDelivery(const void* pF);
void freeDelivery(Delivery* pDeli);
int saveDeliveryToText(const Delivery* pDeli, FILE* fp);
int loadDeliveryText(Delivery* pDeli, Refinery* refineryArr, int countRef, Station** stationArr, int countSta, FILE* fp);

#endif
#ifndef __REFINERY__
#define __REFINERY__

#include "Pump.h"
#include "General.h"

typedef struct
{
	char* name;
	eFuelType type;
	float price;
}Refinery;


void initRefinery(Refinery* pRefinery, Refinery* refineryArr, int count);
void getFuelCost(Refinery* pRefinery);
void getRefineryNameUnique(Refinery* refineryArr, int refineryCount, char** name);
void getRefineryName(char** name);
void printRefinery(Refinery* pRefinary);
void freeRefinery(Refinery* pRefinery);
int readRefineryFromFile(Refinery* pRef, FILE* fp);
int writeRefineryToFile(const Refinery* pRef, FILE* fp);
int writeRefineriesToFile(const Refinery* refineryArr, int count, FILE* fp);
int saveRefineryText(const Refinery* pRef, FILE* fp);
int loadRefineryText(Refinery* pRef, FILE* fp);
Refinery* getRefineryByName(Refinery* refineryArr, int count, char* name);

#endif
#ifndef __PUMP__
#define __PUMP__

#include "General.h"
#define PUMP_CODE_LEN 9

typedef enum {
	ePetrol95, ePetrol98, eDiesel, eNofFuelTypes
} eFuelType;

static const char* pumpTypeStr[eNofFuelTypes]
= { "Petrol95", "Petrol98", "Diesel" };

typedef struct
{
	char code[PUMP_CODE_LEN + 1];
	eFuelType fuelType;
}Pump;

void initPump(Pump* pumpArr, int count, Pump* pPump);
int isCodeUnique(Pump* pumpArr, int count, const char* code);
void printPump(const void* pPump);
void getPumpCode(char* code);
int checkCode(char* code);
eFuelType getFuelType();
void freePump(Pump* pPump);
Pump* findPumpByCode(Pump* pumpArr, int count, char* code);
int writePumpsToFile(const Pump* pumpArr, const  int count, FILE* fp);
int writePumpToFile(const Pump* pPump, FILE* fp);
int readPumpFromFile(Pump* pPump, FILE* fp);
int savePumpText(Pump* pPump, FILE* fp);
int loadPumpText(Pump* pPump, FILE* fp);

#endif

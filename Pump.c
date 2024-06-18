#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Pump.h"
#include "General.h"
#include "fileHelper.h"

//Function to initialize pump
void initPump(Pump* pumpArr,int count,Pump* pPump)
{	
	int unique = 0;
	do
	{
		getPumpCode(pPump->code);
		unique = isCodeUnique(pumpArr,count,pPump->code);
	} while (!unique);
	pPump->fuelType = getFuelType();
}

//Function to check if a code is unique
int isCodeUnique(Pump* pumpArr, int count,  const char* code)
{
	for (int i = 0; i < count; i++)
	{
		if (strcmp(pumpArr[i].code, code) == 0)
			return 0;
	}
	return 1;
}

//Function to print pump
void printPump(const void* pPump)
{
	Pump* tPump = (Pump*)pPump;
	printf("Pump details:\n");
	printf("Pump code: %-20s", tPump->code);
	printf("Fuel type: %-20s\n", pumpTypeStr[tPump->fuelType]);
}

//Function to get pump code from user
void getPumpCode(char* code)
{
	char tempCode[MAX_STR_LEN];
	int res;
	do {
		printf("Enter pump code: (3 first uppercase leteers and then 6 digits)\n");
		myGets(tempCode, MAX_STR_LEN, stdin);
		res = 1;
		if (strlen(tempCode) != PUMP_CODE_LEN)
		{
			printf("code should be %d letters\n", PUMP_CODE_LEN);
			res = 0;
		}
		else if(!checkCode(tempCode))
			res = 0;
	} while (!res);
	strcpy(code, tempCode);
}

//Function to check if pump code is 3 - upper letters and then 6 digits
int checkCode(char* code)
{
	for (int i = 0; i < PUMP_CODE_LEN; i++)
	{
		if (i <= 2)
		{
			if (!isUpperChar(code[i]))
			{
				printf("The first 3 letters need's to be upper.\n");
				return 0;
			}
		}
		else if (!isDigitChar(code[i]))
		{
			printf("The 4th char and above needs to be a digit only.\n");
			return 0;
		}
	}
	return 1;
}

//Function to get fuel type from user
eFuelType getFuelType()
{
	int option;
	printf("\n\n");
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofFuelTypes; i++)
			printf("%d for %s\n", i, pumpTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofFuelTypes);
	getchar();
	return (eFuelType)option;
}

//Function to free pump
void freePump(Pump* pPump)
{
	//nothing to free.
}

//Function to find pump by code in array
Pump* findPumpByCode(Pump* pumpArr, int count, char* code)
{
	for (int i = 0; i < count; i++)
	{
		if (strcmp(pumpArr[i].code, code) == 0)
			return &pumpArr[i];
	}
	return NULL;
}

//Function that writes pump array to binary file
int writePumpsToFile(const Pump* pumpArr, const  int count, FILE* fp)
{
	if (fwrite(&count, sizeof(int), 1, fp) != 1)
		return 0;
	for (int i = 0; i < count; i++)
	{
		if (!writePumpToFile(&pumpArr[i], fp))
			return 0;
	}
	return 1;
}

//Function that writes pump to binary file
int writePumpToFile(const Pump* pPump, FILE* fp)
{
	if (!writeCharsToFile(pPump->code, PUMP_CODE_LEN, fp, "Error write pump code\n")
		|| fwrite(&(pPump->fuelType), sizeof(eFuelType), 1, fp) != 1)
		return 0;
	return 1;
}

//Function that read pump from binary file
int readPumpFromFile(Pump* pPump, FILE* fp)
{
	if (!readCharsFromFile(pPump->code, PUMP_CODE_LEN, fp, "Error read pump code\n")
		|| fread(&pPump->fuelType, sizeof(eFuelType), 1, fp) != 1)
		return 0;
	pPump->code[PUMP_CODE_LEN] = '\0';
	return 1;
}

//Function to write pump to text file
int savePumpText(Pump* pPump, FILE* fp)
{
	if (!pPump)
		return 0;
	fprintf(fp, "%s\n", pPump->code);
	fprintf(fp, "%d\n", pPump->fuelType);
	return 1;
}

//Function that reads pump from text file
int loadPumpText(Pump* pPump, FILE* fp)
{
	if (!pPump)
		return 0;
	myGets(pPump->code, MAX_STR_LEN, fp);
	fscanf(fp, "%d", &pPump->fuelType);
	//clean the buffer
	fgetc(fp);
	return 1;
}
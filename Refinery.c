#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Refinery.h"
#include "General.h"
#include "fileHelper.h"

//Function that initializes refinry
void initRefinery(Refinery* pRefinery, Refinery* refineryArr, int count)
{
	getRefineryNameUnique(refineryArr,count, &pRefinery->name);
	pRefinery->type = getFuelType();
	getFuelCost(pRefinery);
}

//Function to get fuel cost from user
void getFuelCost(Refinery* pRefinery)
{
	printf("Please enter the fuel cost per gallon:\n");
	scanf("%f", &pRefinery->price);
}

//Function to get a unique refinry name from user
void getRefineryNameUnique(Refinery* refineryArr, int refineryCount, char** name)
{
	Refinery* pRef = NULL;
	do {
		getRefineryName(name);
		pRef = getRefineryByName(refineryArr, refineryCount, *name);
		if (pRef != NULL)
			printf("Please choose a name that is not in use.");
	} while (pRef != NULL);
}

//Function to get refinery name from user
void getRefineryName(char** name)
{
	char temp[MAX_STR_LEN];
	printf("Enter refinery name:\n");
	myGets(temp, MAX_STR_LEN, stdin);
	*name = getDynStr(temp);
}

//Function to print refinery
void printRefinery(Refinery* pRefinery)
{
	printf("\nRefinery details:\n");
	printf("Refinery name: %-20s\n", pRefinery->name);
	printf("Refinery fuel type: %s, cost per gallon: %.2f\n", pumpTypeStr[pRefinery->type], pRefinery->price);
}	

//Function to free refinery
void freeRefinery(Refinery* pRefinery)
{
	free(pRefinery->name);
}

//Function to read refinery from binary file
int readRefineryFromFile(Refinery* pRef, FILE* fp)
{
	pRef->name = readStringFromFile(fp, "Error read refinery name\n");
	if (!pRef->name)
		return 0;
	if (fread(&(pRef->type), sizeof(eFuelType), 1, fp) != 1
		|| fread(&(pRef->price), sizeof(int), 1, fp) != 1)
	{
		free(pRef->name);
		return 0;
	}
	return 1;
}

//Function to write refinery array to binary file
int writeRefineriesToFile(const Refinery* refineryArr, int count, FILE* fp)
{
	if (fwrite(&count, sizeof(int), 1, fp) != 1)
		return 0;
	for (int i = 0; i < count; i++)
	{
		if (!writeRefineryToFile(&refineryArr[i], fp))
			return 0;
	}
	return 1;
}

//Function to write refinery to binary file
int writeRefineryToFile(const Refinery* pRef, FILE* fp)
{
	if (!writeStringToFile(pRef->name, fp, "Error write refinery name\n")
		|| fwrite(&pRef->type, sizeof(eFuelType), 1, fp) != 1
		|| fwrite(&pRef->price, sizeof(int), 1, fp) != 1)
		return 0;
	return 1;
}

//Function to write refinery to text file
int saveRefineryText(const Refinery* pRef, FILE* fp)
{
	if (!pRef)
		return 0;
	fprintf(fp, "%s\n", pRef->name);
	fprintf(fp, "%f\n", pRef->price);
	fprintf(fp, "%d\n", pRef->type);
	return 1;
}

//Function to read refinery from text file
int loadRefineryText(Refinery* pRef, FILE* fp)
{
	char temp[MAX_STR_LEN];
	if (!pRef)
		return 0;
	myGets(temp, MAX_STR_LEN, fp);
	pRef->name = getDynStr(temp);
	fscanf(fp, "%f", &pRef->price);
	//clean the buffer
	fgetc(fp);
	fscanf(fp, "%d", &pRef->type);
	return 1;
}

//Function to get refinery by name
Refinery* getRefineryByName(Refinery* refineryArr, int count, char* name)
{
	for (int i = 0; i < count; i++)
	{
		if (strcmp(refineryArr[i].name, name) == 0)
			return &refineryArr[i];
	}
	return NULL;
}
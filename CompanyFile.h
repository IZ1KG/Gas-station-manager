#ifndef __BINARY__
#define __BINARY__

#include "Company.h"

#define ERROR_FILE fclose(fp); return 0; 
#define ERROR_FREE_ALLOCATED_STATION_MAN free(pComp->name); free(pComp->stationManager); ERROR_FILE
#define ERROR_FREE_STATION_MANAGER free(pComp->name); freeStationManager(pComp->stationManager); ERROR_FILE
#define ERROR_FREE_REFINERY free(pComp->refineryArr); free(pComp->name); freeStationManager(pComp->stationManager); ERROR_FILE
#define ERROR_FREE_LIST L_free(&pComp->deliverysList, free); ERROR_FREE_REFINERY
#define SUCCESS_FILE fclose(fp); return 1;

int writeCompanyToFile(const Company * pComp, const char* fileName);
int initCompanyfromFile(Company * pComp, const char* fileName);
int createCarArr(Company * pComp);
int createRefineryArr(Company * pComp);
int loadCompanyFromText(Company * pComp, const char* fileName);
int saveCompanyToText(const Company * pComp, const char* fileName);

#endif
#ifndef __STATIONMANAGER__
#define __STATIONMANAGER__

#include "Station.h"
#include "PersonManager.h"

typedef struct
{
	Station** stationArr;
	int countOfStations;
	PersonManager* pManager;
}StationManager;

void initStationManager(StationManager* pStaMan, PersonManager* pManager);
void initStationManagerNoPerson(StationManager* pStaMan);
int addEmployee(StationManager* pStaMan);
void showBestStation(StationManager* pStaMan);
int addEmployeeExisting(PersonManager* pPerMan, Station* pStation);
int addEmployeeNew(PersonManager* pPerMan, Station* pStation);
int addCustomer(StationManager* pStaMan);
void makeSales(StationManager* pStaMan);
Station* chooseStation(StationManager* pStaMan, char* errorMsg, char* msg, char* errorMsg2);
int addCustomerExisting(PersonManager* pPerMan, Station* pStation);
int addCustomerNew(PersonManager* pPerMan, Station* pStation);
int compareStation(const void* e1, const void* e2);
int findNameIndex(const Station** stationArr, int count, char* name);
int addStation(StationManager* pStaMan);
void printStationManager(const StationManager* pStaMan);
void freeStationManager(StationManager* pStaMan);
int readStationManagerFromFile(StationManager* pStaMan, FILE* fp);
int writeStationManagerToFile(const StationManager* stationManager, FILE* fp);
int saveStationManagerText(StationManager* pStaMan, FILE* fp);
int loadStationManagerText(StationManager* pStaMan, FILE* fp);
int loadStationText(Station* pSta, Person** pPersonArr, int count, FILE* fp);
void getStationAndSort(StationManager* pSta);
void addPump(StationManager* pStaMan);
void binarySearchEmployee(StationManager* pStaMan);

#endif

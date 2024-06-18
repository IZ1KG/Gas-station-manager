#ifndef __STATION__
#define __STATION__

#include "Pump.h"
#include "Person.h"
#include "Employee.h"
#include "Customer.h"

typedef enum { eNone, eID, eSalary, eAge, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt] = {
	"None","ID", "Salary", "Age" };

typedef struct
{
	char* name;
	char* city;
	Pump* pumpsArr;
	int countOfPumps;
	Employee* employeeArr;
	int countOfEmployees;
	Customer* customerArr;
	int countOfCustomers;
	eSortOption	employeeSortOpt;
}Station;

int initStation(Station** stationArr, int count, Station* pStation);
int	isStationName(const Station* pStation, const char* name);
void printStation(const void* pStation);
void getStationNameUnique(Station** stationArr, int stationCount, char** name);
void getStationName(char** name);
void freeStation(void* pStation);
void makeSaleInStation(Station* pSta);
int getStationProfits(Station* pSta);
int addPumpToStation(Station* pSta);
int addCustomerToStation(Station* pStation, Person* pPer);
int addEmployeeToStation(Station* pStation, Person* pPer);
int writeStationToFile(const Station* pSta, FILE* fp);
int readStationFromFile(Station* pSta, Person** personArr, int count, FILE* fp);
int readCustomersFromFile(Station* pSta, Person** personArr, int count, FILE* fp);
int readEmployeesFromFile(Station* pSta, Person** personArr, int count, FILE* fp);
int readPumpsFromFile(Station* pSta, FILE* fp);
void sortEmployees(Station* pSta);
eSortOption showSortMenu();
void findEmployee(const Station* pSta);
int saveStationText(const Station* pSta, FILE* fp);
Station* getStationByName(Station** stationArr, int count, char* name);

#endif
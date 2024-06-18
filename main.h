#include "Company.h"
#include "CompanyFile.h"
#define EXIT		-1
#define COMPANY_TEXT_FILE_NAME "company.txt"
#define COMPANY_BINARY_FILE_NAME "company.bin"
typedef enum
{
	eShowAll, eShowStations, eShowRefineries,
	eShowDeliveris, eShowVehicels, eAddStation, eAddPump, eAddRefinery,
	eAddDelivery, eAddVehicle, eAddCustomer, eAddEmployee, eAddPerson, eSort,
	eFind, eSales, eProfits, eSaveToBinary, eSaveToText ,eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Print all company inforamtion",
	"Print stations", "Print refineries",
	"Print deliveris", "Print vehicle fleet", "Add station",
	"Add pump", "Add refinery", "Add delivery",
	"Add vehicle", "Add customer", "Add employee", "Add person",
	"Sort employee in station", "Find employeee", "Add sales randomly to station",
	"Show most profitable station", "Save system to binary", "Save system to text"};

typedef enum
{
	eInitFromBinary, eInitFromText, eNofInitOptions
} eInitMenuOptions;

const char* str2[eNofInitOptions] = { "Init from binary file", "Init from text file" };

int menu();
int initMenu();
int initCompanyFromBianryFile(Company* pCompany);
int initCompanyFromTextFile(Company* pCompany);
void writeToText(Company* pComp);
void writeToBinary(Company* pComp);
int initCompanyChoice(Company* pComp);
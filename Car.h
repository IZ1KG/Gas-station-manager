#ifndef __CAR__
#define __CAR__

#include "Pump.h"
#include "General.h"

typedef enum {
	ePrivate, eTruck, eMotorcycle, eNofVehicleTypes
} eVehicleType;

static const char* vehicleTypeStr[eNofVehicleTypes]
= { "Private", "Truck", "Motorcycle" };


typedef struct
{
	int licensePlate;
	eVehicleType	carType;
	eFuelType	fuelType;
}Car;

void initCar(Car* pCar, Car* CarArr, int CarCount);
eVehicleType getVehicleType();
const char* GetCarTypeStr(int type);
Car* getCarFromArr(Car* carArr, int count);
void getCarLicensePlate(const Car* carArr, int CarCount, int* licensePlate);
Car* findCarByLicensePlate(Car* carArr, int count, int licensePlate);
int	isLicensePlateUnique(const Car* CarArr, int CarCount, const int licensePlate);
void printCar(const void* pCar);
void freeCar(Car* pCar);
void genericPrintCar(void* pPl);
int saveCarText(const Car* car, FILE* fp);
int loadCarText(Car* pCar, FILE* fp);

#endif
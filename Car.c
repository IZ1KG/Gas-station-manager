#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "General.h"
#include "fileHelper.h"
#include "Car.h"

//Function to initialize car
void initCar(Car* pCar, Car* CarArr, int CarCount)
{
	getCarLicensePlate(CarArr, CarCount, &pCar->licensePlate);
	pCar->carType = getVehicleType();
	pCar->fuelType = getFuelType();
}

//Function to get vehicle type from user
eVehicleType getVehicleType()
{
	int option;
	printf("\n\n");
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofVehicleTypes; i++)
			printf("%d for %s\n", i, vehicleTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofVehicleTypes);
	getchar();
	return (eVehicleType)option;
}

//Function that gets string for a vehicle type 
const char* GetCarTypeStr(int type)
{
	if (type < 0 || type >= eNofVehicleTypes)
		return NULL;
	return vehicleTypeStr[type];
}

//Function to get a vehicle type from user
void getCarLicensePlate(const Car* carArr, int CarCount, int* licensePlate)
{
	int res = 0;
	do
	{
		printf("Enter license plate - valid number with %d digits\t", INT_LEN);
		scanf("%d", licensePlate);
		if (*licensePlate < MIN_INT || *licensePlate > MAX_INT)
			printf("The number inserted is out of range!\n");
		else if (!isLicensePlateUnique(carArr, CarCount, *licensePlate))
			printf("The license plate already exists in the systems, please choose a different one!\n");
		else
			res = 1;
	} while (!res);
}

//Function that checks if the license plate number is unique or not
int	isLicensePlateUnique(const Car* CarArr, int CarCount, const int licensePlate)
{
	for (int i = 0; i < CarCount; i++)
	{
		if (CarArr[i].licensePlate - licensePlate == 0)
			return 0;
	}
	return 1;
}

//Function that finds car by the license plate
Car* findCarByLicensePlate(Car* carArr, int count, int licensePlate)
{
	for (int i = 0; i < count; i++)
		if (carArr[i].licensePlate - licensePlate == 0)
			return &carArr[i];
	return NULL;
}

//Function that returns a car from an a car array based on user input
Car* getCarFromArr(Car* carArr, int count)
{
	int index = 0;
	if (count == 0)
	{
		printf("No vehicles available\n");
		return NULL;
	}
	printf("Car list:\n");
	for (int i = 0; i < count; i++)
	{
		printf("%d.  ", i + 1);
		printCar(&carArr[i]);
	}
	do {
		printf("Please enter index for the car:\n");
		scanf("%d", &index);
		if (index <= 0 || index > count)
		{
			printf("Plesae choose a number from 1 - %d\n", count);
			index = 0;
		}
	} while (!index);
	return &carArr[index - 1];
}

void printCar(const void* pCar)
{
	Car* tCar = (Car*)pCar;
	printf("License plate: %d, Vehicle type %s, Fuel type %s\n",
		tCar->licensePlate, vehicleTypeStr[tCar->carType], pumpTypeStr[tCar->fuelType]);
}

void freeCar(Car* pCar)
{
	//no need to free.
}

void genericPrintCar(void* pPl)
{
	const Car* pCar = (const Car*)pPl;
	printCar(pCar);
}

//Function that saves a car to text file
int saveCarText(const Car* pCar, FILE* fp)
{
	if (!pCar)
		return 0;
	fprintf(fp, "%d\n", pCar->carType);
	fprintf(fp, "%d\n", pCar->fuelType);
	fprintf(fp, "%d\n", pCar->licensePlate);
	return 1;
}

//Function that reads a car from text file
int loadCarText(Car* pCar, FILE* fp)
{
	if (!pCar)
		return 0;
	fscanf(fp, "%d", &pCar->carType);
	//clean the buffer
	fgetc(fp);
	fscanf(fp, "%d", &pCar->fuelType);
	//clean the buffer
	fgetc(fp);
	fscanf(fp, "%d", &pCar->licensePlate);
	//clean the buffer
	fgetc(fp);
	return 1;
}
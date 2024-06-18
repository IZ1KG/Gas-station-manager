#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "General.h"
#include "fileHelper.h"
#include "Employee.h"

//Function to initialize employee
void initEmployee(Employee* pEmp)
{
	initPerson(pEmp->person);
	initEmployeeNoPerson(pEmp);
}

//Function to print employee
void printEmployee(const void* pEmp)
{
	Employee* tEmp = (Employee*)pEmp;
	printPerson(&tEmp->person);
	printf("Salary: % -20d\n", tEmp->salary);
}

//Function to get salary from user
void getSalary(Employee* pEmp)
{
	printf("Please enter the salary of the employee\n");
	scanf("%d", &pEmp->salary);
}

//Function that compares employees by salary
int compareEmployeeBySalary(const void* emp1, const void* emp2)
{
	Employee* temp1 = (Employee*)emp1;
	Employee* temp2 = (Employee*)emp2;
	return (temp1->salary - temp2->salary);
}

//Function that compares employees by id number
int compareEmployeeByID(const void* e1, const void* e2)
{
	Employee* t1 = (Employee*)e1;
	Employee* t2 = (Employee*)e2;
	return t1->person->id - t2->person->id;
}

//Function that compares employee by age
int compareEmployeeByAge(const void* e1, const void* e2)
{
	Employee* t1 = (Employee*)e1;
	Employee* t2 = (Employee*)e2;
	return compareDate(&t1->person->dateOfBirth, &t2->person->dateOfBirth);
}

//Function to initialize employee without person data
void initEmployeeNoPerson(Employee* pEmp)
{
	getSalary(pEmp);
}

//Function to write employee array to binary file
int writeEmployeesToFile(const Employee* employeeArr, const int count, FILE* fp)
{
	if (fwrite(&count, sizeof(int), 1, fp) != 1)
		return 0;
	for (int i = 0; i < count; i++)
	{
		if (!writeEmployeeToFile(&employeeArr[i], fp))
			return 0;
	}
	return 1;
}

//Function that writes employee to binary file
int writeEmployeeToFile(const Employee* pEmployee, FILE* fp)
{
	if (fwrite(&pEmployee->person->id, sizeof(int), 1, fp) != 1 ||
		fwrite(&pEmployee->salary, sizeof(int), 1, fp) != 1)
		return 0;
	return 1;
}

//Function that reads employee from binary file
int readEmployeeFromFile(Employee* pEmp, Person** personArr, int count, FILE* fp)
{
	int id;
	if (fread(&id, sizeof(int), 1, fp) != 1)
		return 0;
	pEmp->person = getPersonByID(personArr, count, id);
	if (!pEmp->person)
		return 0;
	if (fread(&(pEmp->salary), sizeof(int), 1, fp) != 1)
		return 0;
	return 1;
}

//Function that writes employee to text file
int saveEmployeeText(Employee* pEmp, FILE* fp)
{
	if (!pEmp)
		return 0;
	fprintf(fp, "%d\n", pEmp->person->id);
	fprintf(fp, "%d\n", pEmp->salary);
	return 1;
}

//Function that reads employee from text file
int loadEmployeeText(Employee* pEmp, Person** personArr, int count, FILE* fp)
{
	if (!pEmp)
		return 0;
	int temp;
	fscanf(fp, "%d", &temp);
	//clean the buffer
	fgetc(fp);
	pEmp->person = getPersonByID(personArr, count, temp);
	if (!pEmp->person)
		return 0;
	fscanf(fp, "%d", &pEmp->salary);
	//clean the buffer
	fgetc(fp);
	return 1;
}
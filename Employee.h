#ifndef __EMPLOYEE__
#define __EMPLOYEE__

#include "Person.h"

typedef struct
{
	int salary;
	Person* person;
}Employee;

int compareEmployeeBySalary(const void* emp1, const void* emp2);
void initEmployee(Employee* pEmp);
void printEmployee(const void* pEmp);
void getSalary(Employee* pEmp);
int compareEmployeeByID(const void* e1, const void* e2);
int compareEmployeeByAge(const void* e1, const void* e2);
void initEmployeeNoPerson(Employee* pEmp);
int writeEmployeesToFile(const Employee* employeeArr, const int count, FILE* fp);
int writeEmployeeToFile(const Employee* pEmployee, FILE* fp);
int readEmployeeFromFile(Employee* pEmp, Person** personArr, int count, FILE* fp);
int saveEmployeeText(Employee* pEmp, FILE* fp);
int loadEmployeeText(Employee* pEmp, Person** personArr, int count, FILE* fp);

#endif
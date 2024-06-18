#ifndef __GENERAL__
#define __GENERAL__

#include "List.h"
#define MAX_STR_LEN 255
#define MAX_INT 999999999
#define MIN_INT 100000000
#define INT_LEN 9
#define ALLOCATION_ERROR printf("Allocation error\n"); return 0;

char* getStrExactName(const char* msg);
char* myGets(char* buffer, int size, FILE* source);
char* getDynStr(char* str);
int isUpperChar(char ch);
int isDigitChar(char ch);
char** splitCharsToWords(char* str, int* pCount, int* pTotalLength);
char getCharExistNew(char* msg);
int nodeCounter(const LIST* list);
void generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element));
int findInArray(const void* arr, int count, int typeSize, const void* element, int(*compare)(const void* t1, const void* t2));


#endif


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "General.h"



char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	printf("%s\t", msg);
	myGets(temp, MAX_STR_LEN, stdin);
	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}

int isUpperChar(char ch)
{
	return ('A' <= ch && 'Z' >= ch);
}

int isDigitChar(char ch)
{
	return ('0' <= ch && '9' >= ch);
}

char getCharExistNew(char* msg)
{
	printf("%s", msg);
	char ch;
	do {
		printf("Enter e for existing, n for new:");
		scanf("%c", &ch);
	} while (ch != 'e' && ch != 'n' && ch != 'E' && ch != 'N');
	return ch;
}

char* myGets(char* buffer, int size, FILE* source)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do {
			ok = fgets(buffer, size, source);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			//trim end spaces
			while ((buffer < back) && (isspace(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

char** splitCharsToWords(char* str, int* pCount, int* pTotalLength)
{
	char temp[255];
	char* delimiters = " ";
	char* word;
	int count = 0;

	strcpy(temp, str);
	char** wordsArray = NULL;
	*pTotalLength = 0;

	word = strtok(temp, delimiters);
	while (word != NULL)
	{
		wordsArray = (char**)realloc(wordsArray, (count + 1) * sizeof(char*));
		if (!wordsArray)
			return 0;
		wordsArray[count] = getDynStr(word);
		count++;
		*pTotalLength += (int)strlen(word);
		word = strtok(NULL, delimiters);
	}
	*pCount = count;
	return wordsArray;
}

void generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element))
{
	for (int i = 0; i < size; i++)
		func((char*)(arr)+(i * typeSize));
}

int findInArray(const void* arr, int count, int typeSize, const void* element, int(*compare)(const void* t1, const void* t2))
{
	for (int i = 0; i < count; i++)
	{
		if (compare((char*)(arr)+i * typeSize, element) == 0)
			return i;
	}
	return -1;
}

//counting how many nodes are in list
int nodeCounter(const LIST* list)
{
	int counter = 0;
	const NODE* pNode = &list->head;
	while (pNode->next != NULL)
	{
		pNode = pNode->next;
		counter++;
	}
	return counter;
}

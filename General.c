#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "General.h"

static const char* AttributeTypeStr[eNoTypes]
= { "SourceName", "DestName", "Date", "PlaneCode" };

char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	printf("%s\t", msg);
	myGets(temp, MAX_STR_LEN);

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



char*  myGets(char* buffer, int size)
{
	if (buffer != NULL && size > 0)
	{
		if (fgets(buffer, size, stdin))
		{
			buffer[strcspn(buffer, "\n")] = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

char**	splitCharsToWords(char* str, int* pCount, int* pTotalLength)
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
		wordsArray = (char**)realloc(wordsArray,(count + 1)*sizeof(char*));
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

void generalArrayFunction(void* arr, int sizeOfArr, int sizeOfElementInBytes, void(*f)(const void*))
{
	char* startPoint = (char*)arr;
	for (int i = 0; i < sizeOfArr; i++)
	{
		f((char*)arr + i * sizeOfElementInBytes);
		//f((const void*)(startPoint + i * sizeOfElementInBytes));
	}
	//for (int i = 0; i < sizeOfArr; i++)
	//{
	//	f((char*)arr + i * sizeOfElementInBytes);
	//}
}

Type findFlightAttribute()
{
	int option;
	printf("\n\n");
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNoTypes; i++)
			printf("%d for %s\n", i, AttributeTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNoTypes);
	getchar();
	return (Type)option;
}

void* getWantedFlight(Type type)
{
	switch (type)
	{
	case 0:
	{
		char* sName = getStrExactName("Enter Wanted Source Name");
		return sName;
	}
	case 1:
	{
		char* dName = getStrExactName("Enter Wanted Destination Name");
		return dName;
	}
	case 2:
	{
	/*	Date* pDate = NULL;
		getCorrectDate(pDate);
		return pDate;*/
		return NULL;
	}
	case 3:
	{
		/*char* pCode = getStrExactName("Enter Wanted Plane Code");
		return pCode;*/
		return NULL;
	}
	default:
		printf("\nNo Such Type\n");
	}
	return NULL;
}
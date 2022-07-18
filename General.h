#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255
#include "Airline.h"

char*	getStrExactName(const char* msg);
char*	myGets(char* buffer, int size);
char*	getDynStr(char* str);
char**	splitCharsToWords(char* str,int* pCount,int* pTotalLength);
void generalArrayFunction(void* arr, int sizeOfArr, int sizeOfElementInBytes, void(*f)(const void*)); //added
Type findFlightAttribute(); //added
void* getWantedFlight(Type type); //added



#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Airline.h"
#include "Airport.h"
#include "General.h"
#include "Date.h" //added


void	initAirline(Airline* pComp)
{
	printf("-----------  Init Airline Airline\n");
	pComp->name = getStrExactName("Enter Airline name");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	L_init(&pComp->flightDates); //added  -- init list
	pComp->flightDates.head.key = NULL; //added
	pComp->flightDates.head.next = NULL; //added
	pComp->sortType = eNoTypes;
}

int	addFlight(Airline* pComp,const AirportManager* pManager)
{
	if (pManager->airportsCount < 2)
	{
		printf("There are not enough airport to set a flight\n");
		return 0;
	}
	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount+1) * sizeof(Flight*));
	if (!pComp->flightArr)
		return 0;
	pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1,sizeof(Flight));
	if (!pComp->flightArr[pComp->flightCount])
		return 0;
	initFlight(pComp->flightArr[pComp->flightCount],pManager);
	addFlightDateToList(pComp, &pComp->flightArr[pComp->flightCount]->date);
	pComp->flightCount++;
		
	return 1;
}

void addFlightDateToList(Airline* pComp, Date* pDate)
{
	if (!pComp->flightDates.head.next) //first time
		L_insert(&pComp->flightDates.head, pDate);
	else
	{
		int index = findPlace(&pComp->flightDates, pDate); //added -- finds the place it should be
		if (index == 0)
			L_insert(&pComp->flightDates.head, pDate);
		if (index == -2)
			return;
		else
		{
			NODE* pos = pComp->flightDates.head.next;
			NODE* pos2 = &pComp->flightDates.head;
			int counter = 0;
			while (pos != NULL)
			{
				pos2 = pos2->next;
				pos = pos->next;
				counter++;
				if (counter == index)
					L_insert(pos2, pDate); //added -- add the date to the date list		
			}
		}
	}
}

//input: list of flight dates and a date
//output: the index where the date should be in the list
int findPlace(LIST* flightDates,Date* pDate) //added
{
	//if (!flightDates->head.next->key) //PROBLEM!
	//	return 0;

	if (checkDates(pDate, flightDates->head.next->key) > 0) // <= 0 before the first date on the list
	{
		return 0;
	} //if the new date smaller than the first

	NODE* pList = flightDates->head.next->next;
	int counter;
	for(counter = 1; pList != NULL && checkDates(pDate, pList->key) <= 0; counter++)
	{
		if (checkDates(pDate, pList->key) == 0)
			return -2;
		pList = pList->next;
	}

	return counter;
}

// returns 1 if first date earlier than the second
// returns -1 if the opposite, or returns 0 if dates are equal
int checkDates(const Date* d1, const Date* d2)
{
	//Date* date2 = (Date*)d2;
	if (d1->year != d2->year)
		return d1->year < d2->year ? 1 : -1;

	if (d1->month != d2->month)
		return d1->month < d2->month ? 1 : -1;

	if (d1->day != d2->day)
		return d1->day < d2->day ? 1 : -1;

	return 0;
}

int compareByPlaneCode(const void* flight1, const void* flight2) //added
{
	//Flight* f1 = (Flight*)flight1;
	//Flight* f2 = (Flight*)flight2;

	//return strcmp((char*)f1->thePlane.code, (char*)f2->thePlane.code);

	const Flight* pFlight1 = *(const Flight**)flight1;
	const Flight* pFlight2 = *(const Flight**)flight2;
	return strcmp(pFlight1->thePlane.code, pFlight2->thePlane.code);
}

int compareBySourceName(const void* flight1, const void* flight2) //added
{
	const Flight* f1 = (Flight*)flight1;
	const Flight* f2 = (Flight*)flight2;

	const char* s1 = *(char**)f1->nameSource; 
	const char* s2 = *(char**)f2->nameSource;

	return strcmp(s1, s2);
}

int compareByDestName(const void* flight1, const void* flight2) //added
{
	const Flight* pFlight1 = *(const Flight**)flight1;
	const Flight* pFlight2 = *(const Flight**)flight2;
	return strcmp(pFlight1->nameDest, pFlight2->nameDest);

}

int compareByDate(const void* flight1, const void* flight2) //added
{
	const Date* d1 = &(*(const Flight**)flight1)->date;
	const Date* d2 = &(*(const Flight**)flight2)->date;

	//Flight* f1 = (Flight*)flight1;
	//Flight* f2 = (Flight*)flight2;

	return checkDates(d1, d2)*-1;
}

int sort(Airline* airline, Type sortType) //added
{
	switch (sortType)
	{
	case 0:
	{
		qsort(airline->flightArr, airline->flightCount, sizeof(Flight*), compareBySourceName);
		return 1;
	}
	case 1:
	{
		qsort(airline->flightArr, airline->flightCount, sizeof(Flight*), compareByDestName);
		return 1;
	}
	case 2:
	{
		qsort(airline->flightArr, airline->flightCount, sizeof(Flight*), compareByDate);
		return 1;
	}
	case 3:
	{
		qsort(airline->flightArr, airline->flightCount, sizeof(Flight*), compareByPlaneCode);
		return 1;
	}
	default:
		printf("\nNo Such Type\n");
	}
	return 0;
}

void search(Airline* airline, Type sortType, void* object)
{
	if (airline->sortType == eNofPlaneTypes)
	{
		printf("Flights aren't sorted yet");
		return;
	}
	Flight** f = NULL, *temp = (Flight*)malloc(sizeof(Flight));
	if (!temp) return;
	switch (sortType)
	{
	case 0:
	{
		temp->nameSource = _strdup(object);
		f = (Flight**)bsearch(&temp, airline->flightArr, airline->flightCount, sizeof(Flight*), compareBySourceName);
		break;
	}
	case 1:
	{
		temp->nameDest = _strdup(object);
		f = (Flight**)bsearch(&temp, airline->flightArr, airline->flightCount, sizeof(Flight*), compareByDestName);		
		break;
	}
	case 2:
	{
		getCorrectDate(&temp->date);
		f = (Flight**)bsearch(&temp, airline->flightArr, airline->flightCount, sizeof(Flight*), compareByDate);
		break;
	}
	case 3:
	{
		getPlaneCode(temp->thePlane.code);
		f = (Flight**)bsearch(&temp, airline->flightArr, airline->flightCount, sizeof(Flight*), compareByPlaneCode);
		break;
	}
	default:
		printf("\nNo Such Type\n");
	}

	if (f != NULL)
		printFlight(f);
	else
		printf("Flight was not found");
	return;
}



void printCompany(const Airline* pComp)
{
	printf("Airline %s\n", pComp->name);
	printf("Has %d flights\n", pComp->flightCount);
	printFlightArr(pComp->flightArr, pComp->flightCount);
	L_print(&pComp->flightDates, printDate); //added
}


//void printDateForList(const void* p1) //added -- for L_print function 
//{
//	const Date* pDate = (const Date*)p1;
//	printDate(pDate);
//}

void	doCountFlightsFromName(const Airline* pComp)
{
	if (pComp->flightCount == 0)
	{
		printf("No flight to search\n");
		return;
	}

	char* tempName = getStrExactName("Please enter origin airport name");

	int count = 0;
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (isFlightFromSourceName(pComp->flightArr[i], tempName))
			count++;
	}

	free(tempName);

	if (count != 0)
		printf("There are %d ", count);
	else
		printf("There are No ");

	printf("flights from this airport\n");
}



void	printFlightArr(Flight** pFlight, int size)
{
	generalArrayFunction(pFlight, size, sizeof(Flight*), printFlight);
}

void	doPrintFlightsWithPlaneCode(const Airline* pComp)
{
	char code[MAX_STR_LEN];
	getPlaneCode(code);
	printf("All flights with plane code %s:\n",code);
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (isPlaneCodeInFlight(pComp->flightArr[i], code))
			printFlight(pComp->flightArr[i]);
	}
	printf("\n");

}

void	doPrintFlightsWithPlaneType(const Airline* pComp)
{
	ePlaneType type = getPlaneType();
	printf("All flights with plane type %s:\n", PlaneTypeStr[type]);
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (isPlaneTypeInFlight(pComp->flightArr[i], type))
			printFlight(pComp->flightArr[i]);
	}
	printf("\n");
}

void	freeFlightArr(Flight** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		freeFlight(arr[i]);
	}
}

void	freeCompany(Airline* pComp)
{
	freeFlightArr(pComp->flightArr, pComp->flightCount);
	free(pComp->flightArr);
	free(pComp->name);
	L_free(&pComp->flightDates, NULL);
}

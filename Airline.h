#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"
#include "list.h" //added

typedef enum {esortBySourceName, eSortByDestName, eSortByDate, eSortByPlaneCode, eNoTypes} Type; //added

typedef struct
{
	char*		name;
	int			flightCount;
	Flight**	flightArr;
	LIST flightDates;
	Type sortType; //added
}Airline;


void	initAirline(Airline* pComp);
int		addFlight(Airline* pComp,const AirportManager* pManager);
void	printCompany(const Airline* pComp);
void	printFlightArr(Flight** pFlight, int size);
void	doCountFlightsFromName(const Airline* pComp);
void	doPrintFlightsWithPlaneCode(const Airline* pComp);
void	doPrintFlightsWithPlaneType(const Airline* pComp);
void	freeFlightArr(Flight** arr, int size);
void	freeCompany(Airline* pComp);

void addFlightDateToList(Airline* pComp, Date* pDate); //added
int findPlace(LIST* flightDates, Date* pDate); //added
//int checkDates(Date* d1, Date* d2); //added
int checkDates(const Date* d1, const Date* d2); //added
//void printDateForList(const void* p1); //added
int compareByPlaneCode(const void* plan1Code, const void* plan2Code); //added
int compareBySourceName(const void* flight1, const void* flight2); //added
int compareByDestName(const void* flight1, const void* flight2); //added
int compareByDate(const void* flight1, const void* flight2); //added
int sort(Airline* airline, Type sortType); //added
void search(Airline* airline, Type sortType, void* object); //added




#endif


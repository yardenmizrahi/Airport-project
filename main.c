#include <stdio.h>
#include <stdlib.h>
#include "Airline.h"
#include "AirportManager.h"
#include "General.h"

#include "AIrportManagerText.h"
#include "AirlineBinary.h"

//last update 29.12

typedef enum 
{ 
	eAddFlight, eAddAirport, ePrintCompany, ePrintAirports,
	ePrintNumFlightsOrig, ePrintFlightsPlaneCode, ePrintFlightsPlaneType, eSortFlightsByAttribute, eSearchFlightsByAttribute,eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Flight", "Add Airport",
								"Print Airline", "Print all Airports",
								"Print number of flights from origin airport name",
								"Print all flights with plane code",
								"Print all flights with plane type",
                                "Sort all flights by sertain attribute",
                                "Search flight by sertain attribute"};

#define EXIT			-1
int menu();
int getAirportManagerFromTFile(AirportManager* pAirportManager);
int getFlightsFromBFile(Airline* pComp);
int saveAirportManagerToTFile(AirportManager* pAirportManager);
int saveFlightsToBFile(Airline* pComp);

int main()
{
	AirportManager	manager;
	Airline			company;

	if (getAirportManagerFromTFile(&manager) == 0)
	{
		initManager(&manager);
		initAirline(&company);
	}

	if (getFlightsFromBFile(&company) == 0)
		printf("Couldn't read from Bfile");


	int option;
	int stop = 0;
	
	do
	{
		option = menu();
		switch (option)
		{
		case eAddFlight:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			break;


		case eAddAirport:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			break;

		case ePrintCompany:
			printCompany(&company);
			break;

		case ePrintAirports:
			printAirports(&manager);
			break;

		case ePrintNumFlightsOrig:
			doCountFlightsFromName(&company);
			break;

		case ePrintFlightsPlaneCode:
			doPrintFlightsWithPlaneCode(&company);
			break;

		case ePrintFlightsPlaneType:
			doPrintFlightsWithPlaneType(&company);
			break;

		case eSortFlightsByAttribute:
		{
			Type type = findFlightAttribute();
			sort(&company,type);
			break;
		}

		case eSearchFlightsByAttribute:
		{
			Type type = findFlightAttribute();
			void* wantedFlight = getWantedFlight(type);
			search(&company,type,wantedFlight);
			break;
		}

		case EXIT:
		{
			saveFlightsToBFile(&company);
			saveAirportManagerToTFile(&manager);
			printf("Bye bye\n");
			stop = 1;
			break;
		}

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	freeManager(&manager);
	freeCompany(&company);
	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for(int i = 0 ; i < eNofOptions ; i++)
		printf("%d - %s\n",i,str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}

int saveAirportManagerToTFile(AirportManager* pAirportManager)
{
	FILE* fp;
	fp = fopen("airport_authority.txt", "w");
	if (!fp)
		return 0;
	writeAirportManagerToTextfile(fp, pAirportManager);
	fclose(fp);
	return 1;
}

int saveFlightsToBFile(Airline* pComp)
{
	FILE* fp;
	fp = fopen("airline.bin", "wb");
	if (!fp)
		return 0;
	writeAirlineToBFile(fp, pComp);
	fclose(fp);
	return 1;
}

int getAirportManagerFromTFile(AirportManager* pAirportManager)
{
	FILE* fp;
	fp = fopen("airport_authority.txt", "r");
	if (!fp)
		return 0;
	readAirportManagerFromTextfile(fp, pAirportManager);
	fclose(fp);
	return 1;
}

int getFlightsFromBFile(Airline* pComp)
{
	FILE* fp;
	fp = fopen("airline.bin", "rb");
	if (!fp)
		return 0;
	readAirlineFromBFile(fp, pComp);
	fclose(fp);
	return 1;
}
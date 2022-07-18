//#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "AirlineText.h"

int writeAirlineToTextFile(const char * fileName, Airline * pAirline)
{
	FILE* fp;
	fp = fopen(fileName, "w");
	if (!fp)
		return 0;
	fprintf(fp, "%s   %d\n", pAirline->name, pAirline->flightCount);
	for (int i = 0; i < pAirline->flightCount; i++)
	{
		writeFlightToTextFile(fp, pAirline->flightArr[i]);
	}
	return 1;
}

void writeFlightToTextFile(FILE* fp, Flight* pFlight)
{
	fprintf(fp, "%s   %s\n", pFlight->nameSource, pFlight->nameDest);
	writePlaneToTextFile(fp, &pFlight->thePlane);
	writeDateToTextFile(fp, &pFlight->date);
}

void writePlaneToTextFile(FILE* fp, Plane* pPlane)
{
	char* planeType = NULL;
	for (int i = 0; i < eNofPlaneTypes; i++)
	{
		if (pPlane->type = (ePlaneType)i)
			strcpy(planeType, PlaneTypeStr[i]);
	}
	fprintf(fp, "%s   %s\n", pPlane->code, planeType);
}

void writeDateToTextFile(FILE* fp, Date* pDate)
{
	fprintf(fp, "%d   %d  %d\n", pDate->day, pDate->month, pDate->year);
}

int readAirlineFromTextFile(const char * fileName, Airline * pAirline)
{
	FILE* fp;
	fp = fopen(fileName, "r");
	if (!fp)
		return 0;
	char temp[255];
	if (fscanf(fp, "%s %d", temp, &pAirline->flightCount) != 2)
		return 0;
	pAirline->name = _strdup(temp);
	if (!pAirline->name)
		return 0;
	for (int i = 0; i < pAirline->flightCount; i++)
	{
		if (!readFlightFromTextFile(fp, pAirline->flightArr[i]))
		{
			free(pAirline->name);
			fclose(fp);
			return 0;
		}
	}

	return 1;
}

int readFlightFromTextFile(FILE* fp, Flight* pFlight)
{
	char temp[255];
	char temp2[255];
	if (fscanf(fp, "%s %s", temp, temp2) != 2)
		return 0;
	pFlight->nameSource = _strdup(temp);
	pFlight->nameDest = _strdup(temp2);
	if (!pFlight->nameSource)
		return 0;
	if (!pFlight->nameDest)
		return 0;
	if(!readPlaneFromTextFile(fp, &pFlight->thePlane))
		return 0;
	if(!readDateFromTextFile(fp, &pFlight->date))
		return 0;
	return 1;
}

int readPlaneFromTextFile(FILE* fp, Plane* pPlane)
{
	//char temp[255];
	char temp2[255];
	if (fscanf(fp, "%s %s", pPlane->code, temp2) != 2)
		return 0;
	//*pPlane->code = _strdup(temp);
	char* planeType = _strdup(temp2);
	//if (!pPlane->code)
	//	return 0;
	if (!planeType)
		return 0;
	for (int i = 0; i < eNofPlaneTypes; i++)
	{
		if (strcmp(planeType, PlaneTypeStr[i]))
			pPlane->type = (ePlaneType)i;
	}
	return 1;
}

int readDateFromTextFile(FILE* fp, Date* pDate)
{
	if (fscanf(fp, "%d %d %d", &pDate->day, &pDate->month, &pDate->year) != 3)
		return 0;
	return 1;
}

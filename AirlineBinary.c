//#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "AirlineBinary.h"



int writeAirlineToBFile(FILE* fp, Airline* pAirline)
{
	int len = (int)strlen(pAirline->name) + 1;
	if (fwrite(&len, sizeof(int), 1, fp) != 1)
		return 0;

	if (fwrite(pAirline->name, sizeof(char), len, fp) != len)
		return 0;

	if (fwrite(&pAirline->sortType, sizeof(int), 1, fp) != 1)
		return 0;
	
	if (fwrite(&pAirline->flightCount, sizeof(int), 1, fp) != 1)
		return 0;
	
	for (int i = 0; i < pAirline->flightCount; i++)
	{
		if (writeFlightToBFile(fp, pAirline->flightArr[i]) == 0)
			return 0;

	}	
	return 1;
}

int writeFlightToBFile(FILE * fp, Flight * pFlight)
{
	int lenSource = (int)strlen(pFlight->nameSource) + 1;
	if (fwrite(&lenSource, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(pFlight->nameSource, sizeof(char), lenSource, fp) != lenSource)
		return 0;

	int lenDest = (int)strlen(pFlight->nameDest) + 1;
	if (fwrite(&lenDest, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(pFlight->nameDest, sizeof(char), lenDest, fp) != lenDest)
		return 0;

	//if(!writePlainToBFile(fp, &pFlight->thePlane))
	//	return 0;

	if ((fwrite(&pFlight->thePlane, sizeof(Plane), 1, fp) != 1)) //writes plane
		return 0;

	//if (fwrite(&pFlight->thePlane.type, sizeof(int), 1, fp) != 1)
	//	return 0;

	//if (fwrite(&pFlight->thePlane.code, sizeof(char), CODE_LENGTH + 1, fp) != CODE_LENGTH + 1)
	//	return 0;


	if(!writeDateToBFile(fp, &pFlight->date))
		return 0;
	return 1;
}

int writePlainToBFile(FILE * fp, Plane* pPlain)
{
	if (fwrite(&pPlain->type, sizeof(int), 1, fp) != 1)
		return 0;

	if (fwrite(pPlain->code, sizeof(char), CODE_LENGTH + 1, fp) != CODE_LENGTH + 1)
		return 0;
	return 1;
}

int writeDateToBFile(FILE * fp, Date* pDate)
{
	if (fwrite(&pDate->day, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(&pDate->month, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(&pDate->year, sizeof(int), 1, fp) != 1)
		return 0;
	return 1;
}

int readAirlineFromBFile(FILE* fp, Airline * pAirline)
{
	int len;
	if (fread(&len, sizeof(int), 1, fp) != 1)
		return 0;
	pAirline->name = (char*)malloc(len * sizeof(char));
	if (!pAirline->name)
		return 0;
	
	if (fread(pAirline->name, sizeof(char), len, fp) != len)
	{
		free(pAirline->name);
		return 0;
	}
	if (fread(&pAirline->sortType, sizeof(int), 1, fp) != 1)
	{
		free(pAirline->name);
		return 0;
	}
	if (fread(&pAirline->flightCount, sizeof(int), 1, fp) != 1)
	{
		free(pAirline->name);
		return 0;
	}
	pAirline->flightArr = (Flight**)malloc(pAirline->flightCount * sizeof(Flight*));
	if (!pAirline->flightArr)
	{
		free(pAirline->name);
		return 0;
	}

	L_init(&pAirline->flightDates);

	for (int i = 0; i < pAirline->flightCount; i++)
	{
		pAirline->flightArr[i] = (Flight*)malloc(sizeof(Flight));
		if (!pAirline->flightArr[i])
		{
			freeFlightArr(pAirline->flightArr, i);
			free(pAirline->name);
			return 0;
		}
		if (readFlightFromBFile(fp, pAirline->flightArr[i]) == 0)
		{
			free(pAirline->name);
			return 0;
		}
		else
			addFlightDateToList(pAirline, &pAirline->flightArr[i]->date);
	}
	return  1;
}

int readFlightFromBFile(FILE* fp, Flight* pFilght)
{
	int len;
	if (fread(&len, sizeof(int), 1, fp) != 1)
		return 0;
	pFilght->nameSource = (char*)malloc(len * sizeof(char));
	if (!pFilght->nameSource)
		return 0;
	if (fread(pFilght->nameSource, sizeof(char), len, fp) != len)
	{
		free(pFilght->nameSource);
		return 0;
	}

	if (fread(&len, sizeof(int), 1, fp) != 1)
		return 0;
	pFilght->nameDest = (char*)malloc(len * sizeof(char));
	if (!pFilght->nameDest)
	{
		free(pFilght->nameSource);
		free(pFilght);
		return 0;
	}
	if (fread(pFilght->nameDest, sizeof(char), len, fp) != len)
	{
		free(pFilght->nameSource);
		free(pFilght->nameDest);
		return 0;
	}

	if (!readPlaneFromBFile(fp, &pFilght->thePlane))
	{
		freeFlight(pFilght);
		return 0;
	}

	if(!readDateFromBFile(fp, &pFilght->date))
	{
		freeFlight(pFilght);
		return 0;
	}

	return 1;
}

int readPlaneFromBFile(FILE* fp, Plane* pPlane)
{
	if (fread(&pPlane->type, sizeof(int), 1, fp) != 1)
		return 0;

	if (fread(pPlane->code, sizeof(char), CODE_LENGTH + 1, fp) != CODE_LENGTH + 1)
		return 0;

	return 1;
}

int readDateFromBFile(FILE* fp, Date* pDate)
{
	fseek(fp, 3, SEEK_CUR);
	if (fread(&pDate->day, sizeof(int), 1, fp) != 1)
		return 0;
	if (fread(&pDate->month, sizeof(int), 1, fp) != 1)
		return 0;
	if (fread(&pDate->year, sizeof(int), 1, fp) != 1)
		return 0;

	return 1;
}

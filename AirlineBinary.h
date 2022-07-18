#pragma once
#include <stdio.h>
#include "Airline.h"
#include "Flight.h"
#include "Plane.h"
#include "Date.h"

//int writeAirlineToBFile(const char* fileName, Airline* pAirline);
int writeAirlineToBFile(FILE* fp, Airline* pAirline);
//int readAirlineFromBFile(const char* fileName, Airline* pAirline);
int readAirlineFromBFile(FILE* fp, Airline * pAirline);
int writeFlightToBFile(FILE * fp, Flight * pFlight);
int writePlainToBFile(FILE * fp, Plane* pPlain);
int writeDateToBFile(FILE * fp, Date* pDate);
int readFlightFromBFile(FILE* fp, Flight* pFilght);
int readPlaneFromBFile(FILE* fp, Plane* pPlane);
int readDateFromBFile(FILE* fp, Date* pDate);

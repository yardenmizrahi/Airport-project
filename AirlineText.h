#pragma once
#include <stdio.h>
#include "Airline.h"
#include "Flight.h"
#include "Plane.h"
#include "Date.h"

int writeAirlineToTextFile(const char* fileName, Airline* pAirline);
void writeFlightToTextFile(FILE* fp, Flight* pFlight);
void writePlaneToTextFile(FILE* fp, Plane* pPlane);
void writeDateToTextFile(FILE* fp, Date* pDate);
int readAirlineFromTextFile(const char* fileName, Airline* pAirline);
int readFlightFromTextFile(FILE* fp, Flight* pFlight);
int readPlaneFromTextFile(FILE* fp, Plane* pPlane);
int readDateFromTextFile(FILE* fp, Date* pDate);
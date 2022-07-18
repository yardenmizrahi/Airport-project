#pragma once
#include <stdio.h>
#include "AirportManager.h"
#define MAX_STR_LEN 255

int	writeAirportManagerToTextfile(FILE* file, AirportManager* pManager);
int writeAirportToTextfile(FILE* file, Airport* pPort);
int	readAirportManagerFromTextfile(FILE * file, AirportManager* pManager);
int readAirportFromTextfile(FILE* file, Airport* pPort);

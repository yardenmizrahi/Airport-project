#include <stdlib.h>
#include <string.h>

#include "AirportManagerText.h"

int	writeAirportManagerToTextfile(FILE* file, AirportManager* pManager)
{
	if (!fprintf(file, "%d\n", pManager->airportsCount))
	{
		return 0;
	}
	for (int i = 0; i < pManager->airportsCount; i++)
	{
		if (!writeAirportToTextfile(file, &pManager->airportsArr[i]))
		{
			return 0;
		}
	}
	return 1;
}

int writeAirportToTextfile(FILE* file, Airport* pPort)
{
	if (!fprintf(file, "%s\n%s\n", pPort->name, pPort->address)) return 0;
	return 1;
}

int	readAirportManagerFromTextfile(FILE * file, AirportManager* pManager)
{
	if (!fscanf(file, "%d", &pManager->airportsCount))
	{
		return 0;
	}
	pManager->airportsArr = (Airport*)malloc(sizeof(Airport)* pManager->airportsCount);
	if (!pManager->airportsArr) return 0;
	for (int i = 0; i < pManager->airportsCount; i++)
	{
		if (!readAirportFromTextfile(file, &pManager->airportsArr[i]))
		{
			return 0;
		}
	}
	return 1;
}

int readAirportFromTextfile(FILE* file, Airport* pPort)
{
	char temp[255];
	do {
		if (!fgets(temp, MAX_STR_LEN, file))return 0;
	} while (temp[0] == '\n');
	temp[strcspn(temp, "\n")] = '\0';
	pPort->name = _strdup(temp);
	do {
		if (!fgets(temp, MAX_STR_LEN, file))return 0;
	} while (temp[0] == '\n');
	temp[strcspn(temp, "\n")] = '\0';
	pPort->address = _strdup(temp);

	return 1;

}
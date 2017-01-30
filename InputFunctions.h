#include "stdbool.h"
#pragma once

typedef struct Step {
	char read,
		write,
		direction;

	int initialState,
		finalState;
}Step;

typedef struct Decode {
	char write,
		direction;

	bool isValid;
}Decode;

int* GetStates(char* line, int *nrOfStates);

Step GetStep(char *line);

int *GetTapeOut(char *tapeIn, Step *steps, int nrOfSteps, int *finalStates, int nrOfTotalStates, bool *hangs);
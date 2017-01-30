#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "InputFunctions.h"

int main()
{
	FILE *inputFile = fopen("tm.in", "r");
	char *lineBuffer = (char *)malloc(sizeof(char) * 20000);
	char *tape = (char *)malloc(sizeof(char) * 20000);

	int *initialStates,
		*finalStates;
	int i,
		nrOfTotalStates,
		nrOfFinalStates,
		initialState,
		totalStepsCount,
		stepsIndex = 0;

	bool hangs = false;

	fgets(lineBuffer, 20000, inputFile);
	initialStates = GetStates(lineBuffer, &nrOfTotalStates);

	fgets(lineBuffer, 20000, inputFile);
	finalStates = GetStates(lineBuffer, &nrOfFinalStates);

	fgets(lineBuffer, 20000, inputFile);
	initialState = atoi(++lineBuffer);

	fgets(lineBuffer, 20000, inputFile);
	totalStepsCount = atoi(lineBuffer);

	Step *steps = (Step *)malloc(sizeof(Step) * totalStepsCount);

	while (fgets(lineBuffer, 10000, inputFile))
	{
		steps[stepsIndex] = GetStep(lineBuffer);
		stepsIndex++;
	}

	fclose(inputFile);

	inputFile = fopen("tape.in", "r");
	
	fgets(tape, 20000, inputFile);
	
	for(i = strlen(tape) - 1; i < 20000; i++)
		tape[i] = '#';

	tape[19999] = '\0';

	GetTapeOut(tape, steps, totalStepsCount, finalStates, nrOfFinalStates, &hangs);

	FILE *outputFile = fopen("tape.out", "w");
	
	if(hangs)
		fprintf(outputFile, "Se agata!");
	else
		fprintf(outputFile, "%s", tape);

	fclose(outputFile);

	return 0;
}
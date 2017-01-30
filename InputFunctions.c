#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "InputFunctions.h"

Decode InitializeDecode()
{
	Decode decode;
	decode.direction = NULL;
	decode.write = NULL;
	decode.isValid = false;

	return decode;
}

Step InitializeStep()
{
	Step step;
	step.direction = NULL;
	step.read = NULL;
	step.write = NULL;
	step.finalState = 0;
	step.initialState = 0;

	return step;
}

int *GetStates(char *line, int *nrOfStates)
{
	char *p = strtok(line, " ");

	*nrOfStates = atoi(p);

	int stateNumber = 0;
	int *states = (int *)malloc(*nrOfStates * sizeof(int));

	p = strtok(NULL, " ");

	while (p != NULL)
	{
		p++;
		states[stateNumber] = atoi(p);

		stateNumber++;

		p = strtok(NULL, " ");
	}

	return states;
}

Step GetStep(char *line)
{
	char *p;
	Step step = InitializeStep();

	line++;

	p = strtok(line, " ");
	step.initialState = atoi(p);

	p = strtok(NULL, " ");
	step.read = p[0];

	p = strtok(NULL, " ");
	p++;
	step.finalState = atoi(p);

	p = strtok(NULL, " ");
	step.write = p[0];

	p = strtok(NULL, " ");
	step.direction = p[0];

	return step;
}

Decode GetDecode(int *currentState, char read, Step *steps, int nrOfSteps)
{
	Decode decode = InitializeDecode();
	int index = 0;
	bool hasDecode = false;

	while (index < nrOfSteps)
	{
		if (steps[index].initialState == *currentState && steps[index].read == read)
		{
			*currentState = steps[index].finalState;
			decode.direction = steps[index].direction;
			decode.write = steps[index].write;
			decode.isValid = true;
			break;
		}

		index++;
	}

	return decode;
}

bool IsFinalState(int currentState, int *finalStates, int nrOfTotalStates)
{
	int index;

	for (index = 0; index < nrOfTotalStates; index++)
		if (currentState == finalStates[index])
			return true;

	return false;
}

int *GetTapeOut(char *tapeIn, Step *steps, int nrOfSteps, int *finalStates, int nrOfTotalStates, bool *hangs)
{
	int currentState = 0;
	char *tapeOut = tapeIn;
	Decode decodeBuffer = InitializeDecode();

	tapeIn++;

	while (!IsFinalState(currentState, finalStates, nrOfTotalStates))
	{

		decodeBuffer = GetDecode(&currentState, tapeIn[0], steps, nrOfSteps);
		printf("currentState: %d\n", currentState);
		
		if (!decodeBuffer.isValid)
		{
			*hangs = true;
			return 0;
		}

		tapeIn[0] = decodeBuffer.write;

		switch (decodeBuffer.direction)
		{
			case 'R':
				tapeIn++;
				break;

			case 'L':
				tapeIn--;
				break;

			case 'H':
				break;
		}
	}

	tapeIn = tapeOut;
	return 0;
}
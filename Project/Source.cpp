#include "Simulator.h"
int main()
{
	Simulator S;
	while (S.CompleteHour())
	{
		// Do Nothing
	}
	S.FinishSim();
	S.CreateStatistics();
	return 0;
}
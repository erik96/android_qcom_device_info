#include <fstream>

#include "constants.h"
#include "helpers.h"
#include "functions.h"

using namespace std;

void _error()
{
	fprintf(stderr,"Invalid value, aborting...");
}


void tune(int p)
{
/*
 * 1 - CPU Temp Threshold
 * 2 - Vibration Amp
 * 3 - Fast Charge
 * 4 - TCP
 * 5 - Sound Control Parameters
 * 6 - GPU Up threshold
 * 7 - GPU Down threshold
 * 8 - Max GPU Freq
 */

	int val;

	switch (p)
	{
		case 1:
			getExtraKernelInfo(p);
			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<30 || val>150)
				return _error();
			else
				write_to_file(val, TEMP_THRESHOLD);
			getExtraKernelInfo(p);
			break;
	}
}



#include <fstream>
#include <iostream>

#include "constants.h"
#include "functions.h"
#include "classes.h"

using namespace std;

void _error(int val)
{
	fprintf(stderr,"Invalid value(%d), aborting...\n",val);
}


void tune(int p)
{
/*
 * 1 - CPU Temp Threshold
 * 2 - Vibration Amp
 * 3 - Fast Charge
 * 4 - TCP -> TODO
 * 5 - Sound Control Parameters -> TODO
 * 6 - GPU Up threshold -> TODO
 * 7 - GPU Down threshold -> TODO
 * 8 - Max GPU Freq -> TODO
 */

	int val;
	SysfsIO TUNNER;

	switch (p)
	{
		case 1:
			getExtraKernelInfo(p);
			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<30 || val>150)
				return _error(val);
			else
				 TUNNER.create_w(TEMP_THRESHOLD,val);
			getExtraKernelInfo(p);
			break;
		case 2:
			getExtraKernelInfo(p);
			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<0 || val>100)
				return _error(val);
			else
				 TUNNER.create_w(VIBRATION_AMP,val);
			getExtraKernelInfo(p);
			break;
		case 3:
			getExtraKernelInfo(p);
			fprintf(stdout,"New Value(ON:1 OFF:0):");
			fscanf(stdin,"%d",&val);

			if (val != 1 && val != 0)
				return _error(val);
			else
				 TUNNER.create_w(FORCE_FAST_CHARGE,val);
			getExtraKernelInfo(p);
			break;
		default:
			break;
	}
}



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
 * 4 - TCP
 * 5 - Sound Control Parameters -> TODO
 * 6 - GPU Up threshold
 * 7 - GPU Down threshold
 * 8 - Max GPU Freq -> FIXME
 */

	int val;
	SysfsIO TUNNER;
	string content;

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
		case 4:
			getExtraKernelInfo(p);
			fprintf(stdout,"New TCP: ");
			cin.ignore();
			getline(cin,content);

			if(TUNNER.create_w(AVAILABLE_TCP_CONGESTION_ALGORITHM,
						TCP_CONGESTION_ALGORITHM,content))
				getExtraKernelInfo(p);
			else
				return _error(-1);
			break;
			
		case 6:
			getExtraKernelInfo(p);
			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<0 || val>100)
				return _error(val);
			else
				 TUNNER.create_w(GPU_UP_THRESHOLD,val);
			getExtraKernelInfo(p);
			break;
		case 7:
			getExtraKernelInfo(p);
			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<0 || val>100)
				return _error(val);
			else
				 TUNNER.create_w(GPU_DOWN_THRESHOLD,val);
			getExtraKernelInfo(p);
			break;
		case 8: //FIXME::
			getGPUInfo(p);
			getGPUInfo(-1);
			fprintf(stdout,"New Max GPU Freq: ");
			cin.ignore();
			getline(cin,content);

			if(TUNNER.create_w(GPU_AVAILABLE_FREQ,
						GPU_MAX_FREQ,content))
				getGPUInfo(p);
			else
				return _error(-1);
			break;
			
		default:
			break;
	}
}



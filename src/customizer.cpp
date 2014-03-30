#include <fstream>
#include <iostream>
#include <vector>

#include <constants.hpp>
#include <functions.hpp>
#include <classes.hpp>
#include <helpers.hpp>

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
 * 5 - Sound Control Parameters
 * 6 - GPU Up threshold
 * 7 - GPU Down threshold
 * 8 - Max GPU Freq -> FIXME
 * 9 - Hotplug
 * 10 - Governor control -> TODO
 * 11 - CPU Freq Control
 */

	int val,nr;
	SysfsIO TUNNER;
	SysfsVector V_TUNNER;
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
		case 5:
			V_TUNNER.populate_vector(SOUND_CONTROL_PATH);
			V_TUNNER.print_vector();
			fprintf(stdout,"Choose Interface number: ");
			cin.ignore();
			fscanf(stdin,"%d",&nr);
			if(nr>V_TUNNER.vsize())
				return _error(nr);

			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<0 || val>20)
				return _error(val);
			else
				 V_TUNNER.write_vector(nr,val);
			V_TUNNER.populate_vector(SOUND_CONTROL_PATH);
			V_TUNNER.print_vector();
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

		case 9:
			V_TUNNER.populate_vector(HOTPLUG_PATH);
			V_TUNNER.print_vector();
			fprintf(stdout,"Choose Interface number: ");
			cin.ignore();
			fscanf(stdin,"%d",&nr);

			if(nr>V_TUNNER.vsize())
				return _error(nr);

			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			V_TUNNER.write_vector(nr,val);
			V_TUNNER.populate_vector(HOTPLUG_PATH);
			V_TUNNER.print_vector();
			break;

		case 11:
			getCPUInfo(p);
			V_TUNNER.populate_vector(SCALING_AVAILABLE_FREQ,NULL);
			fprintf(stdout,"1 - Min; 2 - Max: ");
			cin.ignore();
			fscanf(stdin,"%d",&nr);

			if (nr == 1)
			{
				fprintf(stdout,"Choose new MIN value:");
				V_TUNNER.print_vector(NULL);
				cin.ignore();
				fscanf(stdin,"%d",&val);
				
				if(V_TUNNER.write_vector(CURRENT_MIN_CPU_FREQ,val))
					getCPUInfo(p);
				else
					return _error(val);
			}
			else if (nr == 2)
			{
				fprintf(stdout,"Choose new MAX value:\n");
				V_TUNNER.print_vector(NULL);
				cin.ignore();
				fscanf(stdin,"%d",&val);
				
				if(V_TUNNER.write_vector(CURRENT_MAX_CPU_FREQ,val))
					getCPUInfo(p);

				else
					return _error(val);
			}
			else
				return _error(nr);

			break;
		default:
			break;
	}
}



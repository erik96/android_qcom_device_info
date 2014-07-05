#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

#include <constants.hpp>
#include <functions.hpp>
#include <classes.hpp>
#include <helpers.hpp>
#include <SuperClass.hpp>
#include <Wrapper.hpp>

using namespace std;

static void _error(int val)
{
	fprintf(stderr,"Invalid value(%d), aborting...\n",val);
}

#define _TEMP_THRESOLD		1
#define _VIBRATION_AMP	 	2
#define _FAST_CHARGE 		3
#define _TCP			4
#define _FRANCO_SOUND		5
#define _GPU_UP_THRESHOLD	6
#define _GPU_DOWN_THRESHOLD	7
#define _GPU_MAX_FREQ		8
#define _HOTPLUG		9
#define _GOVERNOR_CONTROL	10
#define _CPU_FREQ_CONTROL	11
#define _ECO_MODE		12
#define _INTELLIPLUG		13
#define _INTELLITHERMAL		14
#define _DYNAMIC_FSYNC		15

void tune(int p)
{
/*
 * 1 - CPU Temp Threshold
 * 2 - Vibration Amp
 * 3 - Fast Charge
 * 4 - TCP
 * 5 - Sound Control Parameters(Franco)
 * 6 - GPU Up threshold
 * 7 - GPU Down threshold
 * 8 - Max GPU Freq
 * 9 - Hotplug
 * 10 - Governor control
 * 11 - CPU Freq Control
 * 12 - INTELLIPLUG
 * 13 - Intellithermal
 * 14 - Dyanimc FSYNC
 * 15 - FauxSound
 */

	int val;
	string content;
	char c;

	switch (p)
	{
		case 0:
			return;

		case _TEMP_THRESOLD:
		{
			SingleBoxPreference *threshold = *heap[_TEMP_THRESOLD].second;

			fprintf(stdout, "Temp Threshold: %d\n", threshold->getValue());

			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<30 || val>150)
				return _error(val);
			else
				 threshold->write(val);

			fprintf(stdout, "Temp Threshold: %d\n", threshold->getValue());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		case _VIBRATION_AMP:
        	{
			SingleBoxPreference *sbp = *heap[_VIBRATION_AMP].second;

		    	fprintf(stdout, "Vibration Amp: %d\n", sbp->getValue());

			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<0 || val>100)
				return _error(val);
			else
				 sbp->write(val);
			fprintf(stdout, "Vibration Amp: %d\n", sbp->getValue());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
        	}
		case _FAST_CHARGE:
        	{
			SingleBoxPreference *fastCharge = *heap[_FAST_CHARGE].second;

			fprintf(stdout,"Fast Charge is %s, switch ?(Y/N)\n", fastCharge->stat().c_str());
			cin.ignore();
			cin>>c;

			if(c == 'y' || c == 'Y')
				 fastCharge->mSwitch();

            		fprintf(stdout,"Fast Charge is %s\n", fastCharge->stat().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
        	}

		case _TCP:
		{
			ListPreference *tcp = *heap[_TCP].second;
			unsigned int position;

			fprintf(stdout,"\nCurrent TCP Congestion Algorithm: %s\n", 
									tcp->status().c_str());
			
			fprintf(stdout, "Choose the new one:\n");
			tcp->mOutput();
			fscanf(stdin,"%u",&position);

			if (!tcp->has(position))
				return _error(position);

			tcp->mChange(position);

			fprintf(stdout,"Current TCP Congestion Algorithm: %s\n", 
									tcp->status().c_str());
			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}
		case _FRANCO_SOUND:
		{
			ListPreference *francoSound = *heap[_FRANCO_SOUND].second;
			unsigned int position;
			fprintf(stdout,"\n");
			francoSound->mOutput();

			fprintf(stdout,"\nInterface number: ");
			fscanf(stdin,"%u",&position);

			if (!francoSound->has(position))
				return _error(position);

			fprintf(stdout,"New Value: ");
			fscanf(stdin,"%d",&val);


			if (val<0 || val>20)
				return _error(val);
			else
				francoSound->mChangeByValue(position,val);

			fprintf(stdout,"Values applied successfully\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}
		case _GPU_UP_THRESHOLD:
        	{
            		SingleBoxPreference *gpuUp = *heap[_GPU_UP_THRESHOLD].second;

            		fprintf(stdout, "GPU Up Threshold: %d\n", gpuUp->getValue());

			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<0 || val>100)
				return _error(val);
			else
				 gpuUp->write(val);
			fprintf(stdout, "GPU Up Threshold: %d\n", gpuUp->getValue());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
        	}
		case _GPU_DOWN_THRESHOLD:
        	{
            		SingleBoxPreference *gpuDown = *heap[_GPU_DOWN_THRESHOLD].second;

            		fprintf(stdout, "GPU Down Threshold: %d\n", gpuDown->getValue());

			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<0 || val>100)
				return _error(val);
			else
				 gpuDown->write(val);
			fprintf(stdout, "GPU Down Threshold: %d\n", gpuDown->getValue());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
        	}

		case _GPU_MAX_FREQ:
		{
			ListPreference *gpuOC = *heap[_GPU_MAX_FREQ].second;
			unsigned int position;
			fprintf(stdout,"Current Max GPU Freq: %s\n",gpuOC->status().c_str());

			fprintf(stdout,"Choose new MAX GPU Freq value:\n");
			gpuOC->mOutput();
			
			cin.ignore();
			fscanf(stdin,"%u",&position);

			if(gpuOC->has(position))
				gpuOC->mChange(position);
			else
				return _error(position);

			fprintf(stdout,"Current Max GPU Freq: %s\n",gpuOC->status().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		case _HOTPLUG:
		{
			ListPreference *hotplug = *heap[_HOTPLUG].second;
			unsigned int position;

			hotplug->mOutput();
			
			fprintf(stdout,"\nChoose Interface number: ");
			cin.ignore();
			fscanf(stdin,"%d",&position);

			if(!hotplug->has(position))
				return _error(position);

			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);
			
			hotplug->mChangeByValue(position,val);

			fprintf(stdout,"Values applied successfully\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		case _GOVERNOR_CONTROL:
		{
			ListPreference *cpuGov = *heap[_GOVERNOR_CONTROL].second;
			unsigned int position;
			fprintf(stdout,"Current CPU Governor: %s\n",cpuGov->status().c_str());

			cpuGov->mOutput();

			fprintf(stdout,"Choose new governor number: ");
			cin.ignore();
			fscanf(stdin,"%d",&position);

			if(cpuGov->has(position))
					cpuGov->mChange(position);
			else
				return _error(position);

			fprintf(stdout,"Current CPU Governor: %s\n",cpuGov->status().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		/*case _CPU_FREQ_CONTROL:
		{
			unsigned int position;

			fprintf(stdout,"1 - Min\n2 - Max\nValue: ");
			cin.ignore();
			fscanf(stdin,"%d",&nr);

			if (nr == 1)
			{
				ListPreference changeMin(SCALING_AVAILABLE_FREQ,
								CURRENT_MIN_CPU_FREQ);

				fprintf(stdout,"CPU MIN Freq:%s\n",changeMin.status().c_str());

				fprintf(stdout,"Choose new MIN value:\n");
				changeMin.mOutput();

				cin.ignore();
				fscanf(stdin,"%d",&position);

				if(changeMin.has(position))
					changeMin.mChange(position);
				else
					return _error(position);

				fprintf(stdout,"CPU MIN Freq:%s\n",changeMin.status().c_str());
			}
			else if (nr == 2)
			{
				ListPreference changeMax(SCALING_AVAILABLE_FREQ,
								CURRENT_MAX_CPU_FREQ);

				fprintf(stdout,"CPU MAX Freq:%s\n",changeMax.status().c_str());

				fprintf(stdout,"Choose new MAX value:\n");
				changeMax.mOutput();

				cin.ignore();
				fscanf(stdin,"%d",&position);

				if(changeMax.has(position))
					changeMax.mChange(position);
				else
					return _error(position);

				fprintf(stdout,"CPU MAX Freq:%s\n",changeMax.status().c_str());
			}
			else
				return _error(nr);

			fprintf(stdout,"\nValues applied successfully\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}*/

		case _INTELLIPLUG:
		{
			SingleBoxPreference *intelliPlug = *heap[_INTELLIPLUG].second;
			fprintf(stdout,"Intelliplug is %s, switch?(y/n): ",
						intelliPlug->stat().c_str());

			cin.ignore();
			fscanf(stdin," %c",&c);

			if(c == 'y' || c == 'Y')
				intelliPlug->mSwitch();

			fprintf(stdout,"Intelliplug is %s\n",
						intelliPlug->stat().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		case _INTELLITHERMAL:
		{
			SingleBoxPreference *intelliThermal = *heap[_INTELLITHERMAL].second;
			fprintf(stdout,"Intellithermal is %s, switch?(y/n): ",
						intelliThermal->stat().c_str());

			cin.ignore();
			fscanf(stdin," %c",&c);

			if(c == 'y' || c == 'Y')
				intelliThermal->mSwitch();

			fprintf(stdout,"Intellithermal is %s\n", intelliThermal->stat().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		case _DYNAMIC_FSYNC:
		{
			SingleBoxPreference *dynamicFsync = *heap[_DYNAMIC_FSYNC].second;
			fprintf(stdout,"Dynamic Fsync is %s, switch?(y/n): ",dynamicFsync->stat().c_str());

			cin.ignore();
			fscanf(stdin," %c",&c);

			if(c == 'y' || c == 'Y')
				dynamicFsync->mSwitch();

			fprintf(stdout,"Dynamic Fsync is %s\n", dynamicFsync->stat().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}


		/*case 16:
		{
			ListPreference fauxSound(FAUX_SOUND);
			unsigned int position;

			fprintf(stdout,"\n");
			fauxSound.mOutput();

			fprintf(stdout,"\nInterface number: ");
			fscanf(stdin,"%u",&position);

			if (!fauxSound.has(position))
				return _error(position);

			fprintf(stdout,"New Value: ");
			fscanf(stdin,"%d",&val);
	
			fauxSound.mChangeByValue(position,val);

			fprintf(stdout,"Values applied successfully\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		} */


		default:
			break;
	}
}

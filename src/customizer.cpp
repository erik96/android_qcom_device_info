#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

#include <constants.hpp>
#include <functions.hpp>
#include <classes.hpp>
#include <helpers.hpp>
#include <SuperClass.hpp>

using namespace std;

static void _error(int val)
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
 * 5 - Sound Control Parameters(Franco)
 * 6 - GPU Up threshold
 * 7 - GPU Down threshold
 * 8 - Max GPU Freq
 * 9 - Hotplug
 * 10 - Governor control
 * 11 - CPU Freq Control
 * 12 - Eco Mode
 * 13 - INTELLIPLUG
 * 14 - Intellithermal
 * 15 - Dyanimc FSYNC
 * 16 - FauxSound
 */

	int val;
	unsigned int nr;
	string content;
	char c;

	switch (p)
	{
		case 0:
			return;

		case 1:
		{
			SingleBoxPreference threshold(TEMP_THRESHOLD);

			fprintf(stdout, "Temp Threshold: %d\n", threshold.getValue());

			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<30 || val>150)
				return _error(val);
			else
				 threshold.write(val);

			fprintf(stdout, "Temp Threshold: %d\n", threshold.getValue());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		case 2:
        	{
		    	SingleBoxPreference vibrator(VIBRATION_AMP);

		    	fprintf(stdout, "Vibration Amp: %d\n", vibrator.getValue());

			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<0 || val>100)
				return _error(val);
			else
				 vibrator.write(val);
			fprintf(stdout, "Vibration Amp: %d\n", vibrator.getValue());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
        	}
		case 3:
        	{
			SingleBoxPreference fastCharge(FORCE_FAST_CHARGE,true);

			fprintf(stdout,"Fast Charge is %s, switch ?(Y/N)\n", fastCharge.stat().c_str());
			cin.ignore();
			cin>>c;

			if(c == 'y' || c == 'Y')
				 fastCharge.mSwitch();

            		fprintf(stdout,"Fast Charge is %s\n", fastCharge.stat().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
        	}

		case 4:
		{
			ListPreference tcp(AVAILABLE_TCP_CONGESTION_ALGORITHM,
						TCP_CONGESTION_ALGORITHM);
			unsigned int position;

			fprintf(stdout,"\nCurrent TCP Congestion Algorithm: %s\n", 
									tcp.status().c_str());
			
			fprintf(stdout, "Choose the new one:\n");
			tcp.mOutput();
			fscanf(stdin,"%u",&position);

			if (!tcp.has(position))
				return _error(position);

			tcp.mChange(position);

			fprintf(stdout,"Current TCP Congestion Algorithm: %s\n", 
									tcp.status().c_str());
			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}
		case 5:
		{
			ListPreference francoSound(SOUND_CONTROL_PATH);
			unsigned int position;
			fprintf(stdout,"\n");
			francoSound.mOutput();

			fprintf(stdout,"\nInterface number: ");
			fscanf(stdin,"%u",&position);

			if (!francoSound.has(position))
				return _error(position);

			fprintf(stdout,"New Value: ");
			fscanf(stdin,"%d",&val);


			if (val<0 || val>20)
				return _error(val);
			else
				francoSound.mChangeByValue(position,val);

			fprintf(stdout,"Values applied successfully\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}
		case 6:
        	{
            		SingleBoxPreference gpuUp(GPU_UP_THRESHOLD);

            		fprintf(stdout, "GPU Up Threshold: %d\n", gpuUp.getValue());

			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<0 || val>100)
				return _error(val);
			else
				 gpuUp.write(val);
			fprintf(stdout, "GPU Up Threshold: %d\n", gpuUp.getValue());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
        	}
		case 7:
        	{
            		SingleBoxPreference gpuDown(GPU_DOWN_THRESHOLD);

            		fprintf(stdout, "GPU Down Threshold: %d\n", gpuDown.getValue());

			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<0 || val>100)
				return _error(val);
			else
				 gpuDown.write(val);
			fprintf(stdout, "GPU Down Threshold: %d\n", gpuDown.getValue());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
        	}

		case 8:
		{
			unsigned int position;
			ListPreference gpuOC(GPU_AVAILABLE_FREQ,GPU_MAX_FREQ);
			fprintf(stdout,"Current Max GPU Freq: %s\n",gpuOC.status().c_str());

			fprintf(stdout,"Choose new MAX GPU Freq value:\n");
			gpuOC.mOutput();
			
			cin.ignore();
			fscanf(stdin,"%u",&position);

			if(gpuOC.has(position))
				gpuOC.mChange(position);
			else
				return _error(position);

			fprintf(stdout,"Current Max GPU Freq: %s\n",gpuOC.status().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		case 9:
		{
			unsigned int position;
			ListPreference hotplug(HOTPLUG_PATH);

			hotplug.mOutput();
			
			fprintf(stdout,"\nChoose Interface number: ");
			cin.ignore();
			fscanf(stdin,"%d",&position);

			if(!hotplug.has(position))
				return _error(position);

			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);
			
			hotplug.mChangeByValue(position,val);

			fprintf(stdout,"Values applied successfully\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		case 10:
		{
			unsigned int position;
			ListPreference cpuGov(SCALING_AVAILABLE_GOVS,CURRENT_CPU_GOV);
			fprintf(stdout,"Current CPU Governor: %s\n",cpuGov.status().c_str());

			cpuGov.mOutput();

			fprintf(stdout,"Choose new governor number: ");
			cin.ignore();
			fscanf(stdin,"%d",&position);

			if(cpuGov.has(position))
					cpuGov.mChange(position);
			else
				return _error(position);

			fprintf(stdout,"Current CPU Governor: %s\n",cpuGov.status().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		case 11:
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
		}

		case 12:
		{
			SingleBoxPreference ecoMode(ECO_MODE,true);
			fprintf(stdout,"Eco Mode is %s, switch?(y/n): ",
						ecoMode.stat().c_str());

			cin.ignore();
			fscanf(stdin," %c",&c);

			if(c == 'y' || c == 'Y')
				ecoMode.mSwitch();

			fprintf(stdout,"Eco Mode is %s\n",
						ecoMode.stat().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		case 13:
		{
			SingleBoxPreference intelliPlug(INTELLIPLUG,true);
			fprintf(stdout,"Intelliplug is %s, switch?(y/n): ",
						intelliPlug.stat().c_str());

			cin.ignore();
			fscanf(stdin," %c",&c);

			if(c == 'y' || c == 'Y')
				intelliPlug.mSwitch();

			fprintf(stdout,"Intelliplug is %s\n",
						intelliPlug.stat().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		case 14:
		{
			SingleBoxPreference intelliThermal(INTELLITHERMAL);
			fprintf(stdout,"Intellithermal is %s, switch?(y/n): ",
						intelliThermal.stat().c_str());

			cin.ignore();
			fscanf(stdin," %c",&c);

			if(c == 'y' || c == 'Y')
				intelliThermal.mSwitch();

			fprintf(stdout,"Intellithermal is %s\n", intelliThermal.stat().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		case 15:
		{
			SingleBoxPreference dynamicFsync(DYN_FSYNC);
			fprintf(stdout,"Dynamic Fsync is %s, switch?(y/n): ",dynamicFsync.stat().c_str());

			cin.ignore();
			fscanf(stdin," %c",&c);

			if(c == 'y' || c == 'Y')
				dynamicFsync.mSwitch();

			fprintf(stdout,"Dynamic Fsync is %s\n", dynamicFsync.stat().c_str());

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

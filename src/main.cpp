#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <map>

#include <functions.hpp>
#include <helpers.hpp>
#include <constants.hpp>

#define VERSION "0.9.84_beta"
#define CH_LIMIT 16

using namespace std;

map <int,string> smap; 

unsigned short ch;
string s;

static void menu(void);
static void AdvancedMenu(void);
static void SysfsTunner(void);
static void ShowMenu(void);
static void ShowAdvancedMenu(void);

static void clear(void);

static void _init_map();
static void show_map();


int main()
{
	_init_map();
	ShowMenu();
	menu();

	clear();
	return 0;
}


static void clear()
{
	remove("/data/local/data.txt");
	remove("/data/local/tmp.sh");
}

static void ShowMenu()
{
	if (IsNexus5())
		fprintf(stdout,"You are running Nexus 5\n");

	fprintf(stdout, "Qualcomm Device Info v%s by educk@XDA-Dev.com\n",VERSION);
	fprintf(stdout, "Options:\n"
			"1: Get ROM Information\n" 
			"2: Get CPU Information\n"
			"3: Get Battery Information\n"
			"4: Get Voltage Table\n"
			"5: Get Linux Kernel Informations\n"
			"6: Dump logcat and last_kmsg (store them to /sdcard/logs/)\n"
			"7: Get VM Stats\n"
			"8: Get RAM Informations\n"
			"9: Get Disk Informations\n");
	if(IsNexus5())
		fprintf(stdout,"10: Nexus 5 Extras[WIP]\n");

		fprintf(stdout,"11: Time in state\n");

	fprintf(stdout,"0: Quit\n");
	return;
}

static void ShowAdvancedMenu()
{
	fprintf(stdout,"\nAdvanced Options:\n");
		if(Has(HOTPLUG_PATH))
			fprintf(stdout,"1: Get HotPlug Info\n");
		fprintf(stdout,"2: Get GPU Info\n"
			"3: Get Extra Kernel Info\n"
			"4: Sysfs Tunner\n"
			"0: Back\n");
}

static void menu()
{
	do
	{
		fscanf(stdin,"%hu",&ch);

		switch (ch)
		{
			case 0:
				fprintf(stdout, "Bye-Bye !\n");
				break;
			case 1:
				getProperty("ro.build.version.release",1);
				getProperty("ro.build.date",2);
				getProperty("ro.build.user",3);

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 2:
				getCPUInfo(0);

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 3:
				getBatteryInfo();

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 4:
				getVddLevels();
				
				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 5:
				getKernelInfo();

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 6:
				getLogs();

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 7:
				getVMStats();

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 8:
				getRAMInfo();

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 9:
    				getDiskInfo();

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 10:
				if(!IsNexus5())
					goto error;

				ShowAdvancedMenu();
				AdvancedMenu();
				break;
			case 11:

				ShowTimeInState();

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;

			default:
			error:
				fprintf(stderr, "Unknown value\n");
				break;
		}
	}

	while (ch != 0);
}

static void AdvancedMenu()
{
	do
	{
		fscanf(stdin,"%hu",&ch);

		switch(ch)
		{
			case 0:
				break;
			case 1:
				if(!Has(HOTPLUG_PATH))
					goto error;

				getHotPlugInfo();
				
				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowAdvancedMenu();
				break;
			case 2:
				getGPUInfo(0);

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowAdvancedMenu();
				break;
			case 3:
				getExtraKernelInfo(0);

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowAdvancedMenu();
				break;
			case 4:
				return SysfsTunner();

			default:
			error:
				fprintf(stderr, "Unknown value\n");
				break;
		}

	}
	while(ch != 0);

	ShowMenu();
	return menu();
}

static void SysfsTunner()
{
	do
	{
		show_map();
		fprintf(stdout, "Value: ");
		fscanf(stdin,"%hu",&ch);

		if ((ch == 0 || smap.count(ch))  && ch<=CH_LIMIT)
			tune(ch);
		else
		{
			fprintf(stderr, "Unknown value, aborting...\n");
			usleep(350000);
		}
		
	}
	while (ch != 0);

	ShowAdvancedMenu();
	return AdvancedMenu();
}

static void _init_map()
{
	if(Has(TEMP_THRESHOLD,NULL))
		smap.insert(make_pair(1,"CPU Temp Threshold"));
	
	if(Has(VIBRATION_AMP,NULL))
		smap.insert(make_pair(2,"Vibration Amp"));

	if(Has(FORCE_FAST_CHARGE,NULL))
		smap.insert(make_pair(3,"Fast Charge"));

	if(Has(TCP_CONGESTION_ALGORITHM,NULL))
		smap.insert(make_pair(4,"TCP"));

	if(Has(SOUND_CONTROL_PATH))
		smap.insert(make_pair(5,"Sound Control Parameters(Franco Sound)"));

	if(Has(GPU_UP_THRESHOLD,NULL))
		smap.insert(make_pair(6,"GPU Up threshold"));

	if(Has(GPU_DOWN_THRESHOLD,NULL))
		smap.insert(make_pair(7,"GPU Down threshold"));

	if(Has(GPU_MAX_FREQ,NULL))
		smap.insert(make_pair(8,"Max GPU Freq"));

	if(Has(HOTPLUG_PATH))
		smap.insert(make_pair(9,"Hotplug"));

	if(Has(CURRENT_CPU_GOV,NULL))
		smap.insert(make_pair(10,"Governor Control"));

	if(Has(CURRENT_MAX_CPU_FREQ,NULL))
		smap.insert(make_pair(11,"CPU Freq Control"));

	if(Has(ECO_MODE,NULL))
		smap.insert(make_pair(12,"Eco Mode"));

	if(Has(INTELLIPLUG,NULL))
		smap.insert(make_pair(13,"INTELLIPLUG"));

	if(Has(INTELLITHERMAL,NULL))
		smap.insert(make_pair(14,"Intellithermal"));

	if(Has(DYN_FSYNC,NULL))
		smap.insert(make_pair(15,"Dynamic Fsync"));
	
	//if(Has(FAUX_SOUND))
		//smap.insert(make_pair(16,"Faux Sound"));

}

static void show_map()
{
	map <int,string>::iterator it;

	cout<<'\n';

	for(it = smap.begin(); it!=smap.end(); ++it)
		cout<<(*it).first<<" - "<<(*it).second<<'\n';

	cout<<"0 - Back\n";
}

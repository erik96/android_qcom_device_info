#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "functions.h"
#include "helpers.h"

using namespace std;

const char ver[] = "0.7.5_beta";
unsigned short ch;

static void menu(void);
static void AdvancedMenu(void);

static void clear()
{
	remove("/data/local/data.txt");
	remove("/data/local/tmp.sh");
}

int main ()
{

	menu();

	clear();
	return 0;


}

static void menu()
{
	if (IsNexus5())
		fprintf(stdout,"You are running Nexus 5\n");

	fprintf(stdout, "Qualcomm Device Info v%s by educk@XDA-Dev.com\n",ver);
	fprintf(stdout, "Options:\n"
			"1: Get ROM Information\n" 
			"2: Get CPU Information\n"
			"3: Get Battery Information\n"
			"4: Get Voltage Table\n"
			"5: Get Linux Kernel Informations\n"
			"6: Dump logcat and last_kmsg (store them to /sdcard/logs/)\n"
			"7: Get VM Stats\n"
			"8: Get RAM Informations\n"
			"9: Get Disk Informations\n"
			"10: Advanced Menu\n"
			"0: Quit\n");

	do
	{
		cin>>ch;

		switch (ch)
		{
			case 0:
				fprintf(stdout, "Bye-Bye !\n");
				break;
			case 1:
				getProperty("ro.build.version.release",1);
				getProperty("ro.build.date",2);
				getProperty("ro.build.user",3);
				break;
			case 2:
				getCPUInfo();
				break;
			case 3:
				getBatteryInfo();
				break;
			case 4:
				getVddLevels();
				break;
			case 5:
				getKernelInfo();
				break;
			case 6:
				getLogs();
				break;
			case 7:
				getVMStats();
				break;
			case 8:
				getRAMInfo();
				break;

			case 9:
    				getDiskInfo();
				break;
			case 10:
				AdvancedMenu();
				break;
			default: 
				fprintf(stderr, "Unknown value\n");
				break;
		}
	}

	while (ch != 0);
}

static void AdvancedMenu()
{
	fprintf(stdout,"Advanced Options:\n");

	do
	{
		cin>>ch;

		switch(ch)
		{
			case 0:
				break;
			default:
				fprintf(stderr, "Unknown value\n");
				break;
		}

	}
	while(ch != 0);


	return menu();
}

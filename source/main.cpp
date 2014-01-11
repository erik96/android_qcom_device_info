#include "functions.h"
#include <cstdio>
#include <cstdlib>

using namespace std;

const char ver[] = "0.5_pre-alpha";

void menu(void);

int main ()
{

	int ch;
	menu();

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
			default: 
				fprintf(stdout, "Unknown value");
				break;
		}
	}

	while (ch != 0);

	return 0;


}

void menu()
{

	fprintf(stdout, "Ariesve Device Info v%s by educk@XDA-Dev.com\n",ver);
	fprintf(stdout, "Options:\n"
			"1: Get ROM Information\n" 
			"2: Get CPU Information\n"
			"3: Get Battery Information\n"
			"4: Get Voltage Table\n"
			"5: Get Linux Kernel Informations\n"
			"6: Dump logcat and last_kmsg\n"
			"0: Quit\n");
}

#include "functions.h"
#include <cstdio>

using namespace std;

const char ver[] = "0.1";

void menu(void);

int main ()
{

	int ch;

	menu();
	cin>>ch;

	switch (ch)
	{
		case 1:
		{
			getProperty("ro.build.version.release",1);
			getProperty("ro.build.date",2);
			getProperty("ro.build.user",3);
			break;
		}
		case 2:
		{
			getCPUInfo();
			break;
		}
		default: break;
	}

	return 0;


}

void menu()
{

	fprintf(stdout, "Ariesve Device Info v%s by educk@XDA-Dev.com\n",ver);
	fprintf(stdout, "Options:\n"
			"1: Get ROM Information\n" 
			"2: Get CPU Information\n");
}

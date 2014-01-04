#include "functions.h"

using namespace std;

void getProperty(string line1, int s)
{
	string line;
	bool found = false;
	int len;

	ifstream fp;
	fp.open("/system/build.prop");

	if (!fp)
	{
		fprintf(stderr,"%s\n","Unable to open input file");
		return;
	}


	size_t pos;
	while (fp.good())
	{
		getline(fp,line);
		pos = line.find(line1);

		if(pos!=string::npos)
        	{

			switch (s)
			{
				case 1:
				{
					line = line.substr(25,5);
            				fprintf(stdout,"%s %s \n", "Android Version:",line.c_str());
					found = true;
            				break;
				}
				case 2:
				{
					len = line.length();
					line = line.substr(14,len-14);
					fprintf(stdout,"%s %s \n", "Build Date:",line.c_str());
					found = true;
					break;
				}
				case 3:
				{
					len = line.length();
					line = line.substr(14,len-14);
					fprintf(stdout,"%s %s \n", "Developer:",line.c_str());
					found = true;
				}
				default: break;
        		}
			break;
		}
 	 }

}


void getCPUInfo()
{
	ifstream fp;
	string Printer;

	fp.open("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq");
	getline(fp,Printer);
	fprintf(stdout,"%s %s \n","Current CPU Freq:",Printer.c_str());
	fp.close();

	fp.open("/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq");
	getline(fp,Printer);
	fprintf(stdout,"%s %s \n","Current Max CPU Freq:",Printer.c_str());
	fp.close();

	fp.open("/sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq");
	getline(fp,Printer);
	fprintf(stdout,"%s %s \n","Current Min CPU Freq:",Printer.c_str());
	fp.close();	
	
	fp.open("/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor");
	getline(fp,Printer);
	fprintf(stdout,"%s %s \n","Current CPU Governor:",Printer.c_str());
	fp.close();
}



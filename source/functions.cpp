#include "functions.h"
#include <cstdlib>

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
            				fprintf(stdout,"Android Version: %s",line.c_str());
					found = true;
            				break;
				}
				case 2:
				{
					len = line.length();
					line = line.substr(14,len-14);
					fprintf(stdout,"Build Date: %s",line.c_str());
					found = true;
					break;
				}
				case 3:
				{
					len = line.length();
					line = line.substr(14,len-14);
					fprintf(stdout,"Developer: %s",line.c_str());
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

	ifstream in("/proc/cpuinfo");
	string buff((istreambuf_iterator<char>(in)), 
    	istreambuf_iterator<char>());
	fprintf(stdout,"CPU Informations: \n%s",buff.c_str());

	fp.open("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq");
	getline(fp,Printer);
	fprintf(stdout,"\n","Current CPU Freq: %s\n",Printer.c_str());
	fp.close();

	fp.open("/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq");
	getline(fp,Printer);
	fprintf(stdout,"Current Max CPU Freq: %s\n",Printer.c_str());
	fp.close();

	fp.open("/sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq");
	getline(fp,Printer);
	fprintf(stdout,"Current Min CPU Freq: %s\n",Printer.c_str());
	fp.close();	
	
	fp.open("/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor");
	getline(fp,Printer);
	fprintf(stdout,"Current CPU Governor: %s\n",Printer.c_str());
	fp.close();
}



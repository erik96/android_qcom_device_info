#include "functions.h"
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>

using namespace std;

void getProperty(string line1, int s)
{
	string line;
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
					line = line.substr(25,5);
            				fprintf(stdout,"Android Version: %s\n",line.c_str());
            				break;
				case 2:
					len = line.length();
					line = line.substr(14,len-14);
					fprintf(stdout,"Build Date: %s\n",line.c_str());
					break;
				case 3:
					len = line.length();
					line = line.substr(14,len-14);
					fprintf(stdout,"Developer: %s\n",line.c_str());
					break;

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

void getVddLevels()
{

	ifstream in("sys/devices/system/cpu/cpu0/cpufreq/vdd_levels");
	if (!in)
	{
		fprintf(stderr,"Your kernel doesn't support VDD Sysfs interface\n");
		return;
	}

	string buff((istreambuf_iterator<char>(in)), 
    	istreambuf_iterator<char>());
	fprintf(stdout,"Voltage Table: \n%s",buff.c_str());
}
	

void getBatteryInfo()
{

	ifstream fp;
	string Printer;

	fp.open("/sys/class/power_supply/battery/status");
	getline(fp,Printer);
	fprintf(stdout,"Battery Status: %s\n",Printer.c_str());
	fp.close();

	fp.open("/sys/class/power_supply/battery/technology");
	getline(fp,Printer);
	fprintf(stdout,"Battery Technology: %s\n",Printer.c_str());
	fp.close();

	fp.open("/sys/class/power_supply/battery/capacity");
	getline(fp,Printer);
	fprintf(stdout,"Battery Level: %s\n",Printer.c_str());
	fp.close();

	fp.open("/sys/class/power_supply/battery/voltage_now");
	getline(fp,Printer);
	fprintf(stdout,"Current battery voltage: %s\n",Printer.c_str());
	fp.close();

	fp.open("/sys/class/power_supply/battery/voltage_max_design");
	getline(fp,Printer);
	fprintf(stdout,"Design Maximal Voltage: %s\n",Printer.c_str());
	fp.close();

	fp.open("/sys/class/power_supply/battery/voltage_min_design");
	getline(fp,Printer);
	fprintf(stdout,"Design Minimal Voltage: %s\n",Printer.c_str());
	fp.close();

	fp.open("/sys/class/power_supply/battery/health");
	getline(fp,Printer);
	fprintf(stdout,"Battery Health: %s\n",Printer.c_str());
	fp.close();

	fp.open("/sys/class/power_supply/battery/batt_temp");
	getline(fp,Printer);
	fprintf(stdout,"Battery Temperature: %s\n",Printer.c_str());
	fp.close();

}

void getKernelInfo()
{

	ifstream in("/proc/version");
	string buff((istreambuf_iterator<char>(in)), 
    	istreambuf_iterator<char>());
	fprintf(stdout,"Linux Kernel Informations: \n%s",buff.c_str());

	in.close();
	
}

static void cpy (const char *infile, const char *outfile)
{
	ifstream  src(infile, ios::binary);

	if (src)
	{
		ofstream  dst(outfile,   ios::binary);
		dst << src.rdbuf();
		dst.close();
		src.close();
		return;
	}
	else
	{
		fprintf(stderr, "%s not found\n", infile);
		src.close();
		return;
	}
}

void getLogs()
{

	int result_code = mkdir("/sdcard/logs", 0770);
	cpy("/proc/last_kmsg", "/sdcard/logs/last_kmsg");
	
	pid_t pid = fork();
  	if (pid == 0) 
	{
    		execl("/system/bin/logcat", "logcat", "-v", "threadtime", "-d", "-t", "1000", "-f", "/sdcard/logs/log.txt", NULL);
   		_exit(EXIT_FAILURE);
  	}

	fprintf(stdout, "DONE !\n");
}

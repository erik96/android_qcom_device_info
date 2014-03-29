#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>

#include <functions.hpp>
#include <helpers.hpp>
#include <constants.hpp>
#include <classes.hpp>

using namespace std;

void getProperty(string line1, unsigned short s)
{
	string line;
	unsigned short len;

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

	fp.close();
}

void getCPUInfo()
{
	SysfsIO CPU;
	
	fprintf(stdout,"CPU Informations: \n%s", CPU.create_rbuff(CPU_INFO).c_str());
	
	fprintf(stdout,"\nCurrent CPU Freq: %s\n", CPU.create_rline(CURRENT_CPU_FREQ).c_str());

	fprintf(stdout,"Current Max CPU Freq: %s\n", CPU.create_rline(CURRENT_MAX_CPU_FREQ).c_str());

	fprintf(stdout,"Current Min CPU Freq: %s\n", CPU.create_rline(CURRENT_MIN_CPU_FREQ).c_str());	
	
	fprintf(stdout,"Current CPU Governor: %s\n", CPU.create_rline(CURRENT_CPU_GOV).c_str());

        fprintf(stdout,"Scaling available frequencies: %s\n", CPU.create_rline(SCALING_AVAILABLE_FREQ).c_str());

        fprintf(stdout,"Scaling available governors: %s\n", CPU.create_rline(SCALING_AVAILABLE_GOVS).c_str());

}

bool getVddLevels()
{
	ifstream in;
	if (IsNexus5())
		in.open("sys/devices/system/cpu/cpu0/cpufreq/UV_mV_table");
	if (IsNexus5() && !FileExists("sys/devices/system/cpu/cpu0/cpufreq/UV_mV_table"))
		in.open("/sys/devices/system/cpu/cpufreq/vdd_table/vdd_levels");
	if (!IsNexus5())
		in.open("sys/devices/system/cpu/cpu0/cpufreq/vdd_levels");
	if (!in)
	{
		fprintf(stderr,"Your kernel doesn't support VDD Sysfs interface\n");
		return false;
	}

	string buff((istreambuf_iterator<char>(in)), 
    	istreambuf_iterator<char>());
	in.close();
	fprintf(stdout,"Voltage Table: \n%s",buff.c_str());

	return true;
}
	

void getBatteryInfo()
{
	SysfsIO BATT;

	fprintf(stdout,"Battery Status: %s\n",BATT.create_rline(BATTERY_STATUS).c_str());

	fprintf(stdout,"Battery Technology: %s\n",BATT.create_rline(BATTERY_TECHNOLOGY).c_str());

	fprintf(stdout,"Battery Level: %s\n",BATT.create_rline(BATTERY_CAPACITY).c_str());

	fprintf(stdout,"Current battery voltage: %s\n",BATT.create_rline(BATTERY_VOLTAGE).c_str());

	fprintf(stdout,"Design Maximal Voltage: %s\n",BATT.create_rline(BATTERY_DESING_MAX_VOLTAGE).c_str());

	fprintf(stdout,"Design Minimal Voltage: %s\n",BATT.create_rline(BATTERY_DESING_MIN_VOLTAGE).c_str());

	fprintf(stdout,"Battery Health: %s\n",BATT.create_rline(BATTERY_HEALTH).c_str());

	if (IsNexus5())
		fprintf(stdout,"Battery Temperature: %s\n",BATT.create_rline(BATTERY_TEMP).c_str());
	else
		fprintf(stdout,"Battery Temperature: %s\n",BATT.create_rline(BATTERY_TEMP_OLD).c_str());

}

void getKernelInfo()
{
	fprintf(stdout,"Linux Kernel Informations: \n%s",BuffFile("/proc/version").c_str());
}

void getLogs()
{
	//int result code = mkdir("/sdcard/logs", 0770);
	mkdir("/sdcard/logs", 0770);
	cpy("/proc/last_kmsg", "/sdcard/logs/last_kmsg");
	
	pid_t pid = fork();
  	if (pid == 0) 
	{
    		execl("/system/bin/logcat", "logcat", "-v", "threadtime", "-d", "-t", "1000", "-f", "/sdcard/logs/log.txt", NULL);
   		_exit(EXIT_FAILURE);
  	}

	fprintf(stdout, "Logs saved to /sdcard/logs !\n");
}

void getVMStats()
{
	PrintDirContent("/proc/sys/vm");
}

void getRAMInfo()
{
	int t;
	char temp[64];
	string Printer;
	ifstream in;

	in.open("/proc/meminfo");

	for(int i=1; i<=7; i++)
	{
		getline(in,Printer);

		istringstream ss(Printer);
		ss>>temp>>t;
		fprintf(stdout, "%s %d MB\n",temp,t/SIZE);
	}
	in.close();
}

void getDiskInfo()
{
	ExecuteScript("df &>/data/local/data.txt");

	ifstream in;
	in.open("/data/local/data.txt");
	
	string line;
	char temp[64];
	const char *system = "/system";
	const char *data = "/data";
	const char *cache = "/cache";
	const char *sdcard1 = "/storage/sdcard1";
	const char *sdcard0 = "/storage/sdcard0";

	bool System = false;
	bool Data = false;
	bool Cache = false;
	bool SDcard1 = false;
	bool SDcard0 = false;
	
	getline(in,line);
	fprintf(stdout,"%s\n",line.c_str());

	while (in.good())
	{
		getline(in,line);
		istringstream ss(line);
		ss>>temp;

		if (!strcmp(temp,system) && !System) {
			line.replace(0,strlen(system),"System:");
			fprintf(stdout,"%s\n",line.c_str());
			System = true;
			continue;
		}
		if (!strcmp(temp,data) && !Data) {
			line.replace(0,strlen(data),"Data:");
			fprintf(stdout,"%s\n",line.c_str());
			Data = true;
			continue;
		}
		if (!strcmp(temp,cache) && !Cache) {
			line.replace(0,strlen(cache),"Cache:");
			fprintf(stdout,"%s\n",line.c_str());
			Cache = true;
			continue;
		}
		if (!strcmp(temp,sdcard1) && !SDcard1 && !IsNexus5()) {
			line.replace(0,strlen(sdcard1),"External SD:    ");
			fprintf(stdout,"%s\n",line.c_str());
			SDcard1 = true;
			continue;
		}
		if (!strcmp(temp,sdcard0) && !SDcard0 && !IsNexus5()) {
			line.replace(0,strlen(sdcard0),"Internal SD:    ");
			fprintf(stdout,"%s\n",line.c_str());
			SDcard0 = true;
			continue;
		}
	}

	in.close();
}

void getHotPlugInfo()
{
	fprintf(stdout, "\nHotplug Info:\n");
	PrintDirContent(HOTPLUG_PATH);
}

void getGPUInfo(int p)
{
	SysfsIO GPU;

	if(!p)
		fprintf(stdout, "\nGPU Info:\n");

	if(!p || p == 6)
		fprintf(stdout,"GPU Up Threshold: %s\n", GPU.create_rline(GPU_UP_THRESHOLD).c_str());

	if(!p || p == 7)
		fprintf(stdout,"GPU Down Threshold: %s\n", GPU.create_rline(GPU_DOWN_THRESHOLD).c_str());

	if(!p || p == -1)
		fprintf(stdout,"GPU Available Freq: %s\n", GPU.create_rline(GPU_AVAILABLE_FREQ).c_str());
	if(!p || p == 8)
		fprintf(stdout,"Max GPU Freq: %s\n", GPU.create_rline(GPU_MAX_FREQ).c_str());

	if(!p)
		fprintf(stdout,"Current GPU Freq: %s\n", GPU.create_rline(GPU_CURRENT_FREQ).c_str());
}

void getExtraKernelInfo(int p)
{
	SysfsIO EXTRA;
	char FastChargeStatus[] = "OFF";

	if (IsOn(FORCE_FAST_CHARGE))
		strcpy(FastChargeStatus, "ON");

	if(!p)
		fprintf(stdout, "\nExtra Kernel Info:\n");

	if(!p || p == 1)
		fprintf(stdout,"CPU Temp Threshold: %s\n", EXTRA.create_rline(TEMP_THRESHOLD).c_str());

	if(!p || p == 2)
		fprintf(stdout,"Vibration Amp: %s\n", EXTRA.create_rline(VIBRATION_AMP).c_str());

	if(!p || p == 3)
		fprintf(stdout,"Fast charge is: %s\n", FastChargeStatus);

	if(!p || p == 4)
		fprintf(stdout,"Available TCP Congestion Algorithm: %s\n", EXTRA.create_rline(AVAILABLE_TCP_CONGESTION_ALGORITHM).c_str());

	if(!p || p == 4)
	fprintf(stdout,"Current TCP Congestion Algorithm: %s\n", EXTRA.create_rline(TCP_CONGESTION_ALGORITHM).c_str());

	if(!p || p == 5) {
		fprintf(stdout, "\nSound Control Parameters:\n");
		PrintDirContent(SOUND_CONTROL_PATH);
	}
}

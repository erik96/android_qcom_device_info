#include <string>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <dirent.h>

#include "helpers.h"

static bool FileExists(const char *filename)
{
	bool ret;
	ifstream in(filename);

	if (in) {
		ret = true;
	}
	else {
		ret = false;
	}

	in.close();

	return ret;
}

string BuffFile(const char *infile)
{
	ifstream in(infile);

	string buff((istreambuf_iterator<char>(in)),
	istreambuf_iterator<char>());
	in.close();

	return buff;
}

string LineFile(const char *infile)
{
	string ret;
	ifstream in(infile);
	getline(in,ret);
	in.close();

	return ret;
}

void cpy(const char *infile, const char *outfile)
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

void PrintDirContent(const char *path)
{
	DIR *dir;
	dirent *pdir;
	char buff[128];
	string val;
	unsigned short i = 0;

	dir = opendir(path);
	
	while(pdir = readdir(dir))
	{
		++i;
		sprintf(buff,"%s/%s",path,pdir->d_name);
		if(i>2)
		{
			val = LineFile(buff);
			fprintf(stdout,"%s: %s\n",pdir->d_name,val.c_str());
		}
	}
	closedir(dir);
}

void ExcuteScript(const char *content)
{
	ofstream script("/data/local/tmp.sh");

	script<<content;
	script.close();

	pid_t pid = fork();
  	if (pid == 0) 
	{
    		execl("/system/bin/chmod", "chmod", "0770", "/data/local/tmp.sh", NULL);
		_exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == 0)
	{
		execl("/system/bin/sh", "sh", "/data/local/tmp.sh", NULL);
		_exit(EXIT_FAILURE);
	}

	usleep(700000); //Wait for the script execution
	return;
}

string GetCPUFreq(const char *path, int jump)
{
	string ret;
	ifstream in;

	in.open(path);
	
	for (int i=1; i<=jump; i++)
		in>>ret;

	in>>ret;
	in.close();

	return ret;
}

int NrFrequencies(const char *path)
{
	int ret = 0;
	string temp;
	ifstream in;

	in.open(path);

	if (!in)
		return -1;

	while (in.good())
	{
		in>>temp;
		ret++;
	}
	in.close();
	ret--;

	return ret;
}

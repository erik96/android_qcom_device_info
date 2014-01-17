#include <string>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>

#include "helpers.h"

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

	return ret;
}

void cpy (const char *infile, const char *outfile)
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

void ExcuteScript(string content)
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

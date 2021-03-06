#include <cstring>
#include <fstream>
#include <unistd.h>
#include <dirent.h>
#include <vector>
#include <string>

#include <helpers.hpp>

bool IsNexus5()
{
	string line;
	string line1("Nexus 5");

	ifstream fp;
	fp.open("/system/build.prop");

	if (!fp)
	{
		fprintf(stderr,"Unable to open input file\n");
		return false;
	}


	size_t pos;
	while (fp.good())
	{
		getline(fp,line);
		pos = line.find(line1);

		if(pos!=string::npos)
		{
			fp.close();
			return true;
		}
	}

	fp.close();
	return false;
}

bool IsOn(const char *infile)
{
	bool ret;
	ifstream in(infile);
	in>>ret;
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

	dir = opendir(path);
	
	while((pdir = readdir(dir)))
	{

		if(!strcmp(pdir->d_name,"power") || !strcmp(pdir->d_name, "uevent") || 
			!strcmp(pdir->d_name, "subsystem") || !strcmp(pdir->d_name, ".") ||
			!strcmp(pdir->d_name, ".."))
				continue;

		sprintf(buff,"%s/%s",path,pdir->d_name);
		val = LineFile(buff);
		fprintf(stdout,"%s: %s\n",pdir->d_name,val.c_str());
	}
	closedir(dir);
}

void ExecuteScript(const char *content)
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

void write_to_file(int val, const char *path)
{
	ofstream out(path);
	out<<val;
	out.close();
}

bool Has(const char *path)
{
	DIR *dir = opendir(path);

	if(dir)
	{
		closedir(dir);
		return true;
	}
	return false;
}

bool Has(const char *path, void *f)
{
	ifstream fin(path);
	
	if (fin)
	{
		fin.close();
		return true;
	}
	else
		return false;
}

string c_convert(int i)
{
	string ret;
	if(i)
		ret.assign("ON");
	else
		ret.assign("OFF");

	return ret;
}

string getPath(vector<string> &poss)
{
	unsigned int i;

	for (i = 0; i<poss.size(); i++)
		if (Has(poss[i].c_str(),NULL))
			break;

	return poss[i];
}

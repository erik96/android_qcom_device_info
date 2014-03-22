#include <fstream>
#include <cstring>

#include "classes.h"

using namespace std;

string SysfsIO::BuffFile(const char *infile) {
	ifstream in(infile);

	string buff((istreambuf_iterator<char>(in)),
	istreambuf_iterator<char>());
	in.close();

	return buff;

}

string SysfsIO::LineFile(const char *infile) {
	string ret;
	ifstream in(infile);
	getline(in,ret);
	in.close();

	return ret;
}

string SysfsIO::create_rline(string path) {
	this->path = path;
	this->content = LineFile(path.c_str());
	return content;
}

string SysfsIO::create_rbuff(string path) {
	this->path = path;
	this->content = BuffFile(path.c_str());
	return content;
}
			
void SysfsIO::create_w(string path, int val) { 
	this->path = path; 
	this->val = val; 
	ofstream out(path.c_str());
	out<<val;
	out.close();
}

void SysfsIO::create_w(string path, string content) { 
	this->path = path; 
	this->content = content;
	ofstream out(path.c_str());
	out<<content;
	out.close();
}

bool SysfsIO::create_w(string poss_path,string path,string content) {
	
	char *p;
	FILE *f = fopen(poss_path.c_str(),"r");
	ofstream out;

	this->path = path;
	this->content = content;
	p = new char[64];

	for(;fscanf(f,"%s",p)+1;)
	{
		if(!strcmp(p,content.c_str()))
		{
			out.open(path.c_str());
			out<<content;
			out.close();
			fclose(f);
			delete p;
			return true;
		}
	}

	delete p;
	fclose(f);
	return false;
}

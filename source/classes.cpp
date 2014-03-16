#include <fstream>

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
	ofstream out;
	this->poss = LineFile(poss_path.c_str());
	this->path = path;
	this->content = content;

	if (poss.find(content) != string::npos)
	{
		out.open(path.c_str());
		out<<content;
		out.close();
		return true;
	}

	return false;
}

#include <fstream>
#include <cstring>
#include <vector>
#include <iostream>
#include <dirent.h>

#include <classes.hpp>

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

/*------------------------------------------------------------------*/


int SysfsVector::get_int(const char *path)
{
	int ret = 0;
	ifstream fp(path);
	fp>>ret;
	fp.close();

	return ret;
}

int SysfsVector::vsize()
{
	return v.size()-1;
}

void SysfsVector::write_vector(int cont, int val)
{
	char buff[128];
	sprintf(buff,"%s/%s",path.c_str(),v[cont].first.c_str());
	v[cont].second = val;

	ofstream out(buff);
	out<<val;
	out.close();

}

bool SysfsVector::write_vector(string path, int cont)
{
	if(cont>vf.size()-1)
		return false;

	ofstream out(path.c_str());
	this->path = path;

	out<<fixed<<vf[cont];
	out.close();

	return true;
}		

void SysfsVector::populate_vector(string path)
{
	v.clear();
	DIR *dir;
	dirent *pdir;
	char buff[128];
	int val;
	string name;

	this->path = path;

	dir = opendir(path.c_str());
	
	while(pdir = readdir(dir))
	{

		if(!strcmp(pdir->d_name,"power") || !strcmp(pdir->d_name, "uevent") || 
			!strcmp(pdir->d_name, "subsystem") || !strcmp(pdir->d_name, ".") ||
			!strcmp(pdir->d_name, "..") || !strcmp(pdir->d_name, "dev"))
				continue;

		sprintf(buff,"%s/%s",path.c_str(),pdir->d_name);
		val = get_int(buff);
		name.assign(pdir->d_name);
		v.push_back(make_pair(name,val));
	}
	closedir(dir);
		
}

void SysfsVector::populate_vector(string poss_path, void *f)
{
	if (f)
	{
		fprintf(stderr,"Invalid use of %s , aborting...\n", __func__);
		return;
	}

	ifstream in(poss_path.c_str());
	float val;
	if (!in)
	{
		fprintf(stderr,"Invalid path: %s\n", poss_path.c_str());
		return;
	}

	this->poss_path = poss_path;

	
	while(in>>val)
		vf.push_back(val);

	in.close();
}

void SysfsVector::print_vector()
{
	int val;
	string name;
	int cont = 0;
	vector_pair::iterator it;

	for(it = v.begin(); it!=v.end(); ++it,++cont)
	{
		name = (*it).first;
		val = (*it).second;
		cout<<cont<<": "<<name<<": "<<val<<"\n";
	}
}

void SysfsVector::print_vector(void *f)
{
	if (f)
	{
		fprintf(stderr,"Invalid use of %s , aborting...", __func__);
		return;
	}

	vector <double>::iterator it;
	int cont = 0;

	for(it = vf.begin(); it!=vf.end(); ++it,++cont)
		cout<<fixed<<cont<<": "<<*it<<"\n";
}

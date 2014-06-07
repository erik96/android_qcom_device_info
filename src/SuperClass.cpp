#include <SuperClass.hpp>

SingleBoxPreference::SingleBoxPreference(string path) {

	this->path = path;
	init();

}

SingleBoxPreference::SingleBoxPreference(string path, bool isBool) {

    	this->path = path;
    	this->isBool = true;
    	init();
}

void SingleBoxPreference::init() {

	ifstream fin;
	status = new char[8];
	strcpy(status,"OFF");

    	if(isBool) {
            	fin.open(path.c_str());
            	fin>>on;
            	fin.close();

            	if (on)
                	strcpy(status,"ON");
            	return;
    	}

	fin.open(path.c_str());
	char c;

	fin>>c;

	if (isalpha(c)) {
		isChar = true;
		on = false;

			if(c == 'Y' || c == 'y') {
				on = true;
				strcpy(status,"ON");
			}
		fin.close();

	} else {
		fin.close();
		fin.open(path.c_str());
		fin>>val;
		fin.close();
	}
}

int SingleBoxPreference::getValue() {

	init();
	return val;
}

string SingleBoxPreference::stat() { init(); string ret(status); return ret; }

void SingleBoxPreference::write(int nVal) {

	ofstream out(path.c_str());
	out<<nVal;
	out.close();
	init();
}

void SingleBoxPreference::mSwitch() {

	ofstream out(path.c_str());
	if(isBool)
		out<<(!on);

	out.close();
}


SingleBoxPreference::~SingleBoxPreference() {
	delete [] status;
}



///////////////////////////////////////////////////////////////////////////////


ListPreference::ListPreference(string readPath, string writePath) {

	this->readPath = readPath;
	this->writePath = writePath;
	isFile = true;

	fillFromFile();

}

ListPreference::ListPreference(string readPath) {

	this->readPath = readPath;
	isFile = false;

	fillFromDir();
}

string ListPreference::status()
{
	string ret;
	ifstream fin(writePath.c_str());
	
	getline(fin,ret);

	return ret;
}

void ListPreference::fillFromFile() {

	int key = 0;
	string val;
	ifstream fin(readPath.c_str());

	while(fin>>val)
	{
		struct mapped m = {val, 0 };
		fileMap.insert(make_pair(key++,m));
	}

	fin.close();
}

void ListPreference::fillFromDir() {


	int key = 0;
	DIR *dir;
	dirent *pdir;
	char buff[128];
	int val;
	string name;

	dir = opendir(readPath.c_str());
	if(!dir)
	{
		fprintf(stderr,"Invalid use of %s , aborting...\n", __func__);
		return;
	}
		
	
	while((pdir = readdir(dir)))
	{

		if(!strcmp(pdir->d_name,"power") || !strcmp(pdir->d_name, "uevent") || 
			!strcmp(pdir->d_name, "subsystem") || !strcmp(pdir->d_name, ".") ||
			!strcmp(pdir->d_name, "..") || !strcmp(pdir->d_name, "dev"))
				continue;

		sprintf(buff,"%s/%s",readPath.c_str(),pdir->d_name);
		val = SysfsVector::get_int(buff); //TEMP
		name.assign(pdir->d_name);
		mapped m = { name,val };
		dirMap.insert(make_pair(key++,m));
	}
	closedir(dir);
		
}

void ListPreference::mChange(unsigned position)
{
		ofstream out(writePath.c_str());
		out<<fileMap[position].str;
		out.close();
}

void ListPreference::mChangeByValue(unsigned position, int val)
{
	string full(readPath);
	full+="/";
	full+=dirMap[position].str;

	ofstream fout(full.c_str());
	if (fout)
		fout<<val;
	fout.close();
} 

void ListPreference::mOutput()
{
	if(isFile)
		list(fileMap);
	else
		list(dirMap);
		
}

bool ListPreference::has(unsigned int position)
{
	if(isFile)
		return fileMap.count(position);
	else
		return dirMap.count(position);
}

template <typename T>
void ListPreference::list(T &m)
{
	for (auto &it : m) {
			if (isFile)
				cout<<it.first<<": "<<it.second.str<<'\n';
			else
				cout<<it.first<<": "<<it.second.str<<": "<<it.second.value<<'\n';
	}
}

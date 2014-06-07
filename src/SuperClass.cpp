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

	//fillDir(stringMap);
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
		fileMap.insert(make_pair(key++,val));

	fin.close();
}

template <typename T>
void ListPreference::list(T &m)
{
	typename T::iterator it;

	for (it = m.begin(); it!=m.end(); ++it)
		cout<<(*it).first<<": "<<(*it).second<<'\n';
}

void ListPreference::mOutput()
{
	if(isFile)
		list(fileMap);
	else
		list(dirMap);
		
}

void ListPreference::mChange(unsigned position)
{
		ofstream out(writePath.c_str());
		out<<fileMap[position];
		out.close();
}

#include <SuperClass.hpp>

SingleBoxPreference::SingleBoxPreference(string path) {

	this->path = path;
	init();
		
}

void SingleBoxPreference::init() {

	ifstream fin(path.c_str());
	char c;
	status = new char[8];

	fin>>c;

	if (isalpha(c)) {
		isChar = true;
		strcpy(status,"OFF");
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

string stat() { init(); string ret(status); return ret; }

void SingleBoxPreference::write(int nVal) {

	ofstream out(path.c_str());
	out<<nVal;
	out.close();
	init();
}

SingleBoxPreference::~SingleBoxPreference()
{
	delete [] status;
}

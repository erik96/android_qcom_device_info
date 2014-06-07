#include <SuperClass.hpp>

SingleBoxPreference::SingleBoxPreference(string path) {

	this->path = path;
	init();

}

SingleBoxPreference::SingleBoxPreference(string path, bool isBool)
{
    this->path = path;
    this->isBool = true;
    init();
}

void SingleBoxPreference::init() {

    ifstream fin;
    status = new char[8];
    strcpy(status,"OFF");

    if(isBool) {
            fin.open(path.c_str())
            f>>on;
            fin.close();

            if (on)
                strcpy(status,"ON");
            return;
    }

	fin.open(path.c_str())
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

string stat() { init(); string ret(status); return ret; }

void SingleBoxPreference::write(int nVal) {

	ofstream out(path.c_str());
	out<<nVal;
	out.close();
	init();
}

void SingleBoxPreference::mSwitch() {

    ofstream out(path.c_str())
    if(isBool)
        out<<(!on);

    out.close();
}


SingleBoxPreference::~SingleBoxPreference()
{
	delete [] status;
}

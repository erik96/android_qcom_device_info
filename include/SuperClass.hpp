#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include <iostream>

using namespace std;


class SingleBoxPreference {

	private:
		int val;
		char *status;
		bool on,isChar,isBool;
		string path;
		void init();

	public:
		SingleBoxPreference(string path);
		SingleBoxPreference(string path, bool isBool);
		void mSwitch();
		void write(int nVal);
		int getValue();
		string stat();

		~SingleBoxPreference();

};

class ListPreference {

	private:
		map <int,string> fileMap;
		map <string,int> dirMap;
		string readPath, writePath;
		bool isFile;

		void fillFromFile();
		void fillDir();

		template <typename T>
		void list(T &m);

	public:
		ListPreference(string readPath, string writePath);
		ListPreference(string readPath);

		void mOutput();
		void mChange(unsigned position);
		string status();
};

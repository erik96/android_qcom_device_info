#ifndef SUPERCLASS_HPP
#define SUPERCLASS_HPP

#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include <iostream>
#include <dirent.h>

using namespace std;

struct mapped
{
	string tr;
	int value;
};

class SingleBoxPreference {

	private:
		string path;
		int val;
		char *status;
		bool on,isChar,isBool;
		void init();

	public:
		SingleBoxPreference(string path, bool isBool=false);
		SingleBoxPreference(SingleBoxPreference &obj);
		void mSwitch();
		void write(int nVal);
		int getValue();
		string stat();

		~SingleBoxPreference();

};

class ListPreference {

	private:
		map <int, mapped> Map;
		string readPath, writePath;
		bool isFile;

		void fillFromFile();
		void fillFromDir();

	public:
		ListPreference(string readPath, string writePath);
		ListPreference(string readPath);

		ListPreference(ListPreference &obj);

		void mOutput();
		void mChange(unsigned position);
		void mChangeByValue(unsigned position, int val);
		string status();
		bool has(unsigned int position);

		template <typename T>
		void list(T &m);

		static int get_int(const char *path);
};

#endif //SUPERCLASS_HPP

#ifndef CLASSES_H
#define CLASSES_H

#include <string>

using namespace std;

class SysfsIO {

	private:
		int val;
		string path;
		string content;
		string poss;

		string BuffFile(const char *infile);

		string LineFile(const char *infile);

	public:

		string create_rline(string path);

		string create_rbuff(string path);
			
		void create_w(string path, int val);

		void create_w(string path, string content);

		bool create_w(string poss_path,string path,string content);

		
};

#endif //CLASSES_H
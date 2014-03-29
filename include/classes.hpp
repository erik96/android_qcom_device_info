#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <string>

using namespace std;

typedef vector< pair<string,int> > vector_pair;

class SysfsIO {

	private:
		int val;
		string path;
		string content;

		string BuffFile(const char *infile);

		string LineFile(const char *infile);

	public:

		string create_rline(string path);

		string create_rbuff(string path);
			
		void create_w(string path, int val);

		void create_w(string path, string content);

		bool create_w(string poss_path,string path,string content);

		void create_w(string path,vector< pair<string,int> > &v, int cont, int val);
		

		
};

class SysfsVector {

	private:
		vector_pair v;
		string path;

		int get_int(const char *path);

	public:
		int vsize();
		void populate_vector(string path);
		void print_vector();
		void write_vector(int cont, int val);
};


#endif //CLASSES_HPP

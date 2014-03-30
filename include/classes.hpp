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
		
};

class SysfsVector {

	private:
		vector_pair v;
		vector <unsigned long> vf;
		string path;
		string poss_path;

		int get_int(const char *path);

	public:
		unsigned int vsize();
		void populate_vector(string path);
		void populate_vector(string path,void *f);
		void print_vector();
		void print_vector(void *f);
		void write_vector(unsigned int cont, int val);
		bool write_vector(string path, unsigned int cont);
};


#endif //CLASSES_HPP

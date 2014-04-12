#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <vector>

using namespace std;

bool IsNexus5();

bool IsOn(const char *infile);

string BuffFile(const char *infile);

string LineFile(const char *infile);

void cpy (const char *infile, const char *outfile);

void PrintDirContent(const char *path);

void ExecuteScript(const char *content);

void write_to_file(int val, const char *path);

bool Has(const char *path);

bool Has(const char *path, void *f);

string c_convert(int i);

string getPath(vector<string> &poss);

#endif //HELPERS_HPP

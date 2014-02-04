#include <string>

using namespace std;

bool IsNexus5();

bool FileExists(const char *filename);

string BuffFile(const char *infile);

string LineFile(const char *infile);

void cpy (const char *infile, const char *outfile);

void PrintDirContent(const char *path);

void ExcuteScript(const char *content);

string GetCPUFreq(const char *path, int jump);

int NrFrequencies(const char *path);

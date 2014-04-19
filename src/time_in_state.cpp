#include <fstream>
#include <vector>
#include <iostream>

#define HZ 100

using namespace std;

static inline unsigned int jiffies_to_msecs(const unsigned long j) //code from the linux kernel
{
 	#if HZ <= 1000 && !(1000 % HZ)
         	return (1000 / HZ) * j;
 	#elif HZ > 1000 && !(HZ % 1000)
         	return (j + (HZ / 1000) - 1)/(HZ / 1000);
 	#else
         	return (j * 1000) / HZ;
 	#endif
}


class TimeInState {

	private:
		vector < pair<long,long> > Frequencies;
		string path;


	public:
		TimeInState(string path) { this->path = path; }

		void getTimeByCPU()
		{
			ifstream f(path.c_str());
			if(!f) {
				cout<<"Invalid path"<<__func__;
				return;
			}

			long x,y;
			
			while(f>>x>>y)
				Frequencies.push_back(make_pair(x,y));

			f.close();

			//TODO:: WRITE VECTOR
		}
		
		void Print()
		{
			vector < pair<long,long> >::iterator it;
			cout<<"Freq\tTime in state(minutes)\n";
			
			for(it = Frequencies.begin(); it!=Frequencies.end(); ++it)
			{
				int minutes = (int) ((jiffies_to_msecs((int)it->second) / (1000*60)) );
				cout<<(*it).first<<"\t"<<minutes<<"\n";
			}
		}
};


void ShowTimeInState()
{
	TimeInState T("/sys/devices/system/cpu/cpu0/cpufreq/stats/time_in_state");

	T.getTimeByCPU();
	T.Print();
}

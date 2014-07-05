#ifndef WRAPPER_HPP
#define WRAPPER_HPP

#include <SuperClass.hpp>
#include <map>
#include <memory>

struct Wrapper {

	SingleBoxPreference *sbp;
	ListPreference *lp;

	Wrapper(SingleBoxPreference &obj) { sbp = new SingleBoxPreference(obj); lp = NULL; }
	Wrapper(ListPreference &obj) { lp = new ListPreference(obj); sbp = NULL; }

	operator SingleBoxPreference*() { return sbp; };
	operator ListPreference*() { return lp; };

	~Wrapper() {
		if(sbp != NULL)
			delete sbp;

		if (lp != NULL)
			delete lp; 
	}
};

extern map <int, pair<string, shared_ptr<Wrapper> > > heap;

#endif //WRAPPER_HPP

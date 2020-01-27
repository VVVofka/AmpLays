#pragma once
#include "Lay.h"
class Lays {
public:
	std::vector<Lay> vlays;
	Lays(int szx_0, int szy_0, std::vector<vtype>* vArray) {
		assert(szx_0 > 1 && szy_0 > 1);
		vlays.push_back(Lay(szx_0, szy_0, vArray));
		int n = 0;
		vlays[n].dump();
		while (vlays[n].sz > 1 && vlays[n].szy > 1) {
			n++;
			Lay* layUp = n + 1 < vlays.size() ? &vlays[n + 1] : nullptr;
			vlays.push_back(Lay(&vlays[n - 1], layUp));
		}
	} // ///////////////////////////////////////////////////////////////
	size_t size() {
		return vlays.size();
	} // ////////////////////////////////////////////////////////////////
	Lay* operator[](int n_lay) {
		return &vlays[n_lay];
	} // //////////////////////////////////////////////////////////////
	array_view<vtype, 1>* operator()(int n_lay) {
		return vlays[n_lay].v;
	} // //////////////////////////////////////////////////////////////
	void dump() {
		for (int n = 0; n < vlays.size(); n++) 
			vlays[n].dump();
	} // //////////////////////////////////////////////////////////////
}; // ********************************************************************


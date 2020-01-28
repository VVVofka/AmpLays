#pragma once
#include "Lay.h"
#include "Lay0.h"
#include "LayLast.h"
class Lays {
public:
	Lay0 lay0;
	std::vector<Lay> vlays;
	LayLast laylast;

	Lays(int szx, int szy, std::vector<vtype>* vArray) {
		assert(szx > 2 && szy > 2);
		lay0 = Lay0(szx, szy, vArray);
		lay0.dump();
		while ((szx /= 2) > 1 && (szy /= 2) > 1) {
			vlays.push_back(Lay(szx, szy));
		}
		laylast = LayLast(szx, szy);
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


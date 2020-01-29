#pragma once
#include "Lay.h"
#include "Lay0.h"
#include "LayLast.h"
class Lays {
public:
	Lay0 lay0;
	std::vector<Lay> vlays;
	LayLast laylast;

	Lays(int szy, int szx, std::vector<vtype>& vArray) {
		assert(szy > 2 && szx > 2);
		lay0 = Lay0(szy, szx, vArray);
		//lay0.dump();
		while (true) {
			szy /= 2, szx /= 2;
			if(szy % 2 || szx % 2) break;
			vlays.push_back(Lay(szy, szx));
		}
		laylast = LayLast(szy, szx);
	} // ///////////////////////////////////////////////////////////////
	size_t size() {
		return vlays.size() + 2;
	} // ////////////////////////////////////////////////////////////////
	LayBase* operator[](int n_lay) {
		if (n_lay == 0)
			return &lay0;
		if (n_lay == size() - 1)
			return &laylast;
		return &vlays[n_lay - 1];
	} // //////////////////////////////////////////////////////////////
	av2* v(int n_lay) {
		return this->operator[](n_lay)->v;
	} // //////////////////////////////////////////////////////////////
	void dump() {
		lay0.dump();
		for (int n = 0; n < vlays.size(); n++)
			vlays[n].dump();
		laylast.dump();
	} // //////////////////////////////////////////////////////////////
}; // ********************************************************************


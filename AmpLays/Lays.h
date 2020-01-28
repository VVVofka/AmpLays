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
		return vlays.size() + 2;
	} // ////////////////////////////////////////////////////////////////
	LayBase* operator[](int n_lay) {
		if (n_lay == 0)
			return &lay0;
		if (n_lay == size() - 1)
			return &laylast;
		return &vlays[n_lay - 1];
	} // //////////////////////////////////////////////////////////////
	array_view<vtype, 1>* operator()(int n_lay) {
		return this->operator[](n_lay)->v;
	} // //////////////////////////////////////////////////////////////
	void dump() {
		lay0.dump();
		for (int n = 0; n < vlays.size(); n++)
			vlays[n].dump();
		laylast.dump();
	} // //////////////////////////////////////////////////////////////
}; // ********************************************************************


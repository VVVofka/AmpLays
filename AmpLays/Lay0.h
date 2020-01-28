#pragma once
#include "LayBase.h"
class Lay0 :	public LayBase{
public:
	Lay0() {}
	int szy() { return v->extent[0] - 1; }
	int szx() { return v->extent[1] - 1; }
	Lay0(int szy, int szx, std::vector<vtype>& pv) {
		assert(pv.size() == (szy+1) * (szx+1));
		v = new concurrency::array_view<vtype, 2>(szy+1, szx+1, pv);
	} // //////////////////////////////////////////////////////////////////////////////////
}; // *******************************************************************************


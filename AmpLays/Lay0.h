#pragma once
#include "LayBase.h"
class Lay0 :	public LayBase{
	int realszx = 0;
	int realszy = 0;
public:
	Lay0(int sz_x, int sz_y, std::vector<vtype>* p_v) {
		szx = sz_x;
		szy = sz_y;
		sz = szx * szy;
		realszx = szx + 1;
		realszy = szy + 1;
		size_t vsize = p_v->size();
		assert(realszx * realszy == vsize);
		v = new av(vsize, *p_v);
		layDn = layUp = nullptr;
	} // //////////////////////////////////////////////////////////////////////////////////
}; // *******************************************************************************


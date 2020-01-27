#pragma once
#include <amp.h>

class Lay {
public:
	int szx;
	int szy;
	int sz;
	concurrency::array_view<vtype, 1>* v;
	Lay* layDn;
	Lay* layUp;
	Lay(int sz_x, int sz_y, std::vector<vtype>* p_v) {
		size_t vsize = p_v->size();
		assert((sz_x + 1) * (sz_y + 1) == vsize);
		szx = sz_x;
		szy = sz_y;
		sz = szx * szy;
		v = new concurrency::array_view<vtype, 1>(vsize, *p_v);
		layDn = layUp = nullptr;
	} // //////////////////////////////////////////////////////////////////////////////////
	Lay(Lay* lay_Dn, Lay* lay_Up = nullptr) {
		layDn = lay_Dn;
		szx = layDn->szx / 2;
		szy = layDn->szy / 2;
		sz = szx * szy;
		v = new concurrency::array_view<vtype, 1>((szx + 1) * (szy + 1));
		layUp = lay_Up;
	} // ////////////////////////////////////////////////////////////////////////////////////
	void dump() {
		for(int y = 0; y < szy; y++) {
			std::cout << std::endl;
			for(int x = 0; x < szx; x++) {
				std::cout << " " << *(v->data() + y * szx + x);
			}
		}
		std::cout << std::endl;
	} // ///////////////////////////////////////////////////////////////////////////////////
}; // ***************************************************************************************


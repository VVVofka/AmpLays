#pragma once
#include <amp.h>
using namespace concurrency;

class Lay {
public:
	int szx;
	int szy;
	int sz;
	array_view<vtype, 1>* v;
	Lay* layDn;
	Lay* layUp;
	void Create0(int sz_x, int sz_y, vector<vtype>* p_v) {
		assert(v == 0);
		szx = sz_x;
		szy = sz_y;
		sz = szx * szy;
		v = new array_view<vtype, 1>(sz, *p_v);
		layDn = nullptr;
	} // //////////////////////////////////////////////////////////////////////////////////
	void Create(Lay* lay_Dn, Lay* lay_Up = nullptr) {
		assert(v == 0);
		layDn = lay_Dn;
		szx = layDn->szx / 2;
		szy = layDn->szy / 2;
		sz = szx * szy;
		v = new array_view<vtype, 1>(sz);
		layUp = lay_Up;
	} // ////////////////////////////////////////////////////////////////////////////////////
	void dump() {
		for (int y = 0; y < szy; y++) {
			cout << endl;
			for (int x = 0; x < szx; x++) {
				cout << " " << *(v->data() + y * szx + x);
			}
		}
		cout << endl;
	} // ///////////////////////////////////////////////////////////////////////////////////
}; // ***************************************************************************************


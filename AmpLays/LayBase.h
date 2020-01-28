#pragma once
#include <amp.h>
#include <cassert>
typedef int vtype;

class LayBase {
public:
	LayBase() { v = nullptr; }
	concurrency::array_view<vtype, 2>* v;
	int szy() { return v->extent[0]; }
	int szx() { return v->extent[1]; }

	void dump(concurrency::array_view<vtype, 2>* p_v) {
		std::cout << "   y:" << p_v->extent[0] << " x:" << p_v->extent[1];
		for(int y = 0; y < p_v->extent[0]; y++) {
			std::cout << std::endl;
			for(int x = 0; x < p_v->extent[1]; x++) {
				vtype tmp = p_v->operator()(y, x);
				std::cout << " " << tmp;
			}
		}
		std::cout << std::endl;
	} // ///////////////////////////////////////////////////////////////////////////////////
	void dump() { dump(v); }

}; // **************************************************************************


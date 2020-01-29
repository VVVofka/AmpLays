#pragma once
#include <amp.h>
#include <cassert>
#include "XY.h"
typedef int vtype;
typedef concurrency::array_view<vtype, 2> av2;

class LayBase {
public:
	LayBase() { v = nullptr; }
	av2* v;
	
	int szy() { return v->extent[0]; }
	int szx() { return v->extent[1]; }

	void dump(const av2& v) {
		std::cout << "   y:" << v.extent[0] << " x:" << v.extent[1];
		for(int y = 0; y < v.extent[0]; y++) {
			std::cout << std::endl;
			for(int x = 0; x < v.extent[1]; x++) {
				vtype tmp = v(y, x);
				std::cout << " " << tmp;
			}
		}
		std::cout << std::endl;
	} // ///////////////////////////////////////////////////////////////////////////////////
	void dump() { dump(*v); }

}; // **************************************************************************


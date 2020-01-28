#pragma once
#include <amp.h>
#include <cassert>
typedef int vtype;

class LayBase {
public:
	LayBase() { v = nullptr; }
	~LayBase() {
		//if(v != nullptr) delete v;
	}
	concurrency::array_view<vtype, 2>* v;
	int szy() { return v->extent[0]; }
	int szx() { return v->extent[1]; }

	void dump() {
		std::cout << "   y:" << v->extent[0] << " x:" << v->extent[1];
		for(int y = 0; y < v->extent[0]; y++) {
			std::cout << std::endl;
			for(int x = 0; x < v->extent[1]; x++) {
				vtype tmp = v->operator()(y, x);
				std::cout << " " << tmp;
			}
		}
		std::cout << std::endl;
	} // ///////////////////////////////////////////////////////////////////////////////////

}; // **************************************************************************


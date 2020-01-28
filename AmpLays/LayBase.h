#pragma once
#include <amp.h>
#include <cassert>

typedef int vtype;
typedef concurrency::array_view<vtype, 1> av;

class LayBase{
public:
	int szx;
	int szy;
	int sz;

	av* v;
	Lay* layUp;

	void dump() {
		for (int y = 0; y < szy; y++) {
			std::cout << std::endl;
			for (int x = 0; x < szx; x++) {
				std::cout << " " << *(v->data() + y * szx + x);
			}
		}
		std::cout << std::endl;
	} // ///////////////////////////////////////////////////////////////////////////////////

}; // **************************************************************************


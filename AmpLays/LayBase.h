#pragma once
#include <amp.h>
#include <cassert>
#include "XY.h"
struct vtype {
	// bit 0: exist
	// bit 1: intent(inertion)
	// bits 2,3,4: direct
	unsigned int a = 0;

	YX xy;
}; // ********************************************************************************
typedef concurrency::array_view<vtype, 2> av2;
typedef concurrency::array_view<const vtype, 2> avc2;

class LayBase {
public:
	LayBase() { v = nullptr; }
	av2* v;

	int szy() { return v->extent[0]; }
	int szx() { return v->extent[1]; }

	void dump(const av2& v) {
		std::cout << "   y:" << v.extent[0] << " x:" << v.extent[1];
		for (int y = 0; y < v.extent[0]; y++) {
			std::cout << std::endl;
			for (int x = 0; x < v.extent[1]; x++) {
				vtype tmp = v(y, x);
				std::cout << " " << (tmp.a & 1);
			}
		}
		std::cout << std::endl;
	} // ///////////////////////////////////////////////////////////////////////////////////
	void dump() {
		dump(*v);
	} // ///////////////////////////////////////////////////////////////////////////////////
	void dumpYX(const av2& v) {
		std::cout << "   y:" << v.extent[0] << " x:" << v.extent[1];
		for (int y = 0; y < v.extent[0]; y++) {
			std::cout << std::endl;
			for (int x = 0; x < v.extent[1]; x++) {
				vtype tmp = v(y, x);
				if (tmp.xy.y >= 0)
					std::cout << " ";
				std::cout << tmp.xy.y << ".";
				if (tmp.xy.x >= 0)
					std::cout << " ";
				std::cout << tmp.xy.x << "\t";
			}
		}
		std::cout << std::endl;
	} // ///////////////////////////////////////////////////////////////////////////////////
	void dumpYX() {
		dumpYX(*v);
	} // ///////////////////////////////////////////////////////////////////////////////////


}; // **************************************************************************


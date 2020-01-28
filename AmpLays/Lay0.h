#pragma once
#include "LayBase.h"
#include "Shifter.h"
class Lay0 : public LayBase {
public:
	Shifter shifter;
	Lay0() {}
	Lay0(int szy, int szx, std::vector<vtype>& pv) {
		assert(pv.size() == (szy + 1) * (szx + 1));
		v = new concurrency::array_view<vtype, 2>(szy + 1, szx + 1, pv);
	} // ////////////////////////////////////////////////////////////////////////////
	int szy() { return v->extent[0] - 1; }
	int szx() { return v->extent[1] - 1; }
	// ////////////////////////////////////////////////////////////////////////////
	concurrency::array_view<vtype, 2> Shift() {
		shifter.Run();
		auto av = v->section(shifter.y(), shifter.x(), szy(), szx());
		//shifter.dump(); dump(&av);
		return av;
	} // ////////////////////////////////////////////////////////////////////////////
}; // *******************************************************************************


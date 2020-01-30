#pragma once
#include "LayBase.h"
#include "Shifter.h"
class Lay0 : public LayBase {
public:
	Shifter shifter;
	Lay0() {}
	Lay0(int szy, int szx, std::vector<vtype>& pv) {
		assert(pv.size() == (szy + 1) * (szx + 1));
		v = new av2(szy + 1, szx + 1, pv);
	} // ////////////////////////////////////////////////////////////////////////////
	int szy() { return v->extent[0] - 1; }
	int szx() { return v->extent[1] - 1; }
	// ////////////////////////////////////////////////////////////////////////////
	av2 Shift() {
		shifter.Run();
		auto av = v->section(shifter.y(), shifter.x(), szy(), szx());
		//shifter.dump(); dump(&av);
		return av;
	} // ////////////////////////////////////////////////////////////////////////////
	void dumpall() {
		LayBase::dump(*v);
	} // ///////////////////////////////////////////////////////////////////////////
	void dumpallYX() {
		LayBase::dumpYX(*v);
	} // ///////////////////////////////////////////////////////////////////////////
	void dump() {
		auto av = v->section(shifter.y(), shifter.x(), szy(), szx());
		LayBase::dump(av);
	} // ///////////////////////////////////////////////////////////////////////////
	void dumpYX() {
		auto av = v->section(shifter.y(), shifter.x(), szy(), szx());
		LayBase::dumpYX(av);
	} // ///////////////////////////////////////////////////////////////////////////
}; // *******************************************************************************


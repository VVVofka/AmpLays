#pragma once
#include "LayBase.h"
using namespace concurrency;

class ProcA2 {
private:
	avc2 m_dn;
	av2 m_up;
public:
	ProcA2(const avc2& vDnIn, const av2& vUpOut)
		: m_dn(vDnIn), m_up(vUpOut) {}
	void operator()(index<2> idx) const restrict(amp) {
		auto y = 2 * idx[0];
		auto x = 2 * idx[1];
		auto tmp =
			m_dn[index<2>(y, x)].a +
			m_dn[index<2>(y + 1, x)].a +
			m_dn[index<2>(y, x + 1)].a +
			m_dn[index<2>(y + 1, x + 1)].a;
		m_up[idx].a = tmp > 1 ? 1 : 0;
	} // //////////////////////////////////////////////////////////////////////////////////
}; // *************************************************************************************
class ProcTable {
protected:
	const YX4 v[16] = {
		YX4(-1, -1, -1, 1, 1, -1, 1, 1),//0000
		YX4(0, 0, 1, 0, 0, 1, 0, 0),	//0001
		YX4(1, 0, 0, 0, 0, 0, 0, -1),	//0010
		YX4(0, 0, 0, 0, 0, -1, 0, 1),	//0011
		YX4(0, 1, 0, 0, 0, 0, -1, 0),	//0100
		YX4(0, 0, -1, 0, 0, 0, 1, 0),	//0101
		YX4(1, 1, 0, 0, 0, 0, -1, -1),	//0110
		YX4(0, 0, 0, 0, 0, 0, 1, 1),	//0111
		YX4(0, 0, 0, -1, -1, 0, 0, 0),	//1000
		YX4(0, 0, 1, -1, -1, 1, 0, 0),	//1001
		YX4(-1, 0, 0, 0, 1, 0, 0, 0),	//1010
		YX4(0, 0, 0, 0, 1, -1, 0, 0),	//1011
		YX4(0, -1, 0, 1, 0, 0, 0, 0),	//1100
		YX4(0, 0, -1, 1, 0, 0, 0, 0),	//1101
		YX4(-1, -1, 0, 0, 0, 0, 0, 0),	//1110
		YX4(-1, -1, -1, 1, 1, -1, 1, 1)	//1111
	};
}; // **************************************************************************************
class ProcT2Last : private ProcTable {
private:
	av2 m_dn;
	avc2 m_up;
public:
	ProcT2Last(const avc2& vUpIn, const av2& vDnOut)
		: m_up(vUpIn), m_dn(vDnOut) {}
	void operator()(index<2> idx) const restrict(amp) {
		auto y = 2 * idx[0];
		auto x = 2 * idx[1];
		int iv =
			m_dn[index<2>(y, x)].a +
			m_dn[index<2>(y, x + 1)].a * 2 +
			m_dn[index<2>(y + 1, x)].a * 4 +
			m_dn[index<2>(y + 1, x + 1)].a * 8;
		YX4 mask = v[iv];

		auto idx0 = index<2>(y, x);
		m_dn[idx0].xy.y = mask.a.y;
		m_dn[idx0].xy.x = mask.a.x;

		auto idx1 = index<2>(y, x + 1);
		m_dn[idx1].xy.y = mask.b.y;
		m_dn[idx1].xy.x = mask.b.x;

		auto idx2 = index<2>(y + 1, x);
		m_dn[idx2].xy.y = mask.c.y;
		m_dn[idx2].xy.x = mask.c.x;

		auto idx3 = index<2>(y + 1, x + 1);
		m_dn[idx3].xy.y = mask.d.y;
		m_dn[idx3].xy.x = mask.d.x;
	} // //////////////////////////////////////////////////////////////////////////////////
}; // *************************************************************************************
class ProcT2 : private ProcTable {
private:
	av2 m_dn;
	avc2 m_up;
public:
	ProcT2(const avc2& vUpIn, const av2& vDnOut)
		: m_up(vUpIn), m_dn(vDnOut) {}
	void operator()(index<2> idx) const restrict(amp) {
		typexy y = m_up[idx].xy.y;
		typexy x = m_up[idx].xy.x;
		auto idxY = 2 * idx[0];
		auto idxX = 2 * idx[1];
		int iv =
			m_dn[index<2>(idxY, idxX)].a +
			m_dn[index<2>(idxY, idxX + 1)].a * 2 +
			m_dn[index<2>(idxY + 1, idxX)].a * 4 +
			m_dn[index<2>(idxY + 1, idxX + 1)].a * 8;
		YX4 mask = v[iv];

		auto idx0 = index<2>(idxY, idxX);
		m_dn[idx0].xy.y = mask.a.y + y;
		m_dn[idx0].xy.x = mask.a.x + x;

		auto idx1 = index<2>(idxY, idxX + 1);
		m_dn[idx1].xy.y = mask.b.y + y;
		m_dn[idx1].xy.x = mask.b.x + x;

		auto idx2 = index<2>(idxY + 1, idxX);
		m_dn[idx2].xy.y = mask.c.y + y;
		m_dn[idx2].xy.x = mask.c.x + x;

		auto idx3 = index<2>(idxY + 1, idxX + 1);
		m_dn[idx3].xy.y = mask.d.y + y;
		m_dn[idx3].xy.x = mask.d.x + x;
	} // //////////////////////////////////////////////////////////////////////////////////
}; // *************************************************************************************
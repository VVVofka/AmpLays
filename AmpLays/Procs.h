#pragma once
#include <amp_math.h>
#include "LayBase.h"

using namespace concurrency;
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
#define mskExist 1
#define mskIntent 2
class ProcA {
private:
	avc2 m_dn;
	av2 m_up;
public:
	ProcA(const avc2& vDnIn, const av2& vUpOut)
		: m_dn(vDnIn), m_up(vUpOut) {}
	void operator()(index<2> idx) const restrict(amp) {
		auto y = 2 * idx[0];
		auto x = 2 * idx[1];
		auto tmp =
			(m_dn[index<2>(y, x)].a & mskExist) +
			(m_dn[index<2>(y + 1, x)].a & mskExist) +
			(m_dn[index<2>(y, x + 1)].a & mskExist) +
			(m_dn[index<2>(y + 1, x + 1)].a & mskExist);
		m_up[idx].a = tmp > 1 ? 1 : 0;
	} // //////////////////////////////////////////////////////////////////////////////////
}; // *************************************************************************************
class ProcTLast : private ProcTable {
private:
	av2 m_dn;
	avc2 m_up;
public:
	ProcTLast(const avc2& vUpIn, const av2& vDnOut)
		: m_up(vUpIn), m_dn(vDnOut) {}
	void operator()(index<2> idx) const restrict(amp) {
		auto idxY = 2 * idx[0];
		auto idxX = 2 * idx[1];
		auto idx0 = index<2>(idxY, idxX);
		auto idx1 = index<2>(idxY, idxX + 1);
		auto idx2 = index<2>(idxY + 1, idxX);
		auto idx3 = index<2>(idxY + 1, idxX + 1);
		int iv =
			(m_dn[idx0].a & mskExist) +
			(m_dn[idx1].a * 2 & mskExist) +
			(m_dn[idx2].a * 4 & mskExist) +
			(m_dn[idx3].a * 8 & mskExist);
		YX4 mask = v[iv];

		m_dn[idx0].xy.y = mask.a.y;
		m_dn[idx0].xy.x = mask.a.x;

		m_dn[idx1].xy.y = mask.b.y;
		m_dn[idx1].xy.x = mask.b.x;

		m_dn[idx2].xy.y = mask.c.y;
		m_dn[idx2].xy.x = mask.c.x;

		m_dn[idx3].xy.y = mask.d.y;
		m_dn[idx3].xy.x = mask.d.x;
	} // //////////////////////////////////////////////////////////////////////////////////
}; // *************************************************************************************
class ProcT : private ProcTable {
private:
	av2 m_dn;
	avc2 m_up;
public:
	ProcT(const avc2& vUpIn, const av2& vDnOut)
		: m_up(vUpIn), m_dn(vDnOut) {}
	void operator()(index<2> idx) const restrict(amp) {
		int y = m_up[idx].xy.y;
		int x = m_up[idx].xy.x;
		auto idxY = 2 * idx[0];
		auto idxX = 2 * idx[1];
		auto idx0 = index<2>(idxY, idxX);
		auto idx1 = index<2>(idxY, idxX + 1);
		auto idx2 = index<2>(idxY + 1, idxX);
		auto idx3 = index<2>(idxY + 1, idxX + 1);
		int iv =
			(m_dn[idx0].a & mskExist) +
			(m_dn[idx1].a * 2 & mskExist) +
			(m_dn[idx2].a * 4 & mskExist) +
			(m_dn[idx3].a * 8 & mskExist);
		YX4 mask = v[iv];

		m_dn[idx0].xy.y = mask.a.y + y;
		m_dn[idx0].xy.x = mask.a.x + x;

		m_dn[idx1].xy.y = mask.b.y + y;
		m_dn[idx1].xy.x = mask.b.x + x;

		m_dn[idx2].xy.y = mask.c.y + y;
		m_dn[idx2].xy.x = mask.c.x + x;

		m_dn[idx3].xy.y = mask.d.y + y;
		m_dn[idx3].xy.x = mask.d.x + x;
	} // //////////////////////////////////////////////////////////////////////////////////
}; // *************************************************************************************
class ProcT0 : private ProcTable {
private:
	av2 m_dn;
	avc2 m_up;
public:
	ProcT0(const avc2& vUpIn, const av2& vDnOut)
		: m_up(vUpIn), m_dn(vDnOut) {}
	void operator()(index<2> idx) const restrict(amp) {
		auto idxY = 2 * idx[0];
		auto idxX = 2 * idx[1];
		auto idx0 = index<2>(idxY, idxX);
		auto idx1 = index<2>(idxY, idxX + 1);
		auto idx2 = index<2>(idxY + 1, idxX);
		auto idx3 = index<2>(idxY + 1, idxX + 1);

		vtype* e = &m_dn[idx0];
		if(e->a & mskExist) {
			//auto z = concurrency::fast_math::log10(2.);
			auto dirx = e->xy.x;
			auto diry = e->xy.y;

			if(e->a & mskIntent) {

			}
		}

		int iv =
			(m_dn[idx0].a & mskExist) +
			(m_dn[idx1].a * 2 & mskExist) +
			(m_dn[idx2].a * 4 & mskExist) +
			(m_dn[idx3].a * 8 & mskExist);
		YX4 mask = v[iv];

		m_dn[idx0].xy.y = mask.a.y;
		m_dn[idx0].xy.x = mask.a.x;

		m_dn[idx1].xy.y = mask.b.y;
		m_dn[idx1].xy.x = mask.b.x;

		m_dn[idx2].xy.y = mask.c.y;
		m_dn[idx2].xy.x = mask.c.x;

		m_dn[idx3].xy.y = mask.d.y;
		m_dn[idx3].xy.x = mask.d.x;
	} // //////////////////////////////////////////////////////////////////////////////////
}; // *************************************************************************************

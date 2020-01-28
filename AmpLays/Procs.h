#pragma once
#include "AmpLays.h"
using namespace concurrency;
class ProcA {
private:
	array_view<const vtype, 1> m_dn;
	array_view<vtype, 1> m_up;
	int szx;
public:
	ProcA(const array_view<const vtype, 1>& vDnIn,
		const array_view<vtype, 1>& vUpOut,
		int szx_dn)
		: m_dn(vDnIn),
		m_up(vUpOut),
		szx(szx_dn) {}
	void operator()(index<1> idx) const restrict(amp) {
		index<1> j = (((2 * idx) / szx) * szx) * 2 + (2 * idx) % szx;
		m_up[idx] = m_dn[j] + m_dn[j + 1] + m_dn[j + szx] + m_dn[j + szx + 1] > 1 ? 1 : 0;
	} // //////////////////////////////////////////////////////////////////////////////////
}; // *************************************************************************************

class ProcA0 {
private:
	array_view<const vtype, 1> m_dn;
	array_view<vtype, 1> m_up;
	int szx;
public:
	ProcA0(const array_view<const vtype, 1>& vDnIn,
		const array_view<vtype, 1>& vUpOut,
		int szx_dn)
		: m_dn(vDnIn),
		m_up(vUpOut),
		szx(szx_dn) {}
	void operator()(index<1> idx) const restrict(amp) {
		index<1> j = (((2 * idx) / szx) * szx) * 2 + (2 * idx) % szx;
		m_up[idx] = m_dn[j] + m_dn[j + 1] + m_dn[j + szx] + m_dn[j + szx + 1] > 1 ? 1 : 0;
	} // //////////////////////////////////////////////////////////////////////////////////
}; // *************************************************************************************

class ProcA2 {
private:
	array_view<const vtype, 2> m_dn;
	array_view<vtype, 2> m_up;
public:
	ProcA2(const array_view<const vtype, 2>& vDnIn,
		const array_view<vtype, 2>& vUpOut)
		: m_dn(vDnIn), m_up(vUpOut) {}
	void operator()(index<2> idx) const restrict(amp) {
		auto y = 2 * idx[0];
		auto x = 2 * idx[1];
		auto tmp =
			m_dn[index<2>(y, x)] +
			m_dn[index<2>(y + 1, x)] +
			m_dn[index<2>(y, 2 * x + 1)] +
			m_dn[index<2>(y + 1, x + 1)];
		m_up[idx] = tmp > 1 ? 1 : 0;
	} // //////////////////////////////////////////////////////////////////////////////////
}; // *************************************************************************************

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

class ProcAn {
private:
	array_view<const vtype, 1> m_dn;
	array_view<vtype, 1> m_up;
public:
	ProcAn(const array_view<const vtype, 1>& vDnIn,
		const array_view<vtype, 1>& vUpOut)
		: m_dn(vDnIn),
		m_up(vUpOut)
	{}
	void operator()(index<1> idx) const restrict(amp) {
		auto sz = m_dn.extent.size();
		index<1> j = (((2 * idx) / sz) * sz) * 2 + (2 * idx) % sz;
		m_up[idx] = m_dn[j] + m_dn[j + 1] + m_dn[j + sz] + m_dn[j + sz + 1] > 1 ? 1 : 0;
	} // //////////////////////////////////////////////////////////////////////////////////
}; // *************************************************************************************


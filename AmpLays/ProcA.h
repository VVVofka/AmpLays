#pragma once
#include "AmpLays.h"
using namespace concurrency;
class ProcA {
private:
    array_view<const vtype, 2> m_mA;
    array_view<vtype, 2> m_mC;
    int m_W;
public:
    ProcA(const array_view<const vtype, 2>& a,
        const array_view<vtype, 2>& c,
        int w) : m_mA(a), 
        m_mC(c), 
        m_W(w) {}
    void operator()(index<2> idx) const restrict(amp) {
        int row = idx[0]; int col = idx[1];
        vtype sum = 0.0f;
        for(int i = 0; i < m_W; i++)
            sum += m_mA(row, i); 
        m_mC[idx] = sum;
    }
};

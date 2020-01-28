#pragma once
#include "LayBase.h"
class LayLast :	public LayBase{
public:
	LayLast() {}
	LayLast(int szy, int szx) {
		v = new concurrency::array_view<vtype, 2>(szy, szx);
	} // ////////////////////////////////////////////////////////////////////////////////////
}; // ***************************************************************************


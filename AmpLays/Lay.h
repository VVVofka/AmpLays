#pragma once
#include "LayBase.h"
class Lay : public LayBase{
public:
	Lay(int szy, int szx) {
		v = new concurrency::array_view<vtype, 2>(szy, szx);
	} // ////////////////////////////////////////////////////////////////////////////////////
}; // ***************************************************************************************


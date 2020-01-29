#pragma once
#include "LayBase.h"
class LayLast :	public LayBase{
public:
	LayLast() {}
	LayLast(int szy, int szx) {
		v = new av2(szy, szx);
	} // ////////////////////////////////////////////////////////////////////////////////////
}; // ***************************************************************************


#pragma once
#include "LayBase.h"
class LayLast :	public LayBase{
public:
	LayLast() {}
	LayLast(int sz_x, int sz_y) {
		szx = sz_x;
		szy = sz_y;
		sz = szx * szy;
		v = new av(szx * szy);
	} // ////////////////////////////////////////////////////////////////////////////////////

}; // ***************************************************************************


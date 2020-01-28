#pragma once
#include "LayBase.h"
class Lay : public LayBase{
public:
	Lay* layDn = nullptr;

	Lay(Lay* lay_Dn, Lay* lay_Up = nullptr) {
		layDn = lay_Dn;
		szx = layDn->szx / 2;
		szy = layDn->szy / 2;
		sz = szx * szy;
		v = new av((szx + 1) * (szy + 1));
		layUp = lay_Up;
	} // ////////////////////////////////////////////////////////////////////////////////////
}; // ***************************************************************************************


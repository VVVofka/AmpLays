#include "AmpLays.h"
#include "Procs.h"
#include "Lays.h"
//https://professorweb.ru/my/csharp/optimization/level4/4_6.php
//https://docs.microsoft.com/ru-ru/cpp/parallel/amp/cpp-amp-overview?view=vs-2017
//C1001: Project property-> C/C++ -> All options -> Additional options -> /Zc:twoPhase- %(AdditionalOptions)
// _CONSOLE
void CppAmpMethod0() {
	std::vector<int> vBaseI{{
			0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1,
			1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0,
			0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
			0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1,
			0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0,
			0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1,
			1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1
		}};
	std::vector<vtype> vBase(vBaseI.size());
	for (int i = 0; i < vBaseI.size(); i++)
		vBase[i].a = vBaseI[i];
	int szy = 8, szx = 16;
	Lays lays(szy, szx, vBase); // main init
	lays.lay0.dumpall();
	assert(lays.size() > 3);
	lays.runShift();

	parallel_for_each(lays.v(1)->extent, ProcA(lays.getShiftV(), *lays.v(1)));	// TODO: shift remove
	for(int nlay = 2; nlay < lays.size(); nlay++) {
		LayBase* prev = lays[nlay - 1];
		LayBase* cur = lays[nlay];
		//_RPT5(0, "%d  %d*%d %d*%d\n", n, prev->szy(), prev->szx(), cur->szy(), cur->szx());
		parallel_for_each(cur->v->extent, ProcA(*prev->v, *cur->v));
	}
	lays.dump();

	int nprevlast = int(lays.size()) - 2;
	parallel_for_each(lays.laylast.v->extent, ProcTLast(*lays.laylast.v, *lays.v(nprevlast)));
	for (int nlay = nprevlast; nlay > 1; nlay--) {
		LayBase* cur = lays[nlay];
		LayBase* next = lays[nlay - 1];
		parallel_for_each(cur->v->extent, ProcT(*cur->v, *next->v));
	}
	parallel_for_each(lays[1]->v->extent, ProcT0(*lays[1]->v, lays.getShiftV()));
	// TODO: mover here 
	lays.dumpYX();
} // //////////////////////////////////////////////////////////////////////////
void CppAmpMethod1() {
	//std::vector<vtype> vBase{ {
	//		0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	//		1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0,
	//		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1,
	//		1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0,
	//		0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
	//		0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1,
	//		0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0,
	//		0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1,
	//		1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1
	//	} };
	//Lays lays(16, 8, &vBase);
	//for (int n = 1; n < lays.size(); n++) {
	//	LayBase* prev = lays[n - 1];
	//	LayBase* cur = lays[n];
	//	_RPT5(0, "%d  %d*%d %d*%d\n", n, prev->szy, prev->szx, cur->szy, cur->szx);
	//	//parallel_for_each(lays(n)->extent, ProcA2(prev, cur, lays[n - 1]->szx));
	//	parallel_for_each(lays(n)->extent, ProcA(*lays(n - 1), *lays(n), lays[n - 1]->szx));
	//}
	//lays.dump();
} // //////////////////////////////////////////////////////////////////////////////////
int main() {
	CppAmpMethod0();
	std::cout << "Hello World!\n";
	return 0 * getchar();
} // ///////////////////////////////////////////////////////////////////////////////////
void dumpV(const std::vector<vtype> v, int szy, int szx) {
	for(int y = 0; y < szy; y++) {
		std::cout << std::endl;
		for(int x = 0; x < szx; x++) {
			std::cout << " " << (v[y * szx + x].a & 1);
		}
	}
	std::cout << std::endl;
} // ///////////////////////////////////////////////////////////////////////////////////
void dumpv(const vtype* v, int szy, int szx) {
	for(int y = 0; y < szy; y++) {
		std::cout << std::endl;
		for(int x = 0; x < szx; x++) {
			std::cout << " " << (v[y * szx + x].a & 1);
		}
	}
	std::cout << std::endl;
} // ///////////////////////////////////////////////////////////////////////////////////
void dumpv(const av2& v) {
	std::cout << "    " << v.extent[0] << " x " << v.extent[1];
	for(int y = 0; y < v.extent[0]; y++) {
		std::cout << std::endl;
		for(int x = 0; x < v.extent[1]; x++) {
			vtype tmp = v(y, x);
			std::cout << " " << (tmp.a & 1);
		}
	}
	std::cout << std::endl;
} // ///////////////////////////////////////////////////////////////////////////////////

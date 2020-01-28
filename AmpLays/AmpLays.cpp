#include "AmpLays.h"
#include "Procs.h"
#include "Lays.h"
//https://professorweb.ru/my/csharp/optimization/level4/4_6.php
//https://docs.microsoft.com/ru-ru/cpp/parallel/amp/cpp-amp-overview?view=vs-2017
//C1001: Project property-> C/C++ -> All options -> Additional options -> /Zc:twoPhase- %(AdditionalOptions)
// _CONSOLE
void CppAmpMethod0() {
	std::vector<vtype> vBase{{
			0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
			1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1,
			1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0,
			0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
			0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1,
			0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0,
			0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1,
			1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1
		}};
	int szy = 8, szx = 16;
	Lays lays(szy, szx, vBase);
	parallel_for_each(lays(1)->extent, ProcA2(lays.lay0.Shift(), *lays(1)));
	for(int n = 2; n < lays.size(); n++) {
		LayBase* prev = lays[n - 1];
		LayBase* cur = lays[n];
		//_RPT5(0, "%d  %d*%d %d*%d\n", n, prev->szy(), prev->szx(), cur->szy(), cur->szx());
		parallel_for_each(lays(n)->extent, ProcA2(*prev->v, *cur->v));
	}
	lays.dump();
} // //////////////////////////////////////////////////////////////////////////
void CppAmpMethod1() {
	//std::vector<vtype> vBase{ {
	//		0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
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
			std::cout << " " << v[y * szx + x];
		}
	}
	std::cout << std::endl;
} // ///////////////////////////////////////////////////////////////////////////////////
void dumpv(const vtype* v, int szy, int szx) {
	for(int y = 0; y < szy; y++) {
		std::cout << std::endl;
		for(int x = 0; x < szx; x++) {
			std::cout << " " << v[y * szx + x];
		}
	}
	std::cout << std::endl;
} // ///////////////////////////////////////////////////////////////////////////////////
void dumpv(const concurrency::array_view<vtype, 2>& v) {
	std::cout << "    " << v.extent[0] << " x " << v.extent[1];
	for(int y = 0; y < v.extent[0]; y++) {
		std::cout << std::endl;
		for(int x = 0; x < v.extent[1]; x++) {
			vtype tmp = v(y, x);
			std::cout << " " << tmp;
		}
	}
	std::cout << std::endl;
} // ///////////////////////////////////////////////////////////////////////////////////

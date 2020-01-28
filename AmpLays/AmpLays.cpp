#include "AmpLays.h"
#include "Procs.h"
#include "Lays.h"
//https://professorweb.ru/my/csharp/optimization/level4/4_6.php
//https://docs.microsoft.com/ru-ru/cpp/parallel/amp/cpp-amp-overview?view=vs-2017
//C1001: Project property-> C/C++ -> All options -> Additional options -> /Zc:twoPhase- %(AdditionalOptions)
// _CONSOLE
void CppAmpMethod1() {
	std::vector<vtype> vBase4{{
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
	Lays lays(16, 8, &vBase4);
	for(int n = 1; n < lays.size(); n++) {
		LayBase* prev = lays[n - 1];
		LayBase* cur = lays[n];
		_RPT5(0, "%d  %d*%d %d*%d\n", n, prev->szx, prev->szy, cur->szx, cur->szy);
		parallel_for_each(lays(n)->extent, ProcA(*lays(n - 1), *lays(n), lays[n - 1]->szx));
	}
	lays.dump();
} // //////////////////////////////////////////////////////////////////////////////////
int main() {
	CppAmpMethod1();
	std::cout << "Hello World!\n";
	return 0 * getchar();
} // ///////////////////////////////////////////////////////////////////////////////////
void dumpV(const std::vector<vtype> v, int szx, int szy) {
	for(int y = 0; y < szy; y++) {
		std::cout << std::endl;
		for(int x = 0; x < szx; x++) {
			std::cout << " " << v[y * szx + x];
		}
	}
	std::cout << std::endl;
} // ///////////////////////////////////////////////////////////////////////////////////
void dumpv(const vtype* v, int szx, int szy) {
	for(int y = 0; y < szy; y++) {
		std::cout << std::endl;
		for(int x = 0; x < szx; x++) {
			std::cout << " " << v[y * szx + x];
		}
	}
	std::cout << std::endl;
} // ///////////////////////////////////////////////////////////////////////////////////


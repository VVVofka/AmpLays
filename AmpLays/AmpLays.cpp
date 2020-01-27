#include "AmpLays.h"
#include "Procs.h"
#include "Lays.h"

using namespace concurrency;
using namespace std;
//https://professorweb.ru/my/csharp/optimization/level4/4_6.php
//https://docs.microsoft.com/ru-ru/cpp/parallel/amp/cpp-amp-overview?view=vs-2017
//C1001: Project property-> C/C++ -> All options -> Additional options -> /Zc:twoPhase- %(AdditionalOptions)
// _CONSOLE
void CppAmpMethod1() {
	const int szx0 = 2, szy0 = 1;
	const int szx1 = 2 * szx0, szy1 = 2 * szy0;
	const int szx2 = 2 * szx1, szy2 = 2 * szy1;
	vtype vBase1[szx2 * szy2] = {};
	vtype vBase2[szx2 * szy2] = {
		1, 0, 0, 0, 0, 0, 1, 0,
		0, 1, 1, 0, 0, 1, 1, 0,
		0, 1, 0, 0, 0, 0, 1, 0,
		0, 0, 0, 0, 0, 0, 1, 1
	};
	array_view<const vtype, 2> v2(szy2, szx2, vBase2);
	array_view<vtype, 2> v1(szy2, szx2, vBase1);
	v1.discard_data();

	parallel_for_each(v1.extent.tile<2, 2>(), [=](tiled_index<2, 2> idx) restrict(amp) {
		tile_static vtype nums[2][2];
		nums[idx.local[1]][idx.local[0]] = v2[idx.global];
		idx.barrier.wait();
		auto sum = nums[0][0] + nums[0][1] + nums[1][0] + nums[1][1];
		v1[idx.global] = (sum >= 2) ? 1 : 0;
		});
	v1.synchronize();

	for (int i = 0; i < szy2; i++) {
		for (int j = 0; j < szx2; j++) {
			std::cout << v1(i, j) << " ";
		}
		std::cout << "\n";
	}
} // //////////////////////////////////////////////////////////////////////////////////
void CppAmpMethod2() {
	const int szx1 = 2, szy1 = 1, sz1 = szx1 * szy1;	// 2 1 2
	const int szx2 = szx1 * 2, szy2 = szy1 * 2, sz2 = szx2 * szy2;  // 4   2  8
	int szx3 = szx2 * 2, szy3 = szy2 * 2, sz3 = szx3 * szy3;	// 8   4  32
	int szx4 = szx3 * 2, szy4 = szy3 * 2, sz4 = szx4 * szy4;	// 16  8  128
	vector<vtype> vBase4{ {
			0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0,
			1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1,
			1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0,
			0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
			0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0,
			0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1,
			0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 } };
	vector<vtype> vBase3(sz3);
	vector<vtype> vBase2(sz2);
	vector<vtype> vBase1(sz1);
	dumpV(vBase4, szx4, szy4);

	array_view<const vtype, 1> v4(sz4, vBase4);
	array_view<vtype, 1> v3(sz3, vBase3);	v3.discard_data();
	array_view<vtype, 1> v2(sz2, vBase2);	v2.discard_data();
	array_view<vtype, 1> v1(sz1, vBase1);	v1.discard_data();
	//for(int i = 0; i < vBase3.size(); i++) {
	//	int y = ((2 * i / szx4) * szx4) * 2;
	//	int x = (2 * i) % szx4;
	//	vBase3[i] = vBase4[y + x] + vBase4[y + x + 1] + vBase4[y + x + szx4] + vBase4[y + x + szx4 + 1];// > 1 ? 1 : 0;
	//	cout << i << " y:" << y << " x:" << x << " x+y:" << y + x << " x+y+1:" <<y + x + 1<<" y+x+szx4:"<< y + x + szx4<< " y+x+szx4+1:"<< y + x + szx4 + 1<< endl;
	//}
	//dumpV(vBase3, szx3, szy3);
	//parallel_for_each(v3.extent, [=](index<1> i) restrict(amp) {
	//	index<1> y = (((2 * i) / szx4) * szx4) * 2;
	//	index<1> x = (2 * i) % szx4;
	//	index<1> j = y + x;
	//	v3[i] = v4[j] + v4[j + 1] + v4[j + szx4] + v4[j + szx4 + 1] > 1 ? 1 : 0;
	//});
	parallel_for_each(v3.extent, ProcA(v4, v3, szx4));
	parallel_for_each(v2.extent, ProcA(v3, v2, szx3));
	parallel_for_each(v1.extent, ProcA(v2, v1, szx2));
	dumpv(v3.data(), szx3, szy3);
	dumpv(v2.data(), szx2, szy2);
	dumpv(v1.data(), szx1, szy1);
} // //////////////////////////////////////////////////////////////////////////////////
void CppAmpMethod3() {
	int szx0 = 16, szy0 = 8, sz0 = szx0 * szy0;	// 16  8  128
	vector<vtype> vBase4{ {
			0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0,
			1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1,
			1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0,
			0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
			0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0,
			0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1,
			0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 } };
	dumpV(vBase4, szx0, szy0);
	vector<array_view<vtype, 1>*> vav(4);
	vector<int> vx(4);	// длины рядов х
	vav[0] = new array_view<vtype, 1>(sz0, vBase4);
	vx[0] = szx0;
	for (int n = 1; n < vav.size(); n++) {
		auto prevsz = vav[n - 1]->extent.size();
		auto newsz = prevsz / 4;
		assert(newsz > 0);
		vav[n] = new array_view<vtype, 1>(newsz);
		assert(vx[n - 1] / 2 > 0);
		vx[n] = vx[n - 1] / 2;
	}
	for (int n = 1; n < vav.size(); n++) {
		parallel_for_each(vav[n]->extent, ProcA(*vav[n - 1], *vav[n], vx[n - 1]));
	}
	for (int n = 0, x = szx0, y = szy0; n < vav.size(); n++, x /= 2, y /= 2) {
		dumpv(vav[n]->data(), x, y);
	}
} // //////////////////////////////////////////////////////////////////////////////////
void CppAmpMethod4() {
	//int szx0 = 16, szy0 = 8, sz0 = szx0 * szy0;	// 16  8  128
	//vector<vtype> vBase4{ {
	//		0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0,
	//		1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0,
	//		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1,
	//		1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0,
	//		0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
	//		0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0,
	//		0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1,
	//		0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 } };
	//dumpV(vBase4, szx0, szy0);
	//vector<Lay> vlays(4);
	//vlays[0].Create0(szx0, szy0, &vBase4);
	//for (int n = 1; n < vlays.size(); n++) {
	//	Lay* uplay = n + 1 < vlays.size() ? &vlays[n + 1] : nullptr;
	//	vlays[n].Create(&vlays[n - 1], uplay);
	//}
	//for (int n = 1; n < vlays.size(); n++) {
	//	parallel_for_each(vlays[n].v->extent, ProcA(*vlays[n - 1].v, *vlays[n].v, vlays[n - 1].szx));
	//}
	//for (int n = 0; n < vlays.size(); n++) {
	//	vlays[n].dump();
	//	delete vlays[n].v;
	//}
} // //////////////////////////////////////////////////////////////////////////////////
void CppAmpMethod5() {
	vector<vtype> vBase4{ {
			0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0,
			1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1,
			1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0,
			0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
			0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0,
			0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1,
			0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 } };
	Lays lays(16, 8, &vBase4);
	for (int n = 1; n < lays.size(); n++) {
		parallel_for_each(lays(n)->extent, ProcA(*lays(n - 1), *lays(n), lays[n - 1]->szx));
	}
	for (int n = 0; n < lays.size(); n++) {
		lays[n]->dump();
		delete lays(n);
	}
} // //////////////////////////////////////////////////////////////////////////////////
int main() {
	CppAmpMethod5();
	std::cout << "Hello World!\n";
	return 0;// *getchar();
} // ///////////////////////////////////////////////////////////////////////////////////
void dumpV(const vector<vtype> v, int szx, int szy) {
	for (int y = 0; y < szy; y++) {
		cout << endl;
		for (int x = 0; x < szx; x++) {
			cout << " " << v[y * szx + x];
		}
	}
	cout << endl;
} // ///////////////////////////////////////////////////////////////////////////////////
void dumpv(const vtype* v, int szx, int szy) {
	for (int y = 0; y < szy; y++) {
		cout << endl;
		for (int x = 0; x < szx; x++) {
			cout << " " << v[y * szx + x];
		}
	}
	cout << endl;
} // ///////////////////////////////////////////////////////////////////////////////////


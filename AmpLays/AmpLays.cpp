#include "AmpLays.h"
#include "Procs.h"
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

	for(int i = 0; i < szy2; i++) {
		for(int j = 0; j < szx2; j++) {
			std::cout << v1(i, j) << " ";
		}
		std::cout << "\n";
	}
} // //////////////////////////////////////////////////////////////////////////////////
//void CppAmpMethod1() {
//	const int szx1 = 2, szy1 = 1, sz1 = szx1 * szy1;	// 2 1 2
//	const int szx2 = szx1 * 2, szy2 = szy1 * 2, sz2 = szx2 * szy2; // 4 2 8
//	const int szx3 = szx2 * 2, szy3 = szy2 * 2, sz3 = szx3 * szy3;	// 8 4 32
//	vtype vBase3a[sz3] = {
//		0, 0, 0, 1, 0, 0, 1, 0,
//		0, 0, 0, 0, 0, 1, 0, 0,
//		0, 0, 1, 0, 0, 1, 0, 0,
//		0, 0, 0, 0, 0, 1, 1, 0
//	};
//	vtype vBase3b[sz3] = {
//		1, 1, 0, 1, 0, 0, 0, 0,
//		0, 0, 0, 0, 0, 1, 1, 1,
//		0, 1, 0, 1, 0, 0, 0, 0,
//		1, 0, 1, 1, 0, 0, 1, 1
//	};
//	vtype vBase3c[sz3] = {
//		1, 0, 0, 1, 0, 0, 1, 1,
//		1, 1, 1, 1, 0, 1, 0, 0,
//		0, 1, 0, 1, 1, 0, 1, 0,
//		0, 1, 1, 0, 0, 0, 1, 1
//	};
//	vtype vBase3d[sz3] = {
//		0, 0, 0, 1, 1, 0, 0, 0,
//		0, 1, 0, 0, 0, 1, 1, 0,
//		1, 1, 1, 0, 0, 0, 1, 0,
//		0, 0, 0, 1, 1, 0, 0, 0
//	};
//	vtype vItem3[sz3] = {};
//
//	vtype vBase2a[sz2] = {};
//	vtype vBase2b[sz2] = {};
//	vtype vBase2c[sz2] = {};
//	vtype vBase2d[sz2] = {};
//	vtype vItem2[sz2] = {};
//
//	vtype vBase1a[sz1] = {};
//	vtype vBase1b[sz1] = {};
//	vtype vBase1c[sz1] = {};
//	vtype vBase1d[sz1] = {};
//	vtype vItem1[sz1] = {};
//
//	array_view<vtype, 1> v3a(sz3, vBase3a);
//	array_view<vtype, 1> v3b(sz3, vBase3b);
//	array_view<vtype, 1> v3c(sz3, vBase3c);
//	array_view<vtype, 1> v3d(sz3, vBase3d);
//	array_view<vtype, 1> v3i(sz3, vItem3);
//
//	array_view<vtype, 1> v2a(sz2, vBase2a); v2a.discard_data();
//	array_view<vtype, 1> v2b(sz2, vBase2b); v2b.discard_data();
//	array_view<vtype, 1> v2c(sz2, vBase2c); v2c.discard_data();
//	array_view<vtype, 1> v2d(sz2, vBase2d); v2d.discard_data();
//	array_view<vtype, 1> v2i(sz2, vItem2); v2i.discard_data();
//
//	array_view<vtype, 1> v1a(sz1, vBase1a); v1a.discard_data();
//	array_view<vtype, 1> v1b(sz1, vBase1b); v1b.discard_data();
//	array_view<vtype, 1> v1c(sz1, vBase1c); v1c.discard_data();
//	array_view<vtype, 1> v1d(sz1, vBase1d); v1d.discard_data();
//	array_view<vtype, 1> v1i(sz1, vItem1); v1i.discard_data();
//
//	for(int y = 0; y < szy3; y++) {
//		std::cout << "\n";
//		int y0 = y * szx3;
//		for(int x = 0; x < szx3; x++) {
//			int i = y0 + x;
//			std::cout << " " << v3a[i] << " " << v3b[i] << " ";
//		}
//		std::cout << "\n";
//		for(int x = 0; x < szx3; x++) {
//			int i = y0 + x;
//			std::cout << " " << v3c[i] << " " << v3d[i] << " ";
//		}
//		std::cout << "\n";
//	}
//
//
//	parallel_for_each(v3i.extent, [=](index<1> i) restrict(amp) {
//		v3i[i] = v3a[i] + v3b[i] + v3c[i] + v3d[i] > 1 ? 1 : 0;
//	});
//	for(int y = 0; y < szy3; y++) {
//		int y0 = y * szx3;
//		for(int x = 0; x < szx3; x++) {
//			int i = y0 + x;
//			std::cout << "  " << v3i[i] << "  ";
//		}
//		std::cout << "\n";
//	}
//
//	array_view< vtype, 2> v3iq(szy3, szx3, v3i); // const
//	//int i = 0;
//	//for(int y = 0; y < szy3; y += 2) {
//	//	int y0 = y * szx3 * 2;
//	//	for(int x = 0; x < szx3; x += 2) {
//	//		v2a[i] = v3iq(y, x);
//	//		v2b[i] = v3iq(y, x+1);
//	//		v2c[i] = v3iq(y+szx3, x);
//	//		v2d[i++] = v3iq(y + szx3, x+1);
//	//	}
//	//}
//	//parallel_for_each(v2i.extent, [=](index<1> i) restrict(amp) {
//	//	v2i[i] = v2a[i] + v2b[i] + v2c[i] + v2d[i] > 1 ? 1 : 0;
//	//});
//	//for(int y = 0; y < szy2; y++) {
//	//	int y0 = y * szx2;
//	//	for(int x = 0; x < szx2; x++) {
//	//		int i = y0 + x;
//	//		std::cout << "  " << v2i[i] << "  ";
//	//	}
//	//	std::cout << "\n";
//	//}
//
//	//parallel_for_each(v3iq.extent.tile<2, 2>(), [=](tiled_index<2, 2> idx) restrict(amp) {
//	//	tile_static vtype nums[2][2];
//	//	nums[idx.local[1]][idx.local[0]] = v3iq[idx.global];
//	//	idx.barrier.wait();
//	//	int sum = nums[0][0] + nums[0][1] + nums[1][0] + nums[1][1];
//	//	//v1[idx.global] = (sum >= 2) ? 1 : 0;
//	//});
//
//	//parallel_for_each(v2a.extent, [=](index<1> i) restrict(amp) {
//	//	auto z = i * 4;
//	//	v2a[i] = v3i[i * 4];
//	//	v2b[i] = v3i[i * 4 + 1];
//	//	v2c[i] = v3i[i * 4 + 2];
//	//	v2d[i] = v3i[i * 4 + 3];
//	//});
//	for(int y = 0; y < szy2; y++) {
//		std::cout << "\n";
//		int y0 = y * szx2;
//		for(int x = 0; x < szx2; x++) {
//			int i = y0 + x;
//			std::cout << " " << v2a[i] << " " << v2b[i] << " ";
//		}
//		std::cout << "\n";
//		for(int x = 0; x < szx2; x++) {
//			int i = y0 + x;
//			std::cout << " " << v2c[i] << " " << v2d[i] << " ";
//		}
//		std::cout << "\n";
//	}
//} // //////////////////////////////////////////////////////////////////////////////////

#include "Lay.h"
void CppAmpMethod2() {
	const int szx1 = 2, szy1 = 1, sz1 = szx1 * szy1;	// 2 1 2
	const int szx2 = szx1 * 2, szy2 = szy1 * 2, sz2 = szx2 * szy2;  // 4   2  8
	int szx3 = szx2 * 2, szy3 = szy2 * 2, sz3 = szx3 * szy3;	// 8   4  32
	int szx4 = szx3 * 2, szy4 = szy3 * 2, sz4 = szx4 * szy4;	// 16  8  128
	vector<vtype> vBase4{{
			0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0,
			1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1,
			1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0,
			0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
			0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0,
			0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1,
			0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0}};
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
	vector<vtype> vBase4{{
			0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0,
			1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1,
			1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0,
			0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
			0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0,
			0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1,
			0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0}};
	dumpV(vBase4, szx0, szy0);
	vector<array_view<vtype, 1>*> vav(4);
	vector<int> vx(4);
	vav[0] = new array_view<vtype, 1>(sz0, vBase4);
	vx[0] = szx0;
	for(int n = 1; n < vav.size(); n++) {
		auto prevsz = vav[n-1]->extent.size();
		auto newsz = prevsz / 4;
		assert(newsz > 0);
		vav[n] = new array_view<vtype, 1>(newsz);
		vx[n] = vx[n - 1] / 2;
	}
	for(int n = 1; n < vav.size(); n++) {
		parallel_for_each(vav[n]->extent, ProcA(*vav[n-1], *vav[n], vx[n-1]));
	}
	for(int n = 0, x = szx0, y = szy0; n < vav.size(); n++, x /=2, y/=2) {
		dumpv(vav[n]->data(), x, y);
	}
} // //////////////////////////////////////////////////////////////////////////////////
int main() {
	CppAmpMethod3();
	std::cout << "Hello World!\n";
	return 0*getchar();
} // ///////////////////////////////////////////////////////////////////////////////////
void dumpV(const vector<vtype> v, int szx, int szy) {
	for(int y = 0; y < szy; y++) {
		cout << endl;
		for(int x = 0; x < szx; x++) {
			cout << " " << v[y * szx + x];
		}
	}
	cout << endl;
} // ///////////////////////////////////////////////////////////////////////////////////
void dumpv(const vtype* v, int szx, int szy) {
	for(int y = 0; y < szy; y++) {
		cout << endl;
		for(int x = 0; x < szx; x++) {
			cout << " " << v[y * szx + x];
		}
	}
	cout << endl;
} // ///////////////////////////////////////////////////////////////////////////////////


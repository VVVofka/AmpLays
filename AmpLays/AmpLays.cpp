#include "AmpLays.h"
#include "Procs.h"
using namespace std;
//https://professorweb.ru/my/csharp/optimization/level4/4_6.php
//https://docs.microsoft.com/ru-ru/cpp/parallel/amp/cpp-amp-overview?view=vs-2017
//C1001: Project property-> C/C++ -> All options -> Additional options -> /Zc:twoPhase- %(AdditionalOptions)
// _CONSOLE
using namespace concurrency;
void CppAmpMethod() {
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
void CppAmpMethod2() {
	const int szx1 = 2, szy1 = 1, sz1 = szx1 * szy1;	// 2 1 2
	const int szx2 = szx1 * 2, szy2 = szy1 * 2, sz2 = szx2 * szy2;  // 4   2  8
	const int szx3 = szx2 * 2, szy3 = szy2 * 2, sz3 = szx3 * szy3;	// 8   4  32
	const int szx4 = szx3 * 2, szy4 = szy3 * 2, sz4 = szx4 * szy4;	// 16  8  128
	vtype vBase3a[sz3] = {
		0, 0, 0, 1, 0, 0, 1, 0,
		0, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 1, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 0
	};
	vtype vBase3b[sz3] = {
		1, 1, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 1,
		0, 1, 0, 1, 0, 0, 0, 0,
		1, 0, 1, 1, 0, 0, 1, 1
	};
	vtype vBase3c[sz3] = {
		1, 0, 0, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 0, 1, 0, 0,
		0, 1, 0, 1, 1, 0, 1, 0,
		0, 1, 1, 0, 0, 0, 1, 1
	};
	vtype vBase3d[sz3] = {
		0, 0, 0, 1, 1, 0, 0, 0,
		0, 1, 0, 0, 0, 1, 1, 0,
		1, 1, 1, 0, 0, 0, 1, 0,
		0, 0, 0, 1, 1, 0, 0, 0
	};
	vector<vtype> vBase4(sz4);
	vector<vtype> vBase3(sz3);
	vector<vtype> vBase2(sz2);
	vector<vtype> vBase1(sz1);
	for(int y = 0, i = 0; y < szy4; y += 2) {
		int y0 = y * szx4;
		for(int x = 0; x < szx4; x += 2) {
			vBase4[y0 + x] = vBase3a[i];
			vBase4[y0 + x + 1] = vBase3b[i];
			vBase4[y0 + szx4 + x] = vBase3c[i];
			vBase4[y0 + szx4 + x + 1] = vBase3d[i++];
		}
	}
	//dumpV(vBase3a, szx3, szy3);
	//dumpV(vBase3b, szx3, szy3);
	//dumpV(vBase3c, szx3, szy3);
	//dumpV(vBase3d, szx3, szy3);
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
	v3.synchronize();
	v2.synchronize();
	v1.synchronize();
	dumpV(vBase3, szx3, szy3);
	dumpV(vBase2, szx2, szy2);
	dumpV(vBase1, szx1, szy1);

	//array_view< vtype, 2> v3iq(szy3, szx3, v3i); // const
	////int i = 0;
	////for(int y = 0; y < szy3; y += 2) {
	////	int y0 = y * szx3 * 2;
	////	for(int x = 0; x < szx3; x += 2) {
	////		v2a[i] = v3iq(y, x);
	////		v2b[i] = v3iq(y, x+1);
	////		v2c[i] = v3iq(y+szx3, x);
	////		v2d[i++] = v3iq(y + szx3, x+1);
	////	}
	////}
	////parallel_for_each(v2i.extent, [=](index<1> i) restrict(amp) {
	////	v2i[i] = v2a[i] + v2b[i] + v2c[i] + v2d[i] > 1 ? 1 : 0;
	////});
	////for(int y = 0; y < szy2; y++) {
	////	int y0 = y * szx2;
	////	for(int x = 0; x < szx2; x++) {
	////		int i = y0 + x;
	////		std::cout << "  " << v2i[i] << "  ";
	////	}
	////	std::cout << "\n";
	////}

	////parallel_for_each(v3iq.extent.tile<2, 2>(), [=](tiled_index<2, 2> idx) restrict(amp) {
	////	tile_static vtype nums[2][2];
	////	nums[idx.local[1]][idx.local[0]] = v3iq[idx.global];
	////	idx.barrier.wait();
	////	int sum = nums[0][0] + nums[0][1] + nums[1][0] + nums[1][1];
	////	//v1[idx.global] = (sum >= 2) ? 1 : 0;
	////});

	////parallel_for_each(v2a.extent, [=](index<1> i) restrict(amp) {
	////	auto z = i * 4;
	////	v2a[i] = v3i[i * 4];
	////	v2b[i] = v3i[i * 4 + 1];
	////	v2c[i] = v3i[i * 4 + 2];
	////	v2d[i] = v3i[i * 4 + 3];
	////});
	//for(int y = 0; y < szy2; y++) {
	//	std::cout << "\n";
	//	int y0 = y * szx2;
	//	for(int x = 0; x < szx2; x++) {
	//		int i = y0 + x;
	//		std::cout << " " << v2a[i] << " " << v2b[i] << " ";
	//	}
	//	std::cout << "\n";
	//	for(int x = 0; x < szx2; x++) {
	//		int i = y0 + x;
	//		std::cout << " " << v2c[i] << " " << v2d[i] << " ";
	//	}
	//	std::cout << "\n";
	//}
} // //////////////////////////////////////////////////////////////////////////////////
int main() {
	//void CppAmpMethod();	CppAmpMethod();
	void CppAmpMethod2();	CppAmpMethod2();
	std::cout << "Hello World!\n";
	return getchar();
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
void dumpV(const vtype* v, int szx, int szy) {
	for(int y = 0; y < szy; y++) {
		cout << endl;
		for(int x = 0; x < szx; x++) {
			cout << " " << v[y * szx + x];
		}
	}
	cout << endl;
} // ///////////////////////////////////////////////////////////////////////////////////


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

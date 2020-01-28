#pragma once
#include <random>
//using namespace std;
// не повторять текущее и предыдущее значения
class Shifter {
	std::mt19937 gen;
	int v[4] = {0, 0b1011, 0b0111, 0b0110};
	int prevChanges = 3;	// 1,2,3
	int state = 0;			// 0,1,2,3
public:
	Shifter() {
		//std::random_device rd;   // non-deterministic generator
		//std::mt19937 gen(rd());  
		gen.seed(20210);
	} // ////////////////////////////////////////////////////////////////////
	int x() { return state & 1; }
	int y() { return (state >> 1) & 1; }
	// ////////////////////////////////////////////////////////////////////
	void Run() {
		static std::uniform_int_distribution<int> dst(0, 1);
		auto tmp = v[prevChanges];
		if(dst(gen) == 0)
			tmp >>= 2;
		else
			tmp &= 0b11;
		prevChanges ^= tmp;
		state ^= prevChanges;
	} // ////////////////////////////////////////////////////////////////////
	void dump() {
		std::cout << "shift_y:" << y() << " shift_x:" << x() << std::endl;
	} // ////////////////////////////////////////////////////////////////////
}; // ***************************************************************************


#pragma once
#define INTEND(Y, X) ()
//  +----->x
//  | 0 1
//  | 2 3
// y|
//  V

// bit=0: -1 or disable
// bit=1: +1 or enable

// bit 7: intendY value
// bit 6: intendY enable
// bit 5: intendX value
// bit 4: intendX enable
// bit 3: moveY value
// bit 2: moveY enable
// bit 1: moveX value
// bit 0: moveX enable
typedef unsigned __int32 typeMoveIntend;
typeMoveIntend vMoveIntend[16] = {};
void fillvMoveIntend() {
	auto p = vMoveIntend;
	// \   /  \   /		;
	//	O O    # #		;
	//  O O    # #		;
	// /   \  /   \		;
	p[0b0000] = p[0b1111] = intend( -1,-1,  1,-1,
									-1, 1,  1, 1);

	//	#   O    0   #	  0 > O    0 < 0		;
	//      v    v            ^    ^			;
	//  O > O    0 < 0	  #   O    0   #		;
	p[0b0001] = move1(+0, +1) | move2(+1, +0);
	p[0b0010] = move0(+0, +1) | move3(-1, +0);
	p[0b0100] = move0(+1, +0) | move3(+0, -1);
	p[0b1000] = move1(-1, +0) | move2(+0, -1);

	//               \       /  
	//	#   #     #   0	    0   #      0   0		;
	// \     /                        /     \		;
	//  O   O     #   0	    0   #      #   #		;
	//               /       \						;
	p[0b0011] = intend2(-1, -1) | intend3(+1, -1);
	p[0b0101] = intend1(-1, -1) | intend3(-1, +1);
	p[0b1010] = intend0(+1, -1) | intend2(+1, +1);
	p[0b1100] = intend0(-1, +1) | intend1(+1, +1);

	//	#   0      0   #	    ;
	//     /        \			;
	//   /            \			;           
	//  O   #      #   0	    ;
	p[0b1001] = move1(-1, +1) | move2(+1, -1);
	p[0b0110] = move0(+1, +1) | move3(-1, -1);

	//      /  \       \            /
	//	#  #    #  #    #  0    0  #	;
	//   \        / 	  /		 \		;
	//    \      /  	 /		  \		;           
	//  #  0    0  #    #  #    #  #	;
	// /		    \		\  /		;
	p[0b0111] = p[0b1110] = move0(+1, +1) | intend1(+1, -1) | intend2(-1, +1) | move3(-1, -1);
	p[0b1011] = p[0b1101] = intend0(-1, -1) | move1(-1, +1) | move2(+1, -1) | intend3(+1, +1);
}
typeMoveIntend uni(int x, int y) {
	typeMoveIntend ret = 0;
	if (y != 0) {
		if (y > 0)
			ret = 0b1100;
		else
			ret = 0b0100;
	}
	if (x != 0) {
		if (x > 0)
			ret |= 0b0011;
		else
			ret |= 0b0001;
	}
	return ret;
} // ///////////////////////////////////////////////////////
typeMoveIntend intend(int x, int y) {
	return uni(x, y) << 4;
} // ////////////////////////////////////////////////////////////////////////////
typeMoveIntend intend(  int x0, int y0,		int x1, int y1,
						int x2, int y2,		int x3, int y3) {
	typeMoveIntend ret = intend(x3, y3);
	ret = (ret << 8) | intend(x2, y2);
	ret = (ret << 8) | intend(x1, y1);
	ret = (ret << 8) | intend(x0, y0);
	return ret;
} // ////////////////////////////////////////////////////////////////////////////
typeMoveIntend move(int x, int y) {
	return uni(x, y);
} // ////////////////////////////////////////////////////////////////////////////

typeMoveIntend move0(int x, int y) {
	return move(x, y);
} // ////////////////////////////////////////////////////////////////////////////
typeMoveIntend move1(int x, int y) {
	return move(x, y) << 8;
} // ////////////////////////////////////////////////////////////////////////////
typeMoveIntend move2(int x, int y) {
	return move(x, y) << 16;
} // ////////////////////////////////////////////////////////////////////////////
typeMoveIntend move3(int x, int y) {
	return move(x, y) << 24;
} // ////////////////////////////////////////////////////////////////////////////

typeMoveIntend intend0(int x, int y) {
	return intend(x, y);
} // ////////////////////////////////////////////////////////////////////////////
typeMoveIntend intend1(int x, int y) {
	return intend(x, y) << 8;
} // ////////////////////////////////////////////////////////////////////////////
typeMoveIntend intend2(int x, int y) {
	return intend(x, y) << 16;
} // ////////////////////////////////////////////////////////////////////////////
typeMoveIntend intend3(int x, int y) {
	return intend(x, y) << 24;
} // ////////////////////////////////////////////////////////////////////////////



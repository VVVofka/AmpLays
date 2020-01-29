#pragma once
typedef int typexy;
class XY {
public:
	typexy y, x;
	XY() { y = 0, x = 0; }
	XY(typexy new_y, typexy new_x) { y = new_y, x = new_x; }
	void operator +=(const XY& z) { y += z.y, x += z.x; }
	XY operator +(const XY& z) { return XY(y + z.y, x + z.x); }
}; // *************************************************************


#pragma once
class YX {
public:
	int y, x;
	YX() { y = 0, x = 0; }
//	YX(int new_y, int new_x) { y = new_y, x = new_x; }
//	void operator +=(YX& z) { y += z.y, x += z.x; }
}; // *************************************************************

class YX4 {
public:
	YX a, b, c, d;
	YX4(int ay, int ax,
		int by, int bx,
		int cy, int cx,
		int dy, int dx) {
		a.x = ax, a.y = ay;
		b.x = bx, b.y = by;
		c.x = cx, c.y = cy;
		d.x = dx, d.y = dy;
	}
}; // *************************************************************

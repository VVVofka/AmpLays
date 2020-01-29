#pragma once
typedef int typexy;
class YX {
public:
	typexy y, x;
	YX() { y = 0, x = 0; }
	YX(typexy new_y, typexy new_x) { y = new_y, x = new_x; }
	void operator +=(YX& z) { y += z.y, x += z.x; }
	YX operator +(const YX& z) { return YX(y + z.y, x + z.x); }
	void add(const YX* q) { y += q->y, x += q->x; }
}; // *************************************************************

class YX4 {
public:
	YX a, b, c, d;
	YX4(typexy ay, typexy ax,
		typexy by, typexy bx,
		typexy cy, typexy cx,
		typexy dy, typexy dx) {
		a.x = ax, a.y = ay;
		b.x = bx, b.y = by;
		c.x = cx, c.y = cy;
		d.x = dx, d.y = dy;
	}
}; // *************************************************************

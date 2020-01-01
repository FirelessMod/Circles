#pragma once
#include <math.h>

class Point {
private:
public:
	int x = 0;
	int y = 0;
	Point() { x = y = 0; }
	Point(int xi, int yi) { x = xi; y = yi; }
	int getX() { return x; }
	int getY() { return y; }
	bool operator == (Point c) {
		if (c.x == x && c.y == y) 
			return true;
		
		return false;
	}
	bool operator != (Point c) {
		if (c.x != x || c.y != y) 
			return true;
		
		return false;
	}
	Point operator - (Point p1) {
		Point new_point; 
		new_point.x = x - p1.x;
		new_point.y = y - p1.y;
	}
	double distance(const Point& p2) { return hypot(double(p2.x-x), double(p2.y-y)); }
};


#pragma once
#include "Point.h"
#include <stdio.h>
#include "mywindow.h"


class Image;

class Circle {

private:
	int x = 0;
	int y = 0;

public:
	Point c; 
	int color = 0;
	std::vector<Circle> l;
	int v = 0;

	Circle(int value, int colour, Point center, std::vector<Circle> layer) {
		v = value;  
		color = colour; 
		c = center;
		l = layer;
	}

	Circle(); 

	~Circle();
	
	void drawOnImage(Image& img, std::vector <Circle>& C, int i, int recolor);
	
	bool contains(Point& p); 
	
	void OpenFile(std::vector<Circle>& C);
	
	void Path(std::vector<Circle>& path, Image& img);
};


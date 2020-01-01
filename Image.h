#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "font8x.h"
#include <vector>
#define BLACK 0
#define WHITE 255
#define GRAY 100
class Circle;
class Image{
private:
	int n_lines, n_columns, color;
	int** mat;
	void allocMat(int nl, int nc);
	void deallocMat();
public:
	
	Image();
	
	Image(int nl, int nc, int bg_color);
	
	Image(Image& orig);
	
	~Image();
	
	Image& operator= (const Image& orig);
	
	bool isValid() const { return (n_lines > 0 && n_columns > 0 && mat != NULL); }
	
	int getNLines() const { return n_lines; }
	
	int getNColumns() const { return n_columns; }
	
	int getPixel(int l, int c) const { return mat[l][c]; }
	
	void setPixel(int l, int c, int p) { mat[l][c] = p; }
	
	void drawLine(int x1, int y1, int x2, int y2, int c);
	
	void drawText(int x, int y, int col, const char* text); 
	
	void drawNumber(int x, int y, int col, int number);
	
	void Assign(std::vector<Circle>& C);
	
	void AssignLines(std::vector<Circle>& C);

};

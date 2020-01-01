#define _CRT_SECURE_NO_WARNINGS
#include "Image.h"
#include "Circle.h"
#include "font8x.h"
#include <stdio.h>
void Image::allocMat(int nl, int nc){
	n_lines = nl, n_columns = nc;
	mat = new int* [n_lines];
	for (int i = 0; i < n_lines; i++)
		mat[i] = new int[n_columns];
}

void Image::deallocMat(){
	if (mat == NULL)
	{
		return;
	}
	for (int i = 0; i < n_lines; i++)
	{
		delete[] mat[i];
	}
	delete[]mat;
}

Image::Image(){
	n_columns = 0;
	n_lines = 0;
	color = 0;
	mat = NULL;
}

Image::Image(int nl, int nc, int bg_color){
	allocMat(nl, nc);
	color = bg_color;
}

Image::Image(Image& orig){
	allocMat(orig.n_lines, orig.n_columns);
	for (int i = 0; i < n_lines; i++){
		for (int j = 0; j < n_columns; j++){
			mat[i][j] = orig.mat[i][j];
		}
	}
}

Image::~Image(){
	deallocMat();
}

Image& Image::operator=(const Image& orig)
{
	{
		deallocMat();

		allocMat(orig.n_lines, orig.n_columns);

		for (int i = 0; i < n_lines; i++)
		{
			for (int j = 0; j < n_columns; j++)
			{
				mat[i][j] = orig.mat[i][j];
			}
		}
		return*this;
	}
}

void Image::drawLine(int x1, int y1, int x2, int y2, int c) {
	HDC hdc = GetDC(GetConsoleWindow());
	int cx, cy;
	int dx = (x2 - x1);
	int dy = (y2 - y1);
	float n;
	float dx1 = 0.0;
	float dy1 = 0.0;
	if (abs(dx) <= abs(dy)) { n = abs(dy); }
	else { n = abs(dx); }
	if (dx != 0) { dx1 = dx / n; }
	if (dy != 0) { dy1 = dy / n; }
	for (int x = 0; x <= n; x++) {
		cx = x1 + (x * dx1);
		cy = y1 + (x * dy1);
		setPixel(cy, cx, RGB(c, c, c));
	}
}

void Image::drawText(int x, int y, int col, const char* text) {
	for (int chr = 0; text[chr] != '\0'; ++chr) {
		unsigned char glyph = text[chr];
		for (int cy = 0; cy < 16; ++cy) {
			unsigned char l = font_data[glyph][cy];
			for (int cx = 0; cx < 8; ++cx) {
				if ((l & 0x80) && // bit 7 == 1
					x + cx >= 0 && x + cx < n_columns && y + cy >= 0 && y + cy <= n_lines) mat[y + cy][x + cx] = col;
				l <<= 1;
			}
		}
		x += 8;
	}
}

void Image::drawNumber(int x, int y, int col, int number) {
	char str[20];
	sprintf_s(str, "%d", number);
	drawText(x - strlen(str) * 4, y - 8, col, str);
}

void Image::Assign(std::vector<Circle>& C) {
	std::vector <Circle> l;
	C[0].l.insert(std::end(C[0].l),		{ C[0] });//25
	C[1].l.insert(std::end(C[1].l),		{ C[0], C[1] });//15
	C[2].l.insert(std::end(C[2].l),		{ C[0], C[2] });//35
	C[3].l.insert(std::end(C[3].l),		{ C[0], C[1],	C[3] });//10
	C[4].l.insert(std::end(C[4].l),		{ C[0], C[1],	C[4] });//20
	C[5].l.insert(std::end(C[5].l),		{ C[0], C[2],	C[5] });//31
	C[6].l.insert(std::end(C[6].l),		{ C[0], C[2],	C[6] });//40
	C[7].l.insert(std::end(C[7].l),		{ C[0], C[1],	C[3],	C[7]	});//8
	C[8].l.insert(std::end(C[8].l),		{ C[0], C[1],	C[3],	C[8]	});//13
	C[9].l.insert(std::end(C[9].l),		{ C[0], C[1],	C[4],	C[9]	});//18
	C[10].l.insert(std::end(C[10].l),	{ C[0], C[1],	C[4],	C[10]	});//21
	C[11].l.insert(std::end(C[11].l),	{ C[0], C[2],	C[5],	C[11]	});//28
	C[12].l.insert(std::end(C[12].l),	{ C[0], C[2],	C[5],	C[12]	});//33
	C[13].l.insert(std::end(C[13].l),	{ C[0], C[2],	C[6],	C[13]	});//38
	C[14].l.insert(std::end(C[14].l),	{ C[0], C[2],	C[6],	C[14]	});//45
	C[15].l.insert(std::end(C[15].l),	{ C[0], C[1],	C[3],	C[8],	C[15]	});//11
	C[16].l.insert(std::end(C[16].l),	{ C[0], C[1],	C[3],	C[8],	C[16] });//14
	C[17].l.insert(std::end(C[17].l),	{ C[0], C[1],	C[4],	C[10],	C[17] });//24
	C[18].l.insert(std::end(C[18].l),	{ C[0], C[2],	C[5],	C[12],	C[18] });//32
	C[19].l.insert(std::end(C[19].l),	{ C[0], C[2],	C[5],	C[12],	C[19] });//34
}

void Image::AssignLines(std::vector<Circle>& C) {
	
	drawLine(C[0].c.x, C[0].c.y, C[1].c.x, C[1].c.y, 0);
	drawLine(C[1].c.x, C[1].c.y, C[3].c.x, C[3].c.y, 0);
	drawLine(C[1].c.x, C[1].c.y, C[4].c.x, C[4].c.y, 0);
	drawLine(C[3].c.x, C[3].c.y, C[7].c.x, C[7].c.y, 0);
	drawLine(C[3].c.x, C[3].c.y, C[8].c.x, C[8].c.y, 0);
	drawLine(C[4].c.x, C[4].c.y, C[9].c.x, C[9].c.y, 0);
	drawLine(C[4].c.x, C[4].c.y, C[10].c.x, C[10].c.y, 0);
	drawLine(C[8].c.x, C[8].c.y, C[15].c.x, C[15].c.y, 0);
	drawLine(C[8].c.x, C[8].c.y, C[16].c.x, C[16].c.y, 0);
	drawLine(C[10].c.x, C[10].c.y, C[17].c.x, C[17].c.y, 0);
	drawLine(C[0].c.x, C[0].c.y, C[2].c.x, C[2].c.y, 0);
	drawLine(C[2].c.x, C[2].c.y, C[5].c.x, C[5].c.y, 0);
	drawLine(C[2].c.x, C[2].c.y, C[6].c.x, C[6].c.y, 0);
	drawLine(C[5].c.x, C[5].c.y, C[11].c.x, C[11].c.y, 0);
	drawLine(C[5].c.x, C[6].c.y, C[12].c.x, C[12].c.y, 0);
	drawLine(C[6].c.x, C[6].c.y, C[13].c.x, C[14].c.y, 0);
	drawLine(C[6].c.x, C[6].c.y, C[14].c.x, C[14].c.y, 0);
	drawLine(C[12].c.x, C[12].c.y, C[18].c.x, C[18].c.y, 0);
	drawLine(C[12].c.x, C[12].c.y, C[19].c.x, C[19].c.y, 0);
}

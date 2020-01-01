#define _CRT_SECURE_NO_WARNINGS
#include "Circle.h"
#include <fstream>
#include <sstream>


Circle::Circle() {}

Circle::~Circle(){}

void Circle::drawOnImage(Image& img, std::vector <Circle>& C, int i, int recolor) {
	
	int linhas = img.getNLines();
	int colunas = img.getNColumns();
	int inverse = 200;
	contains(C[i].c);
	if (recolor == 1) { 	
		C[i].color = C[i].color + 200; inverse = 50;	
	}
	
	if (recolor == 0) {		
		C[i].color = 50; inverse = 200;		
	}

	if (C[i].color < 0 || C[i].color > 255) {		
		C[i].color = 50; inverse = 200;		
	}
	
	for (float j = 0; j <= 5 * 3.1415 * 30; j++) {
		for (float d = 0; d <= 7 * 30; d++) {
			float v = cos(j) * d / 8;
			float h = sin(j) * d / 8;
			float cy = y + v;
			float cx = x + h;
			int cxa = int(cx);
			int cya = int(cy);
			if (cya >= 0 && cya < linhas && cxa >= 0 && cxa < colunas) {
				img.setPixel(cya, cxa, C[i].color);
				img.drawNumber(C[i].c.x, C[i].c.y, inverse, C[i].v);
			}
		}
	}
}

bool Circle::contains(Point& p) {

	y = p.getY();
	x = p.getX();
	return false;
}

void Circle::OpenFile(std::vector<Circle>& C) {

	static int array[100];
	std::ifstream infile;
	std::string line;
	int j = 0;
	Point p;
	int value;
	char path[50] = "c:\\";
	char Directory[10];
	char FileName[10];
	char retake = 'n'; 
	do {
		std::cout << "Qual a pasta em que est" << char(160) << " guardado o ficheiro?" << std::endl;
		std::cin >> Directory;
		std::cout << "Qual o nome do ficheiro?" << std::endl;
		std::cin >> FileName;
		std::cout << "Deseja reintroduzir o nome da pasta ou do ficheiro? (N ou S)"<< std::endl;
		std::cin >> retake; 
	} while (retake != 'n' && retake != 'N');
	strcat(path, Directory);
	strcat(path, "\\");
	strcat(path, FileName);
	strcat(path, ".txt");
	infile.open(path, std::ifstream::in);
	if (!infile) {
		std::cout << std::endl << "Nao foi possivel abrir o ficheiro!" << std::endl;
		exit(1);
	}
	if (infile.is_open()) {
		while (!infile.eof()) {
			std::getline(infile, line, ',');
			std::stringstream stream(line);
			while (1) {
				stream >> array[j];
				if (!stream)
					break;
				j++;
			}
		}
	}
	int Nnos = array[0];
	for (int i = 0; i < Nnos; i++) {
		p = Point(array[1 + i * 3], array[2 + i * 3]);
		value = array[3 + i * 3];
		C.emplace_back(value, 50, p, l);
	}
}

void Circle::Path(std::vector<Circle>& path, Image& img) {
	
	std::vector<Circle> end;
	int finder = 0;
	int common = 0;
	for (int i = path[0].l.size()-1; i > 0; i--) {
		for (int j = path[1].l.size()-1; j > 0; j--) {
			if (path[0].l[i].c == path[1].l[j].c && common == 0) {
				finder = i;
				common++;
				break;
			}
		}
	}
	for (size_t i = finder; i < path[0].l.size(); i++) {
		end.emplace_back(path[0].l[i].v, 50, path[0].l[i].c, l);
		if(i < path[0].l.size() - 1) {
			img.drawLine(path[0].l[i].c.x, path[0].l[i].c.y, path[0].l[i + 1].c.x, path[0].l[i + 1].c.y, 255);
		}
		for (size_t j = finder; j < path[1].l.size(); j++) {
			end.emplace_back(path[1].l[j].v, 50, path[1].l[j].c, l);
			if(j < path[1].l.size() - 1) {
				img.drawLine(path[1].l[j].c.x, path[1].l[j].c.y, path[1].l[j + 1].c.x, path[1].l[j + 1].c.y, 255);
			}
		}
	}
	for (size_t i = 0; i < end.size(); i++) {
		drawOnImage(img, end, i, 1);
	}	
end.clear();
}

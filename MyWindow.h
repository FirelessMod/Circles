#pragma once
#include<windows.h>
#include <gl/glu.h>
#include<stdio.h>
#include"Point.h"
#include "Image.h"

#pragma comment (lib, "opengl32.lib")

class MyWindow
{
private:
	HWND windowId;

	Point cur_coord;

	bool clicked;

	static MyWindow* object; // static object used in the CALLBACK function

	static MyWindow* GetObject();
public:

	MyWindow();

	~MyWindow() { };

	bool Create(const char* sTitulo, int width, int height);

	static LRESULT CALLBACK ProcessMessages(HWND winId, unsigned int msg, WPARAM wp, LPARAM lp);

	HWND GetId() { return windowId; }

	bool Click() { return clicked; }

	Point ObterPonto() { return cur_coord; }

	void redrawImage(Image& im);


};


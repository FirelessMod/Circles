#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Image.h"
#include "mywindow.h"
#include "Point.h"
#include "Circle.h"
#include "font8x.h"

#pragma comment (lib, "opengl32.lib")


int main(){
	MyWindow window;
	HWND windowId;
	Image img(600, 800, 0);
	Circle circ;
	Point p;
	bool found = false;
	std::vector<Circle> C;
	circ.OpenFile(C);
	img.AssignLines(C);
	img.Assign(C); 
	std::vector<Circle> path;
	for (int i = 0; i < C.size(); i++) 
		circ.drawOnImage(img, C, i, 0);
	
	printf("This program uses another window to show the image.\n");
	if (window.Create("Ficha 5", img.getNColumns(), img.getNLines())) {
		if ((windowId = window.GetId()) != NULL) {	
			MSG msg;
			while (GetMessage(&msg, 0, 0, 0)){
				DispatchMessage(&msg);
				if (window.Click()){
					found = false;
					p = window.ObterPonto();
					for (int i = 0; i < C.size(); i++) {
						circ.contains(C[i].c);
						if ((p.distance(C[i].c) <= 30)){
							found = true;
							circ.drawOnImage(img, C, i, 1);
							path.emplace_back(C[i]);
							if (path.size() == 2) 		
								circ.Path(path,img);	
							
							if (path.size() > 2) 
								goto path;
							
						}		
					}	
					if (found == false) {	path:
					img.AssignLines(C);
						for (int i = 0; i < C.size(); i++) {
							if (C[i].color != 0) {
								C[i].color = 0;
								path.clear();
								circ.drawOnImage(img, C, i, 0);	
							}
						}
					}
				}
				window.redrawImage(img);
			}
		}
	}
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow){
	
	MSG msg;
	HWND hwnd;
	WNDCLASSW wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = L"WINDOW";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassW(&wc);
	hwnd = CreateWindowW(L"WINDOW", L"Janela",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 600, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0)) 
		DispatchMessage(&msg);
	
	return (int)msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam){
	switch (msg){
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

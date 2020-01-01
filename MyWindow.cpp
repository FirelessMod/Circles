#include "MyWindow.h"


MyWindow* MyWindow::object = NULL;	

MyWindow::MyWindow(){
	windowId = NULL;
	object = this;		
	clicked = false;
}

MyWindow* MyWindow::GetObject(){
	return object;
}

bool MyWindow::Create(const char* sTitle, int width, int height){
	const char class_name[] = "myclass"; 

	WNDCLASSEX wndclass = {
		sizeof(WNDCLASSEX),
		CS_DBLCLKS,
		ProcessMessages,	
		0, 0,
		GetModuleHandle(0),
		LoadIcon(0,IDI_APPLICATION),
		LoadCursor(0,IDC_ARROW),
		HBRUSH(CTLCOLOR_STATIC + 1),0,
		class_name,
		LoadIcon(0,IDI_APPLICATION)
	};

	if (RegisterClassEx(&wndclass)) { 
		RECT r = { 0, 0, width, height };
		AdjustWindowRectEx(&r, WS_OVERLAPPEDWINDOW, false, 0);

		windowId = CreateWindowEx(  
			0, class_name,
			sTitle,			
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 
			r.right - r.left, r.bottom - r.top, 
			0, 0,
			GetModuleHandle(0), 0
		);
		if (windowId) {
			ShowWindow(windowId, SW_SHOWDEFAULT); 
			return true;
		}
	}
	return false;
}

LRESULT CALLBACK MyWindow::ProcessMessages(HWND janId, unsigned int msg, WPARAM wp, LPARAM lp)
{
	MyWindow* window = GetObject();
	window->clicked = false;

	switch (msg) {
	case WM_CREATE:
	{
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0,
			PFD_MAIN_PLANE,
			0,0, 0, 0
		};

		HDC hDC = GetDC(janId);
		int pf = ChoosePixelFormat(hDC, &pfd);
		SetPixelFormat(hDC, pf, &pfd);
		HGLRC glDC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, glDC);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		if (wp == VK_ESCAPE) {
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_LBUTTONDOWN:
		window->clicked = true;
		window->cur_coord = Point(LOWORD(lp), HIWORD(lp));
		break;
	default: break;
	}
	return DefWindowProc(janId, msg, wp, lp);
}

void MyWindow::redrawImage(Image& img){

	unsigned char* img_data =
		new unsigned char[img.getNLines() * img.getNColumns()];

	int idx = 0;
	for (int l = img.getNLines() - 1; l >= 0; --l) {
		for (int c = 0; c < img.getNColumns(); ++c) {
			img_data[idx++] = (unsigned char)img.getPixel(l, c);
		}
	}

	glDrawPixels(img.getNColumns(), img.getNLines(),
		GL_LUMINANCE, GL_UNSIGNED_BYTE, (void*)img_data);

	delete[] img_data;
	SwapBuffers(GetDC(windowId));
}

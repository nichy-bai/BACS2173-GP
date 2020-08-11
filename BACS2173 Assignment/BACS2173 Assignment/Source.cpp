#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "BACS2173 Assignment"

double rotateX = 0.0, rotateY = 0.0;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
		}
		else if (wParam == VK_LEFT) {
			rotateX += 10;
		}
		else if (wParam == VK_RIGHT) {
			rotateX -= 10;
		}
		else if (wParam == VK_DOWN) {
			rotateY -= 10;
		}
		else if (wParam == VK_UP) {
			rotateY += 10;
		}

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void drawCuboid(double r, double g, double b, double x, double y, double z, double dx, double dy, double w) {
	glColor3f(r, g, b);

	//Face 1: Front
	glBegin(GL_LINE_LOOP);
		glVertex3f(x-dx, y+dy, z);
		glVertex3f(x-dx, y-dy, z);
		glVertex3f(x+dx, y-dy, z);
		glVertex3f(x+dx, y+dy, z);
	glEnd();

	//Face 2: Right
	glBegin(GL_LINE_LOOP);
		glVertex3f(x+dx, y+dy, z);
		glVertex3f(x+dx, y-dy, z);
		glVertex3f(x+dx, y-dy, z+w);
		glVertex3f(x+dx, y+dy, z+w);
	glEnd();

	//Face 3: Rear
	glBegin(GL_LINE_LOOP);
		glVertex3f(x+dx, y+dy, z+w);
		glVertex3f(x+dx, y-dy, z+w);
		glVertex3f(x-dx, y-dy, z+w);
		glVertex3f(x-dx, y+dy, z+w);
	glEnd();

	//Face 4: Top
	glBegin(GL_LINE_LOOP);
		glVertex3f(x-dx, y+dy, z+w);
		glVertex3f(x+dx, y+dy, z+w);
		glVertex3f(x+dx, y+dy, z);
		glVertex3f(x-dx, y+dy, z);
	glEnd();

	//Face 5: Left
	glBegin(GL_LINE_LOOP);
		glVertex3f(x-dx, y+dy, z);
		glVertex3f(x-dx, y+dy, z+w);
		glVertex3f(x-dx, y-dy, z+w);
		glVertex3f(x-dx, y-dy, z);
	glEnd();

	//Face 6: Bottom
	glBegin(GL_LINE_LOOP);
		glVertex3f(x-dx, y-dy, z);
		glVertex3f(x-dx, y-dy, z+w);
		glVertex3f(x+dx, y-dy, z+w);
		glVertex3f(x+dx, y-dy, z);
	glEnd();
}

void Head() {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	
	//Sphere
	glColor3f(0.47, 0.471, 0.47);
	gluSphere(sphere, 0.2, 200, 200);

	////Top
	//glPushMatrix();
	//glTranslatef(0, 0.175, 0);
	//glRotatef(45, 0, 0, 1);
	//glTranslatef(-0, -0.175, 0);
	//drawCuboid(0.84, 0.831, 0.815, 0, 0.175, -0.25, 0.15, 0.15, 0.3);
	//glPopMatrix();

	////Bottom Left
	//glPushMatrix();
	//glTranslatef(-0.2, 0, 0);
	//glRotatef(45, 0, 0, 1);
	//glTranslatef(0.2, -0, 0);
	//drawCuboid(0.84, 0.831, 0.815, -0.2, -0.05, -0.25, 0.08, 0.05, 0.1);
	//glPopMatrix();

	////Bottom Left
	//glPushMatrix();
	//glTranslatef(0.2, 0, 0);
	//glRotatef(315, 0, 0, 1);
	//glTranslatef(-0.2, -0, 0);
	//drawCuboid(0.84, 0.831, 0.815, 0.2, -0.05, -0.25, 0.08, 0.12, 0.1);
	//glPopMatrix();

	//Bottom
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(45, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0, -0, 0);
	drawCuboid(0.84, 0.831, 0.815, 0, 0, -0.25, 0.15, 0.15, 0.2);
	glPopMatrix();
}

void display()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(rotateX, 0.0, 1.0, 0.0);
	glRotatef(rotateY, 1.0, 0.0, 0.0);
	Head();

	glPopMatrix();
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------
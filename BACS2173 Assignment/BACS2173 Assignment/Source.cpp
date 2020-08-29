#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "BACS2173 Assignment" //Nicholas Lee Hong Quan & Lee Jia Shin
#define GLU_LINE 100011
#define GLU_FILL 100012
#define GLU_POINT 100013

float tZ = 0.0, tSpeed = 1.0, rY = 0.0, rX = 0.0, rSpeed = 3.0;
bool isOrtho = true;

float amb[] = { 0.0, 0.0, 1.0 }; //Ambient light
float posA[] = { 0.0, 1.0, 0.0 }; //Position for ambient

float dif[] = { 0.0, 1.0, 0.0 }; //Diffuse light
float posD[] = { 1.0, 1.0, 0.0 }; //Position for diffuse

float ambM[] = { 1.0, 0.0, 0.0 }; //Ambient material
float difM[] = { 1.0, 0.0, 0.0 }; //Diffuse material

bool isLightOn = false;

BITMAP BMP;				//Bitmap structure
HBITMAP hBMP = NULL;	//Bitmap handle

float speed = 0.1;

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
			rY += rSpeed;
		}
		else if (wParam == VK_RIGHT) {
			rY -= rSpeed;
		}
		else if (wParam == VK_DOWN) {
			rX -= rSpeed;
		}
		else if (wParam == VK_UP) {
			rX += rSpeed;
		}
		else if (wParam == VK_SPACE) {
			rX = 0.0;
			rY = 0.0;
			tZ = 0.0;
		}
		else if (wParam == 'O') { //Change to Orthographic
			isOrtho = true;
			tZ = 0.0;
			rY = 0.0;
		}
		else if (wParam == 'P') { //Change to Perspective
			isOrtho = false;
			tZ = 4.0;
			rY = 0.0;
		}
		else if (wParam == 'U') { //Zoom out
			if (isOrtho) {
				if (tZ < 8.0) {
					tZ += tSpeed;
				}
			}
			else {
				if (tZ < 14.0) {
					tZ += tSpeed;
				}
			}
		}
		else if (wParam == 'I') { //Zoom in
			if (isOrtho) {
				if (tZ > -8.0) {
					tZ -= tSpeed;
				}
			}
			else {
				if (tZ > 4.0) {
					tZ -= tSpeed;
				}
			}
		}
		else if (wParam == 'L') {
			isLightOn = !isLightOn;
		}
		break;

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

void drawCuboid(float r, float g, float b, float x, float y, float z, float dx, float dy, float w) {
	glColor3f(r, g, b);

	//Face 1: Front
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x - dx, y + dy, z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x - dx, y - dy, z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + dx, y - dy, z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + dx, y + dy, z);
	glEnd();

	//Face 2: Right
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x + dx, y + dy, z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + dx, y - dy, z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + dx, y - dy, z + w);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + dx, y + dy, z + w);
	glEnd();

	//Face 3: Rear
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x + dx, y + dy, z + w);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + dx, y - dy, z + w);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x - dx, y - dy, z + w);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x - dx, y + dy, z + w);
	glEnd();

	//Face 4: Top
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x - dx, y + dy, z + w);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + dx, y + dy, z + w);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + dx, y + dy, z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x - dx, y + dy, z);
	glEnd();

	//Face 5: Left
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x - dx, y + dy, z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x - dx, y + dy, z + w);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x - dx, y - dy, z + w);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x - dx, y - dy, z);
	glEnd();

	//Face 6: Bottom
	glBegin(GL_LINE_LOOP);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x - dx, y - dy, z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x - dx, y - dy, z + w);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + dx, y - dy, z + w);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + dx, y - dy, z);
	glEnd();
}

void drawPyramid(float r, float g, float b, float x, float y, float z, float dx, float dy, float w) {
	glColor3f(r, g, b);

	//Face 1 : Front
	glBegin(GL_LINE_LOOP); //Change to triangle
		glVertex3f(x, y+dy, z+(w/2));
		glVertex3f(x-dx, y-dy, z);
		glVertex3f(x+dx, y-dy, z);
	glEnd();

	//Face 2 : Right
	glBegin(GL_LINE_LOOP);
		glVertex3f(x, y+dy, z+(w/2));
		glVertex3f(x+dx, y-dy, z);
		glVertex3f(x+dx, y-dy, z+w);
	glEnd();

	//Face 3 : Rear
	glBegin(GL_LINE_LOOP);
		glVertex3f(x, y+dy, z+(w/2));
		glVertex3f(x+dx, y-dy, z+w);
		glVertex3f(x-dx, y-dy, z+w);
	glEnd();

	//Face 4 : Left
	glBegin(GL_LINE_LOOP);
		glVertex3f(x, y+dy, z+(w/2));
		glVertex3f(x-dx, y-dy, z+w);
		glVertex3f(x-dx, y-dy, z);
	glEnd();

	//Face 5 : Bottom
	glBegin(GL_LINE_LOOP);
		glVertex3f(x-dx, y-dy, z);
		glVertex3f(x+dx, y-dy, z);
		glVertex3f(x+dx, y-dy, z+w);
		glVertex3f(x-dx, y-dy, -z+w);
	glEnd();
}

void drawSphere(float r, float g, float b, float x, float y, float z, float radius, int type) {
	GLUquadricObj* sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, type);
	glColor3f(r, g, b);

	glPushMatrix();
	glTranslatef(x, y, z);
	gluSphere(sphere, radius, 50, 50);
	glPopMatrix();
	gluDeleteQuadric(sphere);
}

void drawCylinder(float r, float g, float b, float x, float y, float z, float baseR, float topR, float height, int type) {
	GLUquadricObj* cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, type);
	glColor3f(r, g, b);

	glPushMatrix();
	glTranslatef(x, y, z);
	gluCylinder(cylinder, baseR, topR, height, 50, 50);
	glPopMatrix();
	gluDeleteQuadric(cylinder);
}

void projection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glRotatef(rX, 1.0, 0.0, 0.0);
	glRotatef(rY, 0.0, 1.0, 0.0);

	if (isOrtho) { //Orthographic
		glOrtho(-8.0, 8.0, -8.0, 8.0, -8.0, 8.0);
	}
	else { //Perspective
		gluPerspective(16.0, 1.0, -1.0, 1.0);
		glFrustum(-8.0, 8.0, -8.0, 8.0, 1.0, 17.0);
	}
}

void lighting() {
	if (isLightOn) {
		glEnable(GL_LIGHTING);
	}
	else {
		glDisable(GL_LIGHTING);
	}

	//Light 0 
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_POSITION, posA);
	glEnable(GL_LIGHT0);

	//Light 1
	glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT1, GL_POSITION, posD);
	glEnable(GL_LIGHT1);
}

GLuint skyBox(LPCSTR fileName) {
	GLuint texture = 0;		//Texture name

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		fileName, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);

	return texture;
}

void head() {
	//Sphere
	//drawSphere(0.47, 0.471, 0.47, 0.0, 0.0, 0.0, 0.2, GL_LINE);

	//Eye
	glPushMatrix();
	glTranslatef(0.07, -0.02, 0);
	glRotatef(-10, 1, 0, 0);
	glRotatef(45, 0, 1, 0);
	glTranslatef(-0.07, 0.02, 0);
	drawCuboid(0, 1, 0, 0.07, -0.02, -0.25, 0.15, 0.02, 0.30);
	glPopMatrix();

	//Top
	glPushMatrix();
	glTranslatef(0.14, 0.08, 0);
	glRotatef(-10, 1, 0, 0);
	glRotatef(45, 0, 1, 0);
	glTranslatef(-0.14, -0.08, 0);
	drawCuboid(0.84, 0.831, 0.815, 0.14, 0.08, -0.35, 0.15, 0.08, 0.30);
	glPopMatrix();

	//Bottom
	glPushMatrix();
	glTranslatef(0.07, -0.12, 0);
	glRotatef(-10, 1, 0, 0);
	glRotatef(45, 0, 1, 0);
	glTranslatef(-0.07, 0.12, 0);
	drawCuboid(0.84, 0.831, 0.815, 0.07, -0.12, -0.25, 0.15, 0.08, 0.30);
	glPopMatrix();

	//Top : Middle Diamond
	glPushMatrix();
	glTranslatef(0, 0.22, 0);
	glRotatef(-10, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	glTranslatef(-0, -0.22, 0);
	drawCuboid(0.84, 0.831, 0.815, 0, 0.22, -0.4, 0.15, 0.15, 0.15);
	glPopMatrix();

	//Top : Left Diamond
	glPushMatrix();
	glTranslatef(-0.21, 0.15, 0);
	glRotatef(-10, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	glTranslatef(0.21, -0.15, 0);
	drawCuboid(0.84, 0.831, 0.815, -0.21, 0.15, -0.37, 0.05, 0.05, 0.35);
	glPopMatrix();

	//Top : Right Diamond
	glPushMatrix();
	glTranslatef(0.21, 0.15, 0);
	glRotatef(-10, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	glTranslatef(-0.21, -0.15, 0);
	drawCuboid(0.84, 0.831, 0.815, 0.21, 0.15, -0.37, 0.05, 0.05, 0.35);
	glPopMatrix();

}

void body() {
	//Frame
	drawCuboid(1, 1, 1, 0, 4.8, 1, 1.7, 0.6, 1); 
	drawCuboid(1, 1, 1, 0, 0.4, 1, 1.45, 0.6, 1); 
	
	glPushMatrix();
	glTranslatef(-1.7, 3.5, 1);
	glRotatef(-15, 0, 0, 1);
	glTranslatef(1.7, -3.5, -1);
	drawCuboid(1, 1, 1, -1.7, 3.5, 1, 0.5, 1.8, 1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1.7, 3.5, 1);
	glRotatef(15, 0, 0, 1);
	glTranslatef(-1.7, -3.5, -1);
	drawCuboid(1, 1, 1, 1.7, 3.5, 1, 0.5, 1.8, 1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1.6, 1.1, 1);
	glRotatef(-30, 0, 0, 1);
	glTranslatef(-1.6, -1.1, -1);
	drawCuboid(1, 1, 1, 1.6, 1.1, 1, 0.5, 1.2, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.6, 1.1, 1);
	glRotatef(30, 0, 0, 1);
	glTranslatef(1.6, -1.1, -1);
	drawCuboid(1, 1, 1, -1.6, 1.1, 1, 0.5, 1.2, 1);
	glPopMatrix();

	//Left Shoulder
	glPushMatrix();
	glTranslatef(-3.5, 4, -0.5);
	glRotatef(-10, 0, 0, 1);
	glTranslatef(3.5, -4, 0.5);
	drawCuboid(1, 1, 1, -3.5, 4, 0, 2, 1.2, 1.5);
	glPopMatrix();

	//Right Shoulder
	glPushMatrix();
	glTranslatef(3.5, 4, -0.5);
	glRotatef(10, 0, 0, 1);
	glTranslatef(-3.5, -4, 0.5);
	drawCuboid(1, 1, 1, 3.5, 4, 0, 2, 1.2, 1.5);
	glPopMatrix();

	//Rotating Orb
	glPushMatrix();
	glTranslatef(0, 2.5, 0.8);
	glRotatef(speed, 1, 1, 1);
	glTranslatef(-0, -2.5, -0.8);
	drawSphere(1, 1, 1, 0, 2.5, 0.8, 1, GLU_LINE);
	glPopMatrix();

	//Bottom
	glPushMatrix();
	glTranslatef(-1.7, -1, 1);
	glRotatef(-30, 0, 0, 1);
	glTranslatef(1.7, 1, -1);
	drawCuboid(1, 1, 1, -1.7, -1, 1, 0.5, 1.2, 0.5);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1.7, -1, 1);
	glRotatef(30, 0, 0, 1);
	glTranslatef(-1.7, 1, -1);
	drawCuboid(1, 1, 1, 1.7, -1, 1, 0.5, 1.2, 0.5);
	glPopMatrix();

	drawCuboid(1, 1, 1, 0, -1.7, 1, 0.7, 1.5, 0.8);

	//Back
	//drawCuboid(1, 1, 1, 0, 1, -2, 2, 3.5, 3);

}

void display()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	projection();
	lighting();

	//Sky box
	/*GLuint skyTexture[1];
	skyTexture[0] = skyBox("sky.bmp");
	drawCuboid(1, 1, 1, 0, 0, -8, 8, 8, 8);
	glDeleteTextures(1, &skyTexture[0]);*/

	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, tZ);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambM);

	speed += 0.1;
	glPushMatrix();
	//glScalef(5, 5, 5);
	//head();
	//drawCylinder(1, 1, 1, 0.3, -0.3, 4.0, 2, 2, 2, GLU_FILL);
	//drawSphere(0, 1, 0, 0.0, 0.0, 0.0, 3, GLU_LINE);
	//drawCuboid(1, 1, 1, 0, 0, 0, 4, 2, 2);
	body();
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
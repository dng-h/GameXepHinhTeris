#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <string>
#include "drawText.h"
//#include <ctime>
// Include GLEW
#include <gl/glew.h>
// Include GLFW
#include <glfw/glfw3.h>

using namespace std;
//GLFWwindow* window;

// Include GLM
//#include <glm/glm.hpp>
//using namespace glm;
//function
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void error_callback(int error, const char* description);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouseClick_callback(GLFWwindow* window, int button, int action, int mode);
void KhungTroChoi();
void Khoi1();
void Khoi2();
void Khoi3();
void Khoi4();
void Khoi5();
void Khoi6();
void Khoi7();

const GLuint WIDTH = 800, HEIGHT = 800;
const char* TITLE = "Tro Choi Xep Hinh";

int now = 0, Knext = 0, timeSleep = 800;
int TrThai = 1;
double mouse_x = 0, mouse_y = 0;
GLint x0, x1, x2, x3;
GLint yy0, yy1, yy2, yy3;
GLint a0, a1, a2, a3;
GLint b0, b1, b2, b3;
GLint xmin = 0, xmax = 0, ymin = 0, ymax = 0;
GLint gocXoay = 0;
GLint midX = 0, midY = 0;
GLint MaTran[20][9];
GLint DiemSo = 0;

void ManHinhStart()
{
	drawStart();
	TrThai = 1;
}

void ChonHinh()
{
	switch (now)
	{
		case 1:
			x0 = x1 = x2 = 4; x3 = 5;
			yy0 = 22; yy1 = 21; yy2 = yy3 = 20;
			break;
		case 2:
			x0 = x1 = x2 = 5;
			x3 = 4;
			yy0 = 22;
			yy1 = 21;
			yy2 = yy3 = 20;
			break;
		case 3:
			x0 = x1 = 4;
			x2 = x3 = 5;
			yy0 = yy2 = 21;
			yy1 = yy3 = 20;
			break;
		case 4:
			x0 = 4;
			x1 = x2 = 5; 
			x3 = 6;
			yy0 = yy1 = 20;
			yy2 = yy3 = 21;
			break;
		case 5:
			x0 = 4;
			x1 = x2 = 5;
			x3 = 6;
			yy0 = yy1 = 21;
			yy2 = yy3 = 20;
			break;
		case 6:
			x0 = 4;
			x1 = x2 = 5;
			x3 = 6;
			yy0 = yy1 = yy3 = 21;
			yy2 = 20;
			break;
		case 7:
			x0 = x1 = x2 = x3 = 5;
			yy0 = 23;
			yy1 = 22;
			yy2 = 21;
			yy3 = 20;
			break;
	}
}

void VeHinh()
{
	switch (now)
	{
		case 1:
			Khoi1();
			break;
		case 2:
			Khoi2();
			break;
		case 3:
			Khoi3();
			break;
		case 4:
			Khoi4();
			break;
		case 5:
			Khoi5();
			break;
		case 6:
			Khoi6();
			break;
		case 7:
			Khoi7();
			break;
	}
}

int KtraXoay(GLint u0, GLint v0, GLint u1, GLint v1, GLint u2, GLint v2, GLint u3, GLint v3)
{
	if (u0 < 1 || u1 < 1 || u2 < 1 || u3 < 1) return 1;
	if (u0 > 9 || u1 > 9 || u2 > 9 || u3 > 9) return 1;
	if (v0 < 1 || v1 < 1 || v2 < 1 || v3 < 1) return 1;
	if (MaTran[20 - v0][u0 - 1] != 0 || MaTran[20 - v1][u1 - 1] != 0 || MaTran[20 - v2][u2 - 1] != 0 || MaTran[20 - v3][u3 - 1] != 0)
		return 1;
	return 0;
}

void XoayKhoi()
{
	xmin = min(x0, min(x1, min(x2, x3)));
	xmax = max(x0, max(x1, max(x2, x3)));
	ymin = min(yy0, min(yy1, min(yy2, yy3)));
	ymax = max(yy0, max(yy1, max(yy2, yy3)));
	midX = round((xmin + xmax) / 2);
	midY = round((ymin + ymax) / 2);
	GLint u0, v0, u1, v1, u2, v2, u3, v3;
	u0 = -yy0 + midX + midY;
	v0 = x0 - midX + midY;
	u1 = -yy1 + midX + midY;
	v1 = x1 - midX + midY;
	u2 = -yy2 + midX + midY;
	v2 = x2 - midX + midY;
	u3 = -yy3 + midX + midY;
	v3 = x3 - midX + midY;
	if (!KtraXoay(u0, v0, u1, v1, u2, v2, u3, v3))
	{
		x0 = u0; x1 = u1; x2 = u2; x3 = u3;
		yy0 = v0; yy1 = v1; yy2 = v2; yy3 = v3;
		xmin = min(x0, min(x1, min(x2, x3)));
		xmax = max(x0, max(x1, max(x2, x3)));
		ymin = min(yy0, min(yy1, min(yy2, yy3)));
		ymax = max(yy0, max(yy1, max(yy2, yy3)));
		midX = round((xmin + xmax) / 2);
		midY = round((ymin + ymax) / 2);
	}
	else return;
}

int KtraXmin()
{
	if (xmin == 1) return 1;
	int k0 = 0, k1 = 0, k2 = 0, k3 = 0;
	if (yy0 < 21 && MaTran[20 - yy0][x0 - 2] != 0)
		k0 = 1;
	if (yy1 < 21 && MaTran[20 - yy1][x1 - 2] != 0)
		k1 = 1;
	if (yy2 < 21 && MaTran[20 - yy2][x2 - 2] != 0)
		k2 = 1;
	if (yy3 < 21 && MaTran[20 - yy3][x3 - 2] != 0)
		k3 = 1;
	if (k0 == 1 || k1 == 1 || k2 == 1 || k3 == 1)
	{
		return 1;
	}
	return 0;
}

int KtraXmax()
{
	if (xmax == 9) return 1;
	int k0 = 0, k1 = 0, k2 = 0, k3 = 0;
	if (yy0 < 21 && MaTran[20 - yy0][x0] != 0)
		k0 = 1;
	if (yy1 < 21 && MaTran[20 - yy1][x1] != 0)
		k1 = 1;
	if (yy2 < 21 && MaTran[20 - yy2][x2] != 0)
		k2 = 1;
	if (yy3 < 21 && MaTran[20 - yy3][x3] != 0)
		k3 = 1;
	if (k0 == 1 || k1 == 1 || k2 == 1 || k3 == 1)
	{
		return 1;
	}
	return 0;
}

int KtraY()
{
	if (ymin == 1) return 1;
	int k0 = 0, k1 = 0, k2 = 0, k3 = 0;
	if (yy0 < 21 && MaTran[20 - yy0][x0 -1] != 0)
		k0 = 1;
	if (yy1 < 21 && MaTran[20 - yy1][x1 -1] != 0)
		k1 = 1;
	if (yy2 < 21 && MaTran[20 - yy2][x2 - 1] != 0)
		k2 = 1;
	if (yy3 < 21 && MaTran[20 - yy3][x3 - 1] != 0)
		k3 = 1;
	if (k0 == 1 || k1 == 1 || k2 == 1 || k3 == 1)
	{
		return 1;
	}
	return 0;
}

void gLoop()
{
	for (int i = 19; i >= 0; i--)
	{
		for (int j = 0; j < 9; j++)
		{
			int k = 1;
			switch (MaTran[i][j])
			{
				case 0:
					k = 0;
					break;
				case 1:
					glColor3f(0.0f, 1.0f, 1.0f);
					break;
				case 2:
					glColor3f(1.0f, 0.0f, 1.0f);
					break;
				case 3:
					glColor3f(1.0f, 1.0f, 0.0f);
					break;
				case 4:
					glColor3f(1.0f, 0.0f, 0.0f);
					break;
				case 5:
					glColor3f(0.0f, 1.0f, 0.0f);
					break;
				case 6:
					glColor3f(0.0f, 0.0f, 1.0f);
					break;
				case 7:
					glColor3f(1.0f, 0.5f, 0.0f);
					break;
			}
			if (k != 0)
			{
				glBegin(GL_POINTS);
				glVertex2f(j + 1, 20 - i);
				glEnd();
			}
		}
	}
}

void AnDiem()
{
	for (int i = 19; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < 9; j++)
		{
			if (MaTran[i][j] != 0)
			{
				count++;
			}
		}
		if (count == 9)
		{
			for (int j = i; j > 0; j--)
			{
				for (int k = 0; k < 9; k++)
				{
					if (j > 0) MaTran[j][k] = MaTran[j - 1][k];
					else MaTran[j][k] = 0;
				}
			}
			DiemSo += 10;
			i++;
		}
	}
}
int GameOver()
{
	for (int i = 0; i < 9; i++)
	{
		if (MaTran[0][i] != 0)
		{
			return 1;
		}
	}
	return 0;
}

void VeNext()
{
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glVertex2f(15, 19);
	glVertex2f(24, 19);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(24, 19);
	glVertex2f(24, 12);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(24, 12);
	glVertex2f(15, 12);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(15, 12);
	glVertex2f(15, 19);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(15, 11);
	glVertex2f(24, 11);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(24, 11);
	glVertex2f(24, 4);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(24, 4);
	glVertex2f(15, 4);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(15, 4);
	glVertex2f(15, 11);
	glEnd();

	switch (Knext)
	{
		case 1:
			glColor3f(0.0f, 1.0f, 1.0f);
			a0 = a1 = a2 = 18; a3 = 19;
			b0 = 15; b1 = 14; b2 = b3 = 13;
			break;
		case 2:
			glColor3f(1.0f, 0.0f, 1.0f);
			a0 = a1 = a2 = 19;
			a3 = 18;
			b0 = 15;
			b1 = 14;
			b2 = b3 = 13;
			break;
		case 3:
			glColor3f(1.0f, 1.0f, 0.0f);
			a0 = a1 = 18;
			a2 = a3 = 19;
			b0 = b2 = 14;
			b1 = b3 = 13;
			break;
		case 4:
			glColor3f(1.0f, 0.0f, 0.0f);
			a0 = 18;
			a1 = a2 = 19;
			a3 = 20;
			b0 = b1 = 13;
			b2 = b3 = 14;
			break;
		case 5:
			glColor3f(0.0f, 1.0f, 0.0f);
			a0 = 18;
			a1 = a2 = 19;
			a3 = 20;
			b0 = b1 = 14;
			b2 = b3 = 13;
			break;
		case 6:
			glColor3f(0.0f, 0.0f, 1.0f);
			a0 = 18;
			a1 = a2 = 19;
			a3 = 20;
			b0 = b1 = b3 = 14;
			b2 = 13;
			break;
		case 7:
			glColor3f(1.0f, 0.5f, 0.0f);
			a0 = a1 = a2 = a3 = 19;
			b0 = 16;
			b1 = 15;
			b2 = 14;
			b3 = 13;
			break;
	}
	glBegin(GL_POINTS);
	glVertex2f(a0, b0);
	glVertex2f(a1, b1);
	glVertex2f(a2, b2);
	glVertex2f(a3, b3);
	glEnd();
}

int main(void)
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 9; j++)
			MaTran[i][j] = 0;

	// Initialize GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	// Set the GLFW error callback function
	glfwSetErrorCallback(error_callback);

	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

	if (!window) {
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	GLenum glewInitResult = glewInit();

	if (glewInitResult != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(glewInitResult));
		glfwTerminate();
		return -1;
	}

	// Set the viewport size
	glViewport(0, 0, WIDTH, HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 30.0, -15.0, 25.0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set the clear color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Enable point smoothing for better line rendering
	glEnable(GL_POINT_SMOOTH);

	// Set the GLFW key callback function
	glfwSetKeyCallback(window, key_callback);

	glfwSetErrorCallback(error_callback);

	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetMouseButtonCallback(window, mouseClick_callback);


	srand((unsigned int)time(0));
	now = 1 + rand() % 7;
	Knext = 1 + rand() % 7;
	ChonHinh();
	timeSleep = 800;


	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {
		// Clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Set the line color to white
		glColor3f(1.0f, 1.0f, 1.0f);

		if (TrThai == 1)
		{
			ManHinhStart();
		}
		if (TrThai == 0)
		{
			glPointSize(15.0f);
			glLineWidth(15.0f);

			KhungTroChoi();
			drawString("NEXT", 17, 17);
			drawString("SCORE", 17, 8);
			string str = to_string(DiemSo);
			drawString(str, 17, 5);
			xmin = min(x0, min(x1, min(x2, x3)));
			ymin = min(yy0, min(yy1, min(yy2, yy3)));
			xmax = max(x0, max(x1, max(x2, x3)));
			ymax = max(yy0, max(yy1, max(yy2, yy3)));
			midX = round((xmin + xmax) / 2);
			midY = round((ymin + ymax) / 2);
			VeNext();
			VeHinh();
			gLoop();
			yy0--; yy1--; yy2--; yy3--;
			Sleep(timeSleep);

			if (KtraY())
			{
				if (yy0 < 20) MaTran[19 - yy0][x0 - 1] = now;
				if (yy1 < 20) MaTran[19 - yy1][x1 - 1] = now;
				if (yy2 < 20) MaTran[19 - yy2][x2 - 1] = now;
				if (yy3 < 20) MaTran[19 - yy3][x3 - 1] = now;
				AnDiem();
				if (GameOver())
				{
					TrThai = -1;
				}
				srand((unsigned int)time(0));
				now = Knext;
				Knext = 1 + rand() % 7;
				ChonHinh();
				timeSleep = 800;
			}
		}
		if (TrThai == -1)
		{
			glPointSize(15.0f);
			glLineWidth(15.0f);
			KhungTroChoi();
			Knext = now;
			VeNext();
			drawString("NEXT", 17, 17);
			drawString("SCORE", 17, 8);
			string str = to_string(DiemSo);
			drawString(str, 17, 5);
			gLoop();
			drawGameOver();
		}

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	// Terminate GLFW
	glfwTerminate();

	return 0;

}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		if (!KtraXmin())
		{
			x0--;
			x1--;
			x2--;
			x3--;
			xmin = min(x0, min(x1, min(x2, x3)));
			xmax = max(x0, max(x1, max(x2, x3)));
		}
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		if (!KtraXmax())
		{
			x0++;
			x1++;
			x2++;
			x3++;
			xmin = min(x0, min(x1, min(x2, x3)));
			xmax = max(x0, max(x1, max(x2, x3)));
		}
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		timeSleep = 200;
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		XoayKhoi();
	}	
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouse_x = xpos / 800.0 * 2 - 1;
	mouse_y = 1 - ypos / 800.0 * 2;
	//cout << mouse_x << "   " << mouse_y << endl;
}

void mouseClick_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		if (TrThai == 1 && mouse_x >= -0.08  && mouse_x <= 0.08 && mouse_y >= -0.1 && mouse_y <= 0.05)
		{
			TrThai = 0;
		}
		if (TrThai == -1 && mouse_x >= -0.285 && mouse_x <= -0.08 && mouse_y >= -0.15 && mouse_y <= 0)
		{
			TrThai = 0;
			DiemSo = 0;
			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 9; j++)
					MaTran[i][j] = 0;
			srand((unsigned int)time(0));
			now = 1 + rand() % 7;
			Knext = 1 + rand() % 7;
			ChonHinh();
			timeSleep = 800;
		}
		if (TrThai == -1 && mouse_x >= 0.0775 && mouse_x <= 0.28 && mouse_y >= -0.15 && mouse_y <= 0)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}

void KhungTroChoi()
{
	glLineWidth(3.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(10, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 21);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0, 21);
	glVertex2f(10, 21);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(10, 0);
	glVertex2f(10, 21);
	glEnd();
	for (GLint i = 1; i < 10; i++)
	{
		for (GLint j = 1; j < 21; j++)
		{
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
			glBegin(GL_POINTS);
			glVertex2f(i, j);
			glEnd();
		}
	}
}

void Khoi1() //Chữ L
{
	glColor3f(0.0f, 1.0f, 1.0f); //Light Blue
	if (ymin == 20)
	{
		glBegin(GL_POINTS);
		glVertex2f(x2, yy2);
		glVertex2f(x3, yy3);
		glEnd();
		return;
	}
	if (ymin == 19)
	{
		glBegin(GL_POINTS);
		glVertex2f(x1, yy1);
		glVertex2f(x2, yy2);
		glVertex2f(x3, yy3);
		glEnd();
		return;
	}
	glBegin(GL_POINTS);
	glVertex2f(x0, yy0);
	glVertex2f(x1, yy1);
	glVertex2f(x2, yy2);
	glVertex2f(x3, yy3);
	glEnd();
}

void Khoi2() //Chữ L ngược
{
	glColor3f(1.0f, 0.0f, 1.0f); //Pink
	if (ymin == 20)
	{
		glBegin(GL_POINTS);
		glVertex2f(x2, yy2);
		glVertex2f(x3, yy3);
		glEnd();
		return;
	}
	if (ymin == 19)
	{
		glBegin(GL_POINTS);
		glVertex2f(x1, yy1);
		glVertex2f(x2, yy2);
		glVertex2f(x3, yy3);
		glEnd();
		return;
	}
	glBegin(GL_POINTS);
	glVertex2f(x0, yy0);
	glVertex2f(x1, yy1);
	glVertex2f(x2, yy2);
	glVertex2f(x3, yy3);
	glEnd();
}

void Khoi3() //Khối vuông
{
	glColor3f(1.0f, 1.0f, 0.0f); //Yellow
	if (ymin == 20)
	{
		glBegin(GL_POINTS);
		glVertex2f(x1, yy1);
		glVertex2f(x3, yy3);
		glEnd();
		return;
	}
	glBegin(GL_POINTS);
	glVertex2f(x0, yy0);
	glVertex2f(x1, yy1);
	glVertex2f(x2, yy2);
	glVertex2f(x3, yy3);
	glEnd();
}

void Khoi4() //Chữ T
{
	glColor3f(1.0f, 0.0f, 0.0f); //Red
	if (ymin == 20)
	{
		glBegin(GL_POINTS);
		glVertex2f(x0, yy0);
		glVertex2f(x1, yy1);
		glEnd();
		return;
	}
	glBegin(GL_POINTS);
	glVertex2f(x0, yy0);
	glVertex2f(x1, yy1);
	glVertex2f(x2, yy2);
	glVertex2f(x3, yy3);
	glEnd();
}

void Khoi5() //Chữ Z
{
	glColor3f(0.0f, 1.0f, 0.0f); //Green
	if (ymin == 20)
	{
		glBegin(GL_POINTS);
		glVertex2f(x2, yy2);
		glVertex2f(x3, yy3);
		glEnd();
		return;
	}
	glBegin(GL_POINTS);
	glVertex2f(x0, yy0);
	glVertex2f(x1, yy1);
	glVertex2f(x2, yy2);
	glVertex2f(x3, yy3);
	glEnd();
}
void Khoi6() //Chữ Z ngược
{
	glColor3f(0.0f, 0.0f, 1.0f); //Blue
	if (ymin == 20)
	{
		glBegin(GL_POINTS);
		glVertex2f(x2, yy2);
		glEnd();
		return;
	}
	glBegin(GL_POINTS);
	glVertex2f(x0, yy0);
	glVertex2f(x1, yy1);
	glVertex2f(x2, yy2);
	glVertex2f(x3, yy3);
	glEnd();
}

void Khoi7() // Chữ I
{
	glColor3f(1.0f, 0.5f, 0.0f); //Orange
	if (ymin == 20)
	{
		glBegin(GL_POINTS);
		glVertex2f(x3, yy3);
		glEnd();
		return;
	}
	if (ymin == 19)
	{
		glBegin(GL_POINTS);
		glVertex2f(x2, yy2);
		glVertex2f(x3, yy3);
		glEnd();
		return;
	}
	if (ymin == 18)
	{
		glBegin(GL_POINTS);
		glVertex2f(x1, yy1);
		glVertex2f(x2, yy2);
		glVertex2f(x3, yy3);
		glEnd();
		return;
	}
	glBegin(GL_POINTS);
	glVertex2f(x0, yy0);
	glVertex2f(x1, yy1);
	glVertex2f(x2, yy2);
	glVertex2f(x3, yy3);
	glEnd();
}
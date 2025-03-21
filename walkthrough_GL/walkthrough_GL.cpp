#include "pch.h"

#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

//  affine transformation
double eye[3] = { 0.0, 0.0, 1.5 };
double hangle = 0.0;
double vangle = 95.0;
double speed = 0.5;
double max_speed = 1.0;
double min_speed = 0.01;

void draw_ground()
{
	glBegin(GL_QUADS);
	for (int i = -500; i < 500; i++) {
		for (int j = -500; j < 500; j++) {
			if ((i + j) % 2 == 0)
				glColor3f(0.8f, 0.8f, 0.8f);
			else
				glColor3f(0.6f, 0.6f, 0.6f);
			glVertex3f((float)i, (float)j, 0.0f);
			glVertex3f((float)i, (float)(j + 1), 0.0f);
			glVertex3f((float)(i + 1), (float)(j + 1), 0.0f);
			glVertex3f((float)(i + 1), (float)j, 0.0f);
		}
	}
	glEnd();
}

//  display
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// 視点の設定
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		eye[0], eye[1], eye[2],
		eye[0] + cos(hangle / 180.0 * PI) * sin(vangle / 180.0 * PI),
		eye[1] + sin(hangle / 180.0 * PI) * sin(vangle / 180.0 * PI),
		eye[2] + cos(vangle / 180.0 * PI),
		0.0, 0.0, 1.0
	);

	//地面の描画
	draw_ground();

	glFlush();
}

//  reshape
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)w / h, 1.0, 100.0);
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		eye[0] += speed * sin(vangle / 180.0 * PI) * cos(hangle / 180.0 * PI);
		eye[1] += speed * sin(vangle / 180.0 * PI) * sin(hangle / 180.0 * PI);
		eye[2] += speed * cos(vangle / 180.0 * PI);
		printf("eye = %.2lf, %.2lf\n", eye[0], eye[1]);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		eye[0] -= speed * sin(vangle / 180.0 * PI) * cos(hangle / 180.0 * PI);
		eye[1] -= speed * sin(vangle / 180.0 * PI) * sin(hangle / 180.0 * PI);
		eye[2] -= speed * cos(vangle / 180.0 * PI);
		printf("eye = %.2lf, %.2lf\n", eye[0], eye[1]);
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		//前進
	case 'i':
		eye[0] += speed * cos(hangle / 180.0 * PI) * sin(vangle / 180.0 * PI);
		eye[1] += speed * sin(hangle / 180.0 * PI) * sin(vangle / 180.0 * PI);
		eye[2] += speed * cos(vangle / 180.0 * PI);
		break;
		//後退
	case 'm':
		eye[0] -= speed * cos(hangle / 180.0 * PI) * sin(vangle / 180.0 * PI);
		eye[1] -= speed * sin(hangle / 180.0 * PI) * sin(vangle / 180.0 * PI);
		eye[2] -= speed * cos(vangle / 180.0 * PI);
		break;
		//左回転
	case 'j':
		hangle += 1.0;
		break;
		//右回転
	case 'l':
		hangle -= 1.0;
		break;
		//上向き
	case 's':
		vangle -= 1.0;
		break;
		//下向き
	case 'd':
		vangle += 1.0;
		break;
		//速度+
	case 'w':
		speed += 0.01;
		break;
		//速度-
	case 'e':
		speed -= 0.01;
		break;

	}
	//  再描画
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInitWindowSize(400, 400);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("3D Graphics");
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutMainLoop();

	return 0;
}

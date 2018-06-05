#include<bits/stdc++.h>
#include<GL/glut.h>

#define pi 3.1415

float tri[4][4] = { { 150.0,250.0,350.0 } ,{ 250.0,350.0,250.0 },{ 1.0,1.0,1.0 },{ 1.0,1.0,1.0 } };
float rotate[4][4], result[4][4], angle = 90, h=150,k=250;
float theta = pi / 180.0;

void calc()
{
	
	rotate[0][0] = cos(theta*angle);
	rotate[0][1] = -sin(theta*angle);
	rotate[0][2] = 0;
	rotate[0][3] = -h * cos(theta*angle) + k * sin(theta*angle) + h;

	rotate[1][0] = sin(theta*angle);
	rotate[1][1] = cos(theta*angle);
	rotate[1][2] = 0;
	rotate[1][3] = -h * sin(theta*angle) - k * cos(theta*angle) + k;

	rotate[2][0] = 0;
	rotate[2][1] = 0;
	rotate[2][2] = 1;
	rotate[2][3] = 0;


	rotate[3][0] = 0;
	rotate[3][1] = 0;
	rotate[3][2] = 0;
	rotate[3][3] = 1;
	
	
}

void Init()
{
	gluOrtho2D(0, 500, 0, 500);

}

void triangle(float arr[][4])
{
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);

	glVertex2f(arr[0][0], arr[1][0]);
	glVertex2f(arr[0][1], arr[1][1]);
	glVertex2f(arr[0][2], arr[1][2]);

	glEnd();
	glFlush();
	calc();


}

void trirotation()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < 4; k++)
				result[i][j] += rotate[i][k] * tri[k][j];
		}
	}

	triangle(result);
}


void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	triangle(tri);
	trirotation(tri);

}


int main(int argc, char **argv)
{

	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Triangle roatation around any point");

	Init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;

}


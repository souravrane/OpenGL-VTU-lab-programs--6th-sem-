#include<stdio.h>
#include<GL/glut.h>

int xmax = 100, ymax = 100, xmin = 50, ymin = 50, x1 = 80, y1 = 120, x0 = 60, y0 = 20, left = 8, right = 2, bottom = 1, top = 4, x, y;
float m = (y1 - y0) / (x1 - x0);

void Init()
{

	gluOrtho2D(0, 400, 0, 400);

}

int compute(int x, int y)
{
	int code = 0;

	if (x<xmin)
		code |= left;

	if (x>xmax)
		code |= right;

	if (y<ymin)
		code |= bottom;

	if (y>ymax)
		code |= top;

	return code;

}


void cohen()
{
	bool done = false, accept = false;
	int code0, code1, codeout;

	code0 = compute(x0, y0);
	code1 = compute(x1, y1);

	do
	{
		codeout = code0 ? code0 : code1;
		if (!(code0 | code1))
		{
			done = true;
			accept = true;
		}

		else if (code0 & code1)
			done = true;
		else
		{
			if (codeout & bottom)
			{
				x = x0 + (1 / m)*(ymin - y0);
				y = ymin;

			}

			if (codeout & top)
			{
				x = x0 + (1 / m)*(ymax - y0);
				y = ymax;
			}

			if (codeout & left)
			{
				x = xmin;
				y = y0 + m * (xmin - x0);
			}

			if (codeout & right)
			{
				x = xmax;
			}

			if (codeout == code0)
			{
				x0 = x;
				y0 = y;
				code0 = compute(x, y);
			}

			if (codeout == code1)
			{
				x1 = x;
				y1 = y;
				code1 = compute(x, y);
			}
		}


	} while (!done);
	
	if (accept)
	{
		glTranslatef(100, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(xmin, ymax);
		glVertex2i(xmax, ymax);
		glVertex2i(xmax, ymin);
		glVertex2i(xmin, ymin);
		glEnd();

		glBegin(GL_LINES);
		glVertex2i(x0, y0);
		glVertex2i(x1, y1);
		glEnd();
	}
	
}

void display()
{


	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(xmin, ymax);
	glVertex2i(xmax, ymax);
	glVertex2i(xmax, ymin);
	glVertex2i(xmin, ymin);
	glEnd();

	glBegin(GL_LINES);
	glVertex2i(60,20);
	glVertex2i(80,120);
	glEnd();

	cohen();
	
	glFlush();

}



int main(int argc, char **argv)
{


	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Line clipping algorithm");

	Init();
	glutDisplayFunc(display);
	glutMainLoop();

}
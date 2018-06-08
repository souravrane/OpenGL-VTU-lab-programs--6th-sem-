#include<bits/stdc++.h>
#include<GL/glut.h>


#define MAX 10
int k = 0, flag = 0, doit;

typedef struct diamond
{
	float x;
	float y;
	float r;
}diamond;

diamond c[MAX];
int a[MAX];
int initial[MAX] = { 8,4,10,6,3,7,9,1,5,2 };
float initial_x1, initial_x2;

int ii = 0, jj = 0;
int swapping = 0;
int sorting = 0;
void initialise()
{
	doit = 1;
	ii = jj = swapping = 0;
	for (int i = 0; i<MAX; i++)
	{
		a[i] = initial[i];
		c[i].r = a[i] * 4.0;
		c[i].y = 300.0;
		if (i == 0)
			c[i].x = 45.0;
		else
			c[i].x = c[i - 1].x + 90.0;
		printf("%f - %f - %f\n", c[i].x, c[i].y, c[i].r);
	}
}


void text_display(int x, int y, char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}


void int_str(int rad, char r[])
{
	switch (rad)
	{
	case 1: strcpy(r, "1"); break;
	case 2: strcpy(r, "2"); break;
	case 3: strcpy(r, "3"); break;
	case 4: strcpy(r, "4"); break;
	case 5: strcpy(r, "5"); break;
	case 6: strcpy(r, "6"); break;
	case 7: strcpy(r, "7"); break;
	case 8: strcpy(r, "8"); break;
	case 9: strcpy(r, "9"); break;
	case 10: strcpy(r, "10"); break;
	}

}

void rhombus(diamond c)
{
	float i;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(c.x, c.y);
	for (i = 0; i <= 9; i += 1.57)
		glVertex2f(c.x + sin(i) * c.r, c.y + cos(i) * c.r);
	glEnd();


	int x = c.x - 2;
	int y = c.y - (c.r + 10);
	int rad = c.r / 4;
	char r[3] = "";
	int_str(rad, r);
	glColor3f(0.0, 0.0, 0.0);
	text_display(x, y, r, GLUT_BITMAP_TIMES_ROMAN_10);

}


void swap_diamonds(diamond *cc1, diamond *cc2)
{
	if (swapping == 0)
	{
		initial_x1 = cc1->x;
		initial_x2 = cc2->x;
		swapping = 1;
		printf("%f - %f\n", cc1->r, cc2->r);

	}

	if (initial_x1 <= cc2->x)
		cc2->x -= 1.0;

	if (initial_x2 >= cc1->x)
		cc1->x += 1.0;

	printf("one %f - %f\n", initial_x1, cc2->x);
	printf("two %f - %f\n", initial_x2, cc1->x);

	if (abs(initial_x1 - cc2->x) < 0.3 && abs(initial_x2 - cc1->x) < 0.3)
	{
		swapping = 0;

		int temp = cc1->x;
		cc1->x = cc2->x;
		cc2->x = temp;

		temp = cc1->y;
		cc1->y = cc2->y;
		cc2->y = temp;

		temp = cc1->r;
		cc1->r = cc2->r;
		cc2->r = temp;
	}

}


void sort()
{
	if (!swapping)
	{

		while (ii < 10)
		{
			if (doit == 1)
			{
				jj = 0;
				doit = 0;
			}
			while (jj < 9)
			{
				if (a[jj] > a[jj + 1])
				{
					printf("%d %d\n", jj, a[jj]);
					int temp = a[jj];
					a[jj] = a[jj + 1];
					a[jj + 1] = temp;
					goto SWAP;

				}
				jj++;
			}
			ii++;
			doit = 1;
		}
	}
SWAP:
	printf("swapping --> %d - %d\n", jj, jj + 1);
	text_display(10, 375, "Swapping ->", GLUT_BITMAP_9_BY_15);

	char r[3] = "";
	int_str(a[jj], r);
	text_display(150, 375, r, GLUT_BITMAP_9_BY_15);
	int_str(a[jj + 1], r);
	text_display(175, 375, r, GLUT_BITMAP_9_BY_15);

	swap_diamonds(&c[jj], &c[jj + 1]);
}

void display_text()
{
	text_display(250, 565, "BUBBLE SORT ALGORITHM", GLUT_BITMAP_TIMES_ROMAN_24);
	glBegin(GL_LINES);
	glVertex2f(248, 560);
	glVertex2f(570, 560);
	glBegin(GL_LINES);
	glVertex2f(248, 564);
	glVertex2f(570, 564);
	glEnd();

	text_display(10, 525, "THIS PROGRAM SORTS NUMBERS IN ASCENDING ORDER ", GLUT_BITMAP_HELVETICA_12);
	text_display(10, 505, "NUMBERS ARE DISPLAYED USING RED DIAMONDS WITH SIZE PROPORTIONAL TO THE NUMBER ", GLUT_BITMAP_HELVETICA_12);

	if (sorting == 0)
	{
		text_display(10, 455, "RGITH CLICK FOR MENU", GLUT_BITMAP_9_BY_15);
	}
	else if (sorting == 1)
	{
		glColor3f(0.5, 0.5, 0.5);
		text_display(10, 455, "HOLD ON ! SORTING IN PROGRESS .......", GLUT_BITMAP_9_BY_15);
		glColor3f(0.0, 0.0, 0.0);
	}

	text_display(500, 120, "BY: ABHINAV RAJPUT (1CR15CS005) ", GLUT_BITMAP_HELVETICA_12);
	text_display(500, 100, "    SOURAV MOHAN RANE (1CR15CS153)", GLUT_BITMAP_HELVETICA_12);


}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);


	display_text();

	glPointSize(2.0);
	for (int i = 0; i<MAX; i++)
	{
		glColor3f(1.0, 0.0, 0.0);
		rhombus(c[i]);
	}
	if (jj + 1 < MAX && sorting == 1)
		sort();
	else
		sorting = 0;

	glFlush();
	glutSwapBuffers();

}

void mousemenu(int id) {
	switch (id)
	{
	case 3: exit(0);
	case 1: sorting = 1; break;
	case 2: initialise(); break;
	}

}


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (float)h / (float)w, 2.0* (float)h / (float)w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (float)w / (float)h, 2.0* (float)w / (float)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void init(void)
{
	glClearColor(0.3,0.3, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 900.0, 0.0, 600.0);
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(900, 600);
	glutCreateWindow("Bubble sort");
	init();
	initialise();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutCreateMenu(mousemenu);
	glutAddMenuEntry("SORT", 1);
	glutAddMenuEntry("SHUFFLE", 2);
	glutAddMenuEntry("EXIT", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}


#include <stdio.h>
#include <GL/glut.h>

GLfloat x = 2.3, y = 1.0;

void wall(double thickness)
{
	glPushMatrix();
	glTranslated(0.5, 0.5*thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

//draw one table leg
void tableleg(double thick, double len)
{
	glPushMatrix();
	glTranslated(0, len / 2, 0);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
}

void table(double topWid, double topThick, double legThick, double legLen)
{
	//draw the table - a top and 4 legs
	//draw the top first
	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topWid);
	glutSolidCube(1.0);
	glPopMatrix();
	double dist = 0.95*topWid / 2.0 - legThick / 2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	tableleg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	tableleg(legThick, legLen);
	glTranslated(-2 * dist, 0, 2 * dist);
	tableleg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	tableleg(legThick, legLen);
	glPopMatrix();
}

void displaySolid()
{
	//light source
	GLfloat lightIntensity[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat lightPosition[] = { 2.0f,6.0f,3.0f,0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);


	//camera positioning
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, 2.0, 0.0, 0.2, 0.0, 0.0, 1.0, 0.0);

	//start drawing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslated(0.5, 0.4, 0.5);
	glRotated(30, 0, 1, 0);
	glutSolidTeapot(0.08);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.4, 0, 0.4);
	table(0.6, 0.02, 0.02, 0.3);
	glPopMatrix();

	wall(0.02);

	glPushMatrix();
	glRotated(90, 0, 0, 1);
	wall(0.02);
	glPopMatrix();

	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	wall(0.02);
	glPopMatrix();

	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Teapot");
	glutDisplayFunc(displaySolid);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glClearColor(0.1, 0.1, 0.1, 0.0);
	glutMainLoop();
	return 0;
}
#include <GL/glut.h>
#include <bevgrafmath2017.h>
#include <math.h>

GLint novX = 1;
GLint novY = 1;
vec2 center = { 400, 300 }; 
vec2 O = { center }; 
GLint r = 50; 
GLsizei winWidth = 800, winHeight = 600; 
vec2 points[4] = { {100, 300}, {200, 100}, {300, 200}, {400, 100} }; 
GLint N = 4; 
GLint dragged = -1;
GLdouble t = 0;
GLdouble x = 0;
GLdouble y = 0;
GLboolean inc = false;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0); 
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glEnable(GL_POINT_SMOOTH); 
	glEnable(GL_LINE);
	glPointSize(10.0);
	glLineWidth(2.0); 
}

void szakasz()
{
	GLint i;
	glBegin(GL_LINES);
	for (i = 0; i < 4; i++)
		glVertex2f(points[i].x, points[i].y); 
	glEnd();
}

void pont()
{
	GLint i;
	glBegin(GL_POINTS); 
	for (i = 0; i < 4; i++)
		glVertex2f(points[i].x, points[i].y);
	glEnd();
}

void setN() 
{
	if (N == 4)
	{
		inc = true;
		N++;
	}
	else if (N > 4 && N < 20)
	{
	inc ? N++ : N--;
	}
	else if (N == 20)
	{
		inc = false;
		N--;
	}
}

void movement(int n)
{ 
	center.x += novX;
	center.y += novY;
	if (center.x + r > winWidth || center.x - r < 0)
		novX *= -1;
	if (center.y + r > winHeight || center.y - r < 0)
		novY *= -1;

	glutPostRedisplay();
	glutTimerFunc(10, movement, 0);
}

void circle(vec2 O, GLdouble r)
{
	glBegin(GL_LINE_LOOP);
	for (GLdouble t = 0.0; t <= 2.0 * pi(); t += 2.0* pi() / N)
	{
		glVertex2d(O.x + r * cos(t), O.y + r * sin(t));
	}
	glEnd();
}

void kp()
{
	glBegin(GL_POINTS);
	glVertex2f(center.x, center.y);
	glEnd();
}
void mp() 
{
	GLdouble min_x = 1000;
	GLdouble max_x = -1000;
	GLdouble min_y = 1000;
	GLdouble max_y = -1000;
	GLdouble min_x2 = 1000;
	GLdouble max_x2 = -1000;
	GLdouble min_y2 = 1000;
	GLdouble max_y2 = -1000;

	GLdouble detA = ((points[0].y - points[1].y)*(points[3].x - points[2].x)) - ((points[1].x - points[0].x)*(points[2].y - points[3].y)); 

	GLdouble detX = (-((points[1].y - points[0].y)*points[0].x + (points[0].x - points[1].x)*points[0].y)*(points[3].x - points[2].x)) - 
		((points[1].x - points[0].x)* -((points[3].y - points[2].y)*points[2].x + (points[2].x - points[3].x)*points[2].y));

	GLdouble detY = ((points[0].y - points[1].y) * -((points[3].y - points[2].y)*points[2].x + (points[2].x - points[3].x)*points[2].y)) -
		(-((points[1].y - points[0].y)*points[0].x + (points[0].x - points[1].x)*points[0].y)* (points[2].y - points[3].y));

	GLdouble x1 = detX / detA; 
	GLdouble y1 = detY / detA; 

	for (GLint i = 0; i < 2; i++) 
	{
		if (points[i].x < min_x)
			min_x = points[i].x;
	}
	for (GLint i = 0; i < 2; i++) 
	{									
		if (points[i].x > max_x)
			max_x = points[i].x;
	}
	for (GLint i = 0; i < 2; i++) 
	{
		if (points[i].y < min_y)
			min_y = points[i].y;
	}
	for (GLint i = 0; i < 2; i++) 
	{
		if (points[i].y > max_y)
			max_y = points[i].y;
	}
	for (GLint i = 2; i < 4; i++)
	{
		if (points[i].x < min_x2)
			min_x2 = points[i].x;
	}
	for (GLint i = 2; i < 4; i++) 
	{
		if (points[i].x > max_x2)
			max_x2 = points[i].x;
	}
	for (GLint i = 2; i < 4; i++) 
	{
		if (points[i].y < min_y2)
			min_y2 = points[i].y;
	}
	for (GLint i = 2; i < 4; i++) 
	{
		if (points[i].y > max_y2)
			max_y2 = points[i].y;
	}

	if ((x1 > min_x) && (x1 > min_x2) && (x1 < max_x) && (x1 < max_x2) && (y1 > min_y) && (y1 > min_y2) && (y1 < max_y) && (y1 < max_y2))
	{
		glBegin(GL_POINTS);
		{
			glVertex2f(x1, y1);
		}
		glEnd();
	}
}

void diagonal(vec2 O, GLdouble r)
{
	glBegin(GL_LINES);
	for (GLdouble t = 0.0; t <= 2.0 * pi(); t += 2.0*pi() / N)
	{
		GLdouble j = 2 * pi() / N;
		for (GLdouble z = t + j + j; z < 2 * pi() + t - j; z += j)
		{
			glVertex2d(O.x + r * cos(t), O.y + r * sin(t));
			glVertex2d(O.x + r * cos(z), O.y + r * sin(z));
		}
	}
	glEnd();
}

void keyboard(unsigned char key, int x, int y)
{ 
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'w':
		r += 5;
		break;
	case 's':
		r -= 5;
		break;
	}
}

GLint getActivePoint1(vec2 p[], GLint size, GLint sens, GLint x, GLint y)
{ 
	GLint i, s = sens * sens;
	vec2 P = { (float)x, (float)y };
	for (i = 0; i < size; i++)
		if (dist2(p[i], P) < s) 
			return i; 
	return -1;
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse)
{ 
	GLint i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
		if ((i = getActivePoint1(points, 4, 8, xMouse, winHeight - yMouse)) != -1) 
			dragged = i; 
	if (button == GLUT_LEFT_BUTTON && action == GLUT_UP)
		dragged = -1; 
} 

void processMouseActiveMotion(GLint xMouse, GLint yMouse)
{ 
	GLint i;
	if (dragged >= 0)
	{
		points[dragged].x = xMouse; 
		points[dragged].y = winHeight - yMouse;
		glutPostRedisplay();
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	szakasz();

	glColor3f(1.0, 1.0, 1.0);
	pont();

	glColor3f(0.0, 0.0, 1.0);
	circle(center, r);

	if (((points[0].y - points[1].y) *center.x + (points[1].x - points[0].x) *center.y + (points[1].y - points[0].y)*points[0].x + (points[0].x - points[1].x)*points[0].y) > 0
		&& ((points[2].y - points[3].y) *center.x + (points[3].x - points[2].x) *center.y + (points[3].y - points[2].y)*points[2].x + (points[2].x - points[3].x)*points[2].y) > 0)
	{
		glColor3f(1.0, 0.0, 1.0);
	}
	else if (((points[0].y - points[1].y) *center.x + (points[1].x - points[0].x) *center.y + (points[1].y - points[0].y)*points[0].x + (points[0].x - points[1].x)*points[0].y) < 0
		&& ((points[2].y - points[3].y) *center.x + (points[3].x - points[2].x) *center.y + (points[3].y - points[2].y)*points[2].x + (points[2].x - points[3].x)*points[2].y) < 0)
	{
		glColor3f(1.0, 1.0, 0.0);
	}
	else if (((points[0].y - points[1].y) *center.x + (points[1].x - points[0].x) *center.y + (points[1].y - points[0].y)*points[0].x + (points[0].x - points[1].x)*points[0].y) < 0
		&& ((points[2].y - points[3].y) *center.x + (points[3].x - points[2].x) *center.y + (points[3].y - points[2].y)*points[2].x + (points[2].x - points[3].x)*points[2].y) > 0)
	{
		glColor3f(0.0, 1.0, 1.0);
	}
	else if (((points[0].y - points[1].y) *center.x + (points[1].x - points[0].x) *center.y + (points[1].y - points[0].y)*points[0].x + (points[0].x - points[1].x)*points[0].y) > 0
		&& ((points[2].y - points[3].y) *center.x + (points[3].x - points[2].x) *center.y + (points[3].y - points[2].y)*points[2].x + (points[2].x - points[3].x)*points[2].y) < 0)
	{
		glColor3f(0.0, 1.0, 0.0);
	}
	diagonal(center, r);

	glColor3f(1.0, 1.0, 1.0);
	kp();

	glColor3f(1.0, 0.0, 0.0);
	mp();

	setN();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Boldizsár_Erik_JD93QW_1.HF");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(processMouse); 
	glutKeyboardFunc(keyboard); 
	glutMotionFunc(processMouseActiveMotion);
	glutTimerFunc(10, movement, 0);
	glutMainLoop();
	return 0;
}
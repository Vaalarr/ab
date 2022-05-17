#include <iostream>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>
using namespace std;

#define radian 3.14/180

void drawkoch(float x1,float y1,float x2,float y2,int n);

void draw(int n){
	glColor3f(1,1,0);
	glBegin(GL_LINES);
	drawkoch(100,100,400,100,n);
	drawkoch(400,100,400,400,n);
	drawkoch(400,400,100,400,n);
	drawkoch(100,400,100,100,n);
	glEnd();
	glFlush();
}

void drawkoch(float x1,float y1,float x2,float y2,int n){
	float x3,y3,x4,y4,xm,ym;
	x3 = ((2*x1)+x2)/3;
	y3 = ((2*y1)+y2)/3;
	x4 = ((2*x2)+x1)/3;
	y4 = ((2*y2)+y1)/3;
	
	xm = x3 + ((x4-x3)*cos(60*radian))+((y4-y3)*sin(60*radian));
	ym = y3 - ((x4-x3)*sin(60*radian))+((y4-y3)*cos(60*radian));
	
	if(n>0){
		drawkoch(x1,y1,x3,y3,n-1);
		drawkoch(x3,y3,xm,ym,n-1);
		drawkoch(xm,ym,x4,y4,n-1);
		drawkoch(x4,y4,x2,y2,n-1);
	}
	else{
		glVertex2f(x1,y1);
		glVertex2f(x3,y3);
		
		glVertex2f(x3,y3);
		glVertex2f(xm,ym);
		
		glVertex2f(xm,ym);
		glVertex2f(x4,y4);
		
		glVertex2f(x4,y4);
		glVertex2f(x2,y2);
	}
}

void renderfunction(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,800,0,800);
	draw(3);
	
}

int main(int argc,char** argv){

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("Koch Curve");
	glutDisplayFunc(renderfunction);
	glutMainLoop();
	return 0;
}

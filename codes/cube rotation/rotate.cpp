#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <bits/stdc++.h>


void drawPoint(int x,int y){
	glColor3f(0,1,1);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void bsa(int x1,int y1,int x2,int y2){
	int dx = abs(x2-x1);
	int dy = abs(y2-y1);
	int p;
	int xin = 1;
	int yin = 1;
	if(x1>x2){
		xin = -1;
	}
	if(y1>y2){
		yin = -1;
	}
	int x = x1;
	int y = y1;
	if(dx==0){
		drawPoint(x,y);
		for(int i = 0;i<dy;i++){
			y+=yin;
		}
	}
	else if(dy==0){
		drawPoint(x,y);
		for(int i = 0;i<dx;i++){
			x+=xin;
		}
	}
	else{
		if(dx>dy){
			p = 2*dy - dx;
			for(int i = 0;i<dx;i++){
				drawPoint(x,y);
				if(p>0){
					y+=yin;
					p = p+2*(dy-dx);
				}
				else{
					p = p+2*dy;
				}
				x+=xin;
			}
		}
		else{
			p = 2*dx - dy;
			for(int i = 0;i<dy;i++){
				drawPoint(x,y);
				if(p>0){
					x+=xin;
					p = p+2*(dx-dy);
				}
				else{
					p = p+2*dx;
				}
				y+=yin;
			}
		}
	}
	glEnd();
}

void mymouse(int button,int state,int x,int y){
	
}

void renderfunction(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,800,0,800);
	bsa(100,100,200,300);
	glFlush();
	glEnd();
}

int main(int argc,char** argv){

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("cube rotation");
	glutDisplayFunc(renderfunction);
	glutMouseFunc(mymouse);
	glutMainLoop();
	return 0;
}

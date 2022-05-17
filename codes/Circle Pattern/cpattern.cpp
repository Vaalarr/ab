#include <GL/gl.h>
#include <GL/freeglut.h>
#include <iostream>
#include <math.h>
#define radian 3.14/180

int flag = 0;

void drawPoint(float x,float y){
	glColor3f(0,1,1);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

void octant(float xc,float yc,float x,float y){
	drawPoint(xc+x,yc+y);
	drawPoint(xc-x,yc-y);
	drawPoint(xc+x,yc-y);
	drawPoint(xc-x,yc+y);
	drawPoint(xc+y,yc+x);
	drawPoint(xc-y,yc-x);
	drawPoint(xc+y,yc-x);
	drawPoint(xc-y,yc+x);
	
}

void circleMP(float xc,float yc,float r){
	float x = 0;
	float y = r;
	float p = 3-2*r;
	while(x<y){
		octant(xc,yc,x,y);
		x++;
		if(p>0){
			y--;
			p+=4*(x-y)+10;
		}
		else{
			p+= 4*x+6;
		}
	}
	glFlush();
}

//void drawPattern(float xc,float yc,float r){
	//circleMP(xc,yc,r);
	//circleMP(xc,yc,r/2);
	//float ang = 0;
//	for(int i =0;i<8;i++){
		//circleMP(xc+((r/2)*cos(ang*radian)),yc+((r/2)*sin(ang*radian)),r/2);
	//	ang+=45;
//	}
//}

void drawPattern(float xc,float yc,float r){
	circleMP(xc,yc,2*r);
	float ang = 20;
	float rang = 160;
	for(int i = 3;i<15;i = i+2){
		circleMP(xc+((r*i)*cos(ang*radian)),yc+((r*i)*sin(ang*radian)),r);
		//circleMP(xc-((r*i)*cos(ang*radian)),yc-((r*i)*sin(ang*radian)),r);
		circleMP(xc+((r*i)*cos(rang*radian)),yc+((r*i)*sin(rang*radian)),r);
		ang+=3;
		rang-=3;
	}
}

void mymouse(int button,int state,int x,int y){
	
	float u,v;
	if(state==GLUT_DOWN && flag==0)
	{
		u=x; 
		v=500-y;
		flag = 1;
	}
	drawPattern(u,v,10);
}

void renderfunction(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,500,0,500);
	//drawPattern(400,400,25);
	glEnd();
	glFlush();
}

int main(int argc,char**argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutCreateWindow("lineClip");
	glutDisplayFunc(renderfunction);
	glutMouseFunc(mymouse);
	glutMainLoop();
	return 0;
}

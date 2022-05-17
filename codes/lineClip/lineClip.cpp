#include <GL/gl.h>
#include <GL/freeglut.h>
#include <iostream>
#include<stdio.h>


float x1i,y1i,x2i,y2i;
int xmin = 50;
int ymin = 50;
int xmax = 200;
int ymax = 200;

int get_opcode(float x,float y){
	int c = 0;
	
	if(y>ymax){
		c = 8;
	}
	if(y<ymin){
		c = 4;
	}
	
	if(x>xmax){
		c = c|2;
	}
	if(x<xmin){
		c = c|1;
	}
	return c;

}


void intersect1(int c1,float x1,float y1,float m){
	if((c1&8)==8){
		y1i = ymax;
		x1i = x1+((ymax-y1)/m);
	}
	else if((c1&4)==4){
		y1i = ymin;
		x1i = x1+((ymin-y1)/m);
	}
	else if((c1&2)==2){
		x1i = xmax;
		y1i = y1+ m*(xmax-x1);
	}
	else if((c1&1)==1){
		x1i = xmin;
		y1i = y1+ m*(xmin-x1);
	}
}
void intersect2(int c1,float x1,float y1,float m){
	if((c1&8)==8){
		y2i = ymax;
		x2i = x1+((ymax-y1)/m);
	}
	else if((c1&4)==4){
		y2i = ymin;
		x2i = x1+((ymin-y1)/m);
	}
	else if((c1&2)==2){
		x2i = xmax;
		y2i = y1+ m*(xmax-x1);
	}
	else if((c1&1)==1){
		x2i = xmin;
		y2i = y1+ m*(xmin-x1);
	}
}



void clipline(float x1,float y1,float x2,float y2){

	int c1 = get_opcode(x1,y1);
	std::cout<<c1<<" is c1"<<std::endl;
	int c2 = get_opcode(x2,y2);
	std::cout<<c2<<" is c2"<<std::endl;
	float m = (y2-y1)/(x2-x1);
	if((c1|c2)==0){
		x1i = x1;
		x2i = x2;
		y1i = y1;
		y2i = y2;
	}
	else{
		if((c1&c2)!=0){
			x1i = 0;
			x2i = 0;
			y1i = 0;
			y2i = 0;
		}
		else{
			if(c1!=0){
				intersect1(c1,x1,y1,m);
			}
			else{
				x1i = x1;
				y1i = y1;
			}
			if(c2!=0){
				intersect2(c2,x2,y2,m);
			}
			else{
				x2i = x2;
				y2i = y2;
			}
		}
	}

}

void drawPoint(float x, float y){
	glColor3f(1,0,1);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}



void drawDDA(float x1,float y1,float x2,float y2){
	float dx = x2-x1;
	float dy = y2-y1;
	float step;
	
	if(dx<0){
		dx = -dx;
	}
	if(dy<0){
		dy = -dy;
	}
	if(dx>dy){
		step = dx;
	}
	else{
		step = dy;
	}
	float xin = dx/step;
	float yin = dy/step;
	float x = x1;
	float y = y1;
	drawPoint(x,y);
	for(int i = 0; i<step;i++){
		x+=xin;
		y+=yin;
		drawPoint(x,y);
		
	}
	glFlush();
}

void renderfunction(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,500,0,500);
	drawDDA(50,50,200,50);
	drawDDA(50,50,50,200);
	drawDDA(200,50,200,200);
	drawDDA(50,200,200,200);
	//drawDDA(40,100,100,250);
	clipline(40,100,100,250);
	std::cout<<x1i<<" "<<y1i<<" "<<x2i<<" "<<y2i<<std::endl;
	//clipline(100,100,300,200);
	drawDDA(x1i,y1i,x2i,y2i);
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
	glutMainLoop();
	return 0;
}

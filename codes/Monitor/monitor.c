#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<GL/glut.h>

void myinit(void){
	glClearColor(0,0,0,1);
	glColor3f(1,0,0);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,1000,0,1000);
}

typedef struct pixel
{
	GLubyte r,g,b;
}pixel;

pixel f_color,b_color,old_color;

void flood_fill(int x,int y,pixel old_color ,pixel new_color)
{
	pixel c;
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&c);

	if(c.r==old_color.r && c.g==old_color.g && c.b==old_color.b){
		glColor3ub(new_color.r,new_color.g,new_color.b);//set fill color for pixel
		glBegin(GL_POINTS);
		glVertex2d(x,y);//put pixel
		glEnd();
		glFlush();
		flood_fill(x-1,y,old_color,new_color);//left pixel
		flood_fill(x,y+1,old_color,new_color);//upper pixel
		flood_fill(x,y-1,old_color,new_color);//lower pixel
		flood_fill(x+1,y,old_color,new_color);//right pixel
	}
}

void draw_axes(void){
	glBegin(GL_LINES);
	glVertex2i(0,500);
	glVertex2i(1000,500);
	glVertex2i(500,0);
	glVertex2i(500,1000);
	glEnd();

}
void draw_screen(void){
	glBegin(GL_LINE_LOOP);
	glVertex2i(300,350);
	glVertex2i(700,350);
	glVertex2i(700,650);
	glVertex2i(300,650);
	glEnd();

}
void draw_screenb(void){
	glBegin(GL_LINE_LOOP);
	glVertex2i(250,300);
	glVertex2i(750,300);
	glVertex2i(750,700);
	glVertex2i(250,700);
	glEnd();

}
void draw_stand(void){
	glBegin(GL_LINE_LOOP);
	glVertex2i(400,300);
	glVertex2i(300,200);
	glVertex2i(700,200);
	glVertex2i(600,300);
	
	glEnd();

}
void draw_hills(void){
	glBegin(GL_LINE_LOOP);
	glColor3f(0,1,0);
	glVertex2i(300,350);
	glVertex2i(350,450);
	glVertex2i(400,350);
	
	glVertex2i(550,550);
	glVertex2i(700,350);
	glColor3f(1,0,0);
	glEnd();

}
void draw(void){
	draw_screen();
	draw_hills();
	draw_screen();
	draw_screenb();
	draw_stand();

}
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);	
	draw();
	glFlush();
}
void mouse_click(int btn,int state,int x,int y)  //click the mouse if you want to fill the color
{
	if(btn==GLUT_LEFT_BUTTON&& state==GLUT_DOWN)
	{
		pixel f1_color,old1_color;
		f1_color.r=0;
		f1_color.g=255;
		f1_color.b=0;
		old1_color.r=old1_color.g=old1_color.b=0;
		flood_fill(350,375,old1_color,f1_color);
				
	}
}

int main(int argc,char** argv){

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(1000,0);
	glutInitWindowSize(1000,1000);
	glutCreateWindow("Monitor-DDA");
	myinit();
	glutMouseFunc(mouse_click);
	glutDisplayFunc(display);
	
	glutMainLoop();
}

#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
double cubed(double x){
	return x*x*x;
}
double squared(double x){
	return x*x;
}
double mod2(double x){
	return (double)((int)x%2);
}
double half(double x){
	return x/2;
}

#define SQRT_MAGIC_F 0x5f3759df 
double sqrt2_quake_weird(const double x){
	const double xhalf = 0.5f*x;
 
	union{
		double x;
		int i;
	} u;
  
	u.x = x;
	u.i = SQRT_MAGIC_F - (u.i >> 1);  // gives initial guess y0
	return x*u.x*(1.5f - xhalf*u.x*u.x);// Newton step, repeating increases accuracy 
}

typedef struct{
	float r;
	float g;
	float b;
} Clr;

Clr red_clr={1.0f,0.0f,0.0f};
Clr green_clr={0.0f,1.0f,0.0f};
Clr blue_clr={0.0f,0.0f,1.0f};
Clr white_clr={1.0f,1.0f,1.0f};
Clr yellow_clr={1.0f,1.0f,0.0f};

double integral(Clr color,double a,double b,double dx,double(*f)(double)){
	if (dx <= 0.0) {
		printf("Error: dx must be positive.\n");
		return 0.0;
	}
	double sum=0.0;
	double old_x=0.0;
	double old_y=0.0;
	for(double x=a;x<b;x+=dx){
		double y=f(x);
		sum+=dx*y;
		
		//Make this seen
		glBegin(GL_LINES);
			glColor3f(color.r,color.g,color.b);
	
			glVertex2f(old_x, old_y);
			glVertex2f(x, y);
		glEnd();
		old_y=y;
		old_x=x;
	}
	return sum;
}
void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 2.0, -1.0, 8.0, -1.0, 1.0);  // Adjust the visible range
    glMatrixMode(GL_MODELVIEW);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a red triangle
    //glBegin(GL_TRIANGLES);
	// Red color
    //glColor3f(1.0f, 0.0f, 0.0f);
	//vertexes
    //glVertex2f(-0.5f, -0.5f);
    //glVertex2f( 0.5f, -0.5f);
    //glVertex2f( 0.0f,  0.5f);
    //glEnd();
	
	integral(red_clr,1.0,2.0,0.01,cubed);
	integral(blue_clr,1.0,2.0,0.01,sqrt2_quake_weird);
	integral(green_clr,1.0,2.0,0.01,squared);
	integral(yellow_clr,1.0,2.0,0.01,mod2);
	integral(white_clr,1.0,2.0,0.01,half);
	//integral(green_clr,1.0,2.0,0.1,sqrt);
	
    glFlush(); // Render the graphics
}
int main(int argc, char** argv) {
	//double sz1=integral(1.0,2.0,0.1,cubed);
	//printf("%lf",sz1);
	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Integral");

	init();

    glutDisplayFunc(display); // Register display callback function
    glutMainLoop();           // Enter the GLUT main loop

    return 0;
}
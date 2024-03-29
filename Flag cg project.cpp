#include<stdio.h>
#include<glut.h>
#include<math.h>
#include<string.h>
#define PI 3.1416
static float theta=0;
GLint nctrlpts=4,nbezcurvepts=20;
void startdisplay();
void keystroke(unsigned char,int,int);
void output(float, float, char *);
void drawCircle(float,float,float);
void rhs1();
void menu(int);
void object1();
void object2();
void object3();
void object4();
void object5();
void object6();
void flag();
void moveUp();
void display1();
void bases();
void redCarpet();
void flagBase();
void lineForBase();
void lineForCarpet();
void lineForGreenPolygon();
int  p=0,i=8,r=0,j=0,x=0,k=0,q=0,m=3,a,b,c=0;
int quo,rem,fno,sno,tno,len;
float yr,xcor,ycor;
float xl,yl;
const float DEG2RAD=3.14159/180;


typedef struct wcpt3d
{
	GLfloat x,y,z;
};
void bino(GLint n,GLint *c)
{
	GLint k,j;
	for(k=0;k<=n;k++)
	{
		c[k]=1;
		for(j=n;j>=k+1;j--)
			c[k]*=j;
		for(j=n-k;j>=2;j--)
			c[k]/=j;
	}
}
void computebezpt(GLfloat u,wcpt3d *bezpt,GLint nctrlpts,wcpt3d *ctrlpts,GLint *c)
{
	GLint k,n=nctrlpts-1;
	GLfloat bez;
	bezpt->x=bezpt->y=bezpt->z=0.0;
	for(k=0;k<nctrlpts;k++)
	{
		bez=c[k]*pow(u,k)*pow(1-u,n-k);
		bezpt->x+=ctrlpts[k].x*bez;
		bezpt->y+=ctrlpts[k].y*bez;
		bezpt->z+=ctrlpts[k].z*bez;
	}
}
void bezier(wcpt3d *ctrlpts,GLint nctrlpts,GLint nbezcurvepts)
{
	wcpt3d bezcurvept;
	GLfloat u;
	GLint *c,k;
	c=new GLint[nctrlpts];
	bino(nctrlpts-1,c);
	glBegin(GL_LINE_STRIP);
	for(k=0;k<nbezcurvepts;k++)
	{
		u=GLfloat(k)/GLfloat(nbezcurvepts);
		computebezpt(u,&bezcurvept,nctrlpts,ctrlpts,c);
		glVertex2f(bezcurvept.x,bezcurvept.y);
	}
		glEnd();
		delete[] c;
}
void drawandanimate()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	wcpt3d ctrlpts[4]={{-0.02,0.8,0},{0.03,0.85,0},{0.15,0.75,0},{0.20,0.8,0}};
	ctrlpts[1].x+=0.1*sin(theta*PI/180.0);
    ctrlpts[1].y+=0.05*sin(theta*PI/180.0);
	ctrlpts[2].x-=0.1*sin((theta+30)*PI/180.0);
	ctrlpts[2].y-=0.1*sin((theta+30)*PI/180.0);
	ctrlpts[3].x+=0.04*sin(theta*PI/180.0);
	ctrlpts[3].y+=0.01*sin((theta-30)*PI/180.0);
	theta+=m;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	glPushMatrix();
	glLineWidth(5);
	glColor3f(255/255.0,153/255.0,51/255.0);
	for(int i=0;i<8;i++)
	{
		glTranslatef(0,-0.008,0);
		bezier(ctrlpts,nctrlpts,nbezcurvepts);
	}
	glColor3f(1,1,1);
	for(int i=0;i<8;i++)
		{
			glTranslatef(0,-0.008,0);
			bezier(ctrlpts,nctrlpts,nbezcurvepts);
		}
	glColor3f(19/255.0,135/255.0,8/255.0);
	for(int i=0;i<8;i++)
	{
		glTranslatef(0,-0.008,0);
		bezier(ctrlpts,nctrlpts,nbezcurvepts);
	}
	glPopMatrix();
	glColor3f(0.7,0.5,0.3);
	glLineWidth(5);
	glFlush();
	glutPostRedisplay();
	//glutSwapBuffers();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	display1();
	glFlush();
	glutSwapBuffers();
}
void startdisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.91,0.59,0.48,1);
	glColor3f(0.0,0.0,0.0);
	output(-0.15,0.7,"SJBIT,Bangalore");
	
	output(-0.22,0.55,"  ::::MINI PROJECT ON::::");
	
	output(-0.19,0.40," ::FLAG HOISTING::");
	
	output(-0.15,0.25,"SUBMITTED BY:");
	
	output(-0.9,0.15, "VARSHA A");
	
	output(-0.9,0.05,"1JB16CS178");
	
	output(-0.6,0.15, "SURYANSH SINGH");
	
	output(-0.6,0.05, "1JB16CS168");
	
	output(-0.23,-0.1,"UNDER THE GUIDANCE OF:");

	output(-0.9,-0.25,"Mrs.BINDIYA M K");
	
	output(0.6,-0.25,"Mrs.ROOPA MJ");

	output(-0.9,-0.35,"Asst. Prof., Dept. of CSE");
	
	output(0.6,-0.35,"Asst. Prof., Dept. of CSE");
	
	output(-0.13,-0.6,"Press 'S' to Start ");
	
	
	glutKeyboardFunc(keystroke);
	
	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}
void keystroke(unsigned char key,int x,int y)
{
	if(key == '+')  m++;
   	if(key == '-')  m--;
   	if(key==27) exit(0);
	if((key=='S' || key=='s'))
  {
	
	glutDisplayFunc(display);

	display();
  }

	glutPostRedisplay();
}

void moveUp()						//moving the knot up
{
	if(yr<=0.77)
	{
		if(xl<=-0.55&&yl>=0.14)
			yr += 0.05f;
	}
	glutPostRedisplay();
}

void mouse(int btn,int state,int x,int y)									//Interfacing the Mouse
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) 
	{
		
			moveUp();	
	}
	glutPostRedisplay();
		
}

void output(float x, float y, char *string)
{
	
	glRasterPos2f(x, y);
	len = (int)strlen(string);	
  for (k = 0; k < len; k++) 
  {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[k]);
	glutInitDisplayMode(GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
  }
}
void output1(float a, float b, char *string)
{
	
	glRasterPos2f(a,b);
	len = (int)strlen(string);	
  for (c = 0; c < len; c++) 
  {
	 
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[c]);
	glutInitDisplayMode(GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
  }
}



void display1()
{
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.529,0.807,0.921,1);
	flag();
	object1();
	object2();
	object3();
	object4();
	object5();
	object6();
	lineForGreenPolygon();
	lineForCarpet();
	lineForBase();
	flagBase();
	redCarpet();
	bases();


}

void drawCircle(float radius,float xcor,float ycor)
{
	glPointSize(5);
	glColor3f(0.941,0.901,0.549);
	//glBegin(GL_LINE_LOOP);
	for(int i=0;i<=360;i++)
	{
		float degInRad=i*DEG2RAD;
		glVertex2f(cos(degInRad)*radius+xcor,sin(degInRad)*radius+ycor);
	}
	//glEnd();
}

void chakra(float radius,float xcor,float ycor)//chakra
{
	glPointSize(5);
	glColor3f(0,0,1);
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<=360;i++)
	{
		float degInRad=i*DEG2RAD;
		glVertex2f(cos(degInRad)*radius+xcor,sin(degInRad)*radius+ycor);
	}
	//glEnd();
}

void keys(int k,int x,int y)		//translate using keyboard
{
	switch(k)
	{
		/*case GLUT_KEY_UP:
		if(yl<=0.14)
			yl+=0.05;
		glutPostRedisplay();
		break;*/
		case GLUT_KEY_LEFT:
			if(xl>=-0.52)
				xl-=0.05;
			if(yl<=0.14)
				yl+=0.0175;
		glutPostRedisplay();
		break;
	}
}
void object1()
{
	glColor3f(0,0,0);																				//instructions for project
	output(-0.98,0.92,"Instructions:-");
	output1(-0.98,0.86, "Press '<--' button to Move Left ");
	output1(-0.98,0.80, "Press 'Left Click' to move the knot up ");
	output1(-0.98,0.74, "Press '+' & '-' to Change the Waving speed of Flag ");
	output1(-0.98,0.68, "Press 'ESC' button to exit ");
	glPointSize(5);
    glBegin(GL_POINTS);	//eye1
	glColor3f(0,0,0);
	glVertex2f(0.584+xl,-0.035+yl);
	glEnd();
	glFlush();

			
	glBegin(GL_POLYGON); //face1
	drawCircle(0.033,0.60+xl,-0.041+yl);
	glEnd();
	glFlush();

	glLineWidth(3);   //neck1
    glBegin(GL_LINE_LOOP);	
	glColor3f(0.545,0,0);
	glVertex2f(0.597+xl,-0.041+yl);
	glVertex2f(0.61+xl,-0.041+yl);
	glVertex2f(0.597+xl,-0.091+yl);
	glVertex2f(0.61+xl,-0.091+yl);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.545,0,0);
	glVertex2f(0.597+xl,-0.041+yl);
	glVertex2f(0.61+xl,-0.041+yl);
	glVertex2f(0.597+xl,-0.091+yl);
	glVertex2f(0.61+xl,-0.091+yl);
	glEnd();
	glFlush();

	
	glLineWidth(1);   //left arm1(obj1)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.615+xl,-0.093+yl);
	glVertex2f(0.625+xl,-0.093+yl);
	glVertex2f(0.625+xl,-0.155+yl);
	glVertex2f(0.615+xl,-0.155+yl);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.254,0.411,1);
	glVertex2f(0.615+xl,-0.093+yl);
	glVertex2f(0.625+xl,-0.093+yl);
	glVertex2f(0.625+xl,-0.155+yl);
	glVertex2f(0.615+xl,-0.155+yl);
	glEnd();
	glFlush();

		glLineWidth(1);   //left hand1(obj1)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.615+xl,-0.155+yl);
	glVertex2f(0.625+xl,-0.155+yl);
	glVertex2f(0.625+xl,-0.200+yl);
	glVertex2f(0.615+xl,-0.200+yl);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(0.615+xl,-0.155+yl);
	glVertex2f(0.625+xl,-0.155+yl);
	glVertex2f(0.625+xl,-0.200+yl);
	glVertex2f(0.615+xl,-0.200+yl);
	glEnd();
	glFlush();

		glLineWidth(1);   //right arm1(obj1)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.560+xl,-0.091+yl);
	glVertex2f(0.560+xl,-0.133+yl);
	glVertex2f(0.570+xl,-0.133+yl);
	glVertex2f(0.570+xl,-0.091+yl);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.254,0.411,1);
	glVertex2f(0.560+xl,-0.091+yl);
	glVertex2f(0.560+xl,-0.133+yl);
	glVertex2f(0.570+xl,-0.133+yl);
	glVertex2f(0.570+xl,-0.091+yl);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
	 if(yr<=0.05)
	{
		glLineWidth(1);   //right hand(obj1)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.560+xl,-0.133+yl);
	//glVertex2f(0.360,-0.15);
	glVertex2f(0.570+xl,-0.133+yl);
	glVertex2f(0.570+xl,-0.22+yl);
	glVertex2f(0.560+xl,-0.22+yl);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(0.560+xl,-0.133+yl);
	//glVertex2f(0.360,-0.15);
	glVertex2f(0.570+xl,-0.133+yl);
	glVertex2f(0.570+xl,-0.22+yl);
	glVertex2f(0.560+xl,-0.22+yl);
	glEnd();
	glFlush();

	}
	else
	{
		glLineWidth(1);   //right hand(obj1)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.02,0.015);
	//glVertex2f(0.360,-0.15);
	glVertex2f(-0.02,-0.008);
	glVertex2f(0.0182,-0.008);
	glVertex2f(0.0182,0.015);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(-0.02,0.015);
	//glVertex2f(0.360,-0.15);
	glVertex2f(-0.02,-0.008);
	glVertex2f(0.0182,-0.008);
	glVertex2f(0.0182,0.015);
	glEnd();
	glFlush();
	}

	glPointSize(3.5);//bottons
    glBegin(GL_POINTS);	
	glColor3f(0.501,0,0.501);
	glVertex2f(0.6+xl,-0.140+yl);
	glVertex2f(0.6+xl,-0.118+yl);
	glVertex2f(0.6+xl,-0.165+yl);
	glVertex2f(0.6+xl,-0.187+yl);
	glEnd();
	glFlush();

	glLineWidth(1);   //body3
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.570+xl,-0.091+yl);
	glVertex2f(0.570+xl,-0.215+yl);
	glVertex2f(0.633+xl,-0.215+yl);
	glVertex2f(0.633+xl,-0.091+yl);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.933,0.909,0.666);
	glVertex2f(0.570+xl,-0.091+yl);
	glVertex2f(0.570+xl,-0.215+yl);
	glVertex2f(0.633+xl,-0.215+yl);
	glVertex2f(0.633+xl,-0.091+yl);
        glEnd();
	glFlush();


	glLineWidth(1);   //right leg3(object 1)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.580+xl,-0.215+yl);
	glVertex2f(0.580+xl,-0.300+yl);
	glVertex2f(0.595+xl,-0.300+yl);
	glVertex2f(0.595+xl,-0.215+yl);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.854,0.647,0.125);
	glVertex2f(0.580+xl,-0.215+yl);
	glVertex2f(0.580+xl,-0.300+yl);
	glVertex2f(0.595+xl,-0.300+yl);
	glVertex2f(0.595+xl,-0.215+yl);
	glEnd();
	glFlush();

	glLineWidth(1);   //left leg3(object 1)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.595+xl,-0.215+yl);
	glVertex2f(0.595+xl,-0.335+yl);
	glVertex2f(0.615+xl,-0.335+yl);
	glVertex2f(0.615+xl,-0.215+yl);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.854,0.647,0.125);
	glVertex2f(0.595+xl,-0.215+yl);
	glVertex2f(0.595+xl,-0.335+yl);
	glVertex2f(0.615+xl,-0.335+yl);
	glVertex2f(0.615+xl,-0.215+yl);
	glEnd();
	glFlush();


	glLineWidth(1);   //shoe1(ojb 1)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.570+xl,-0.300+yl);
	glVertex2f(0.570+xl,-0.310+yl);
	glVertex2f(0.595+xl,-0.310+yl);
	glVertex2f(0.595+xl,-0.300+yl);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0,0.752,1);
	glVertex2f(0.570+xl,-0.300+yl);
	glVertex2f(0.570+xl,-0.310+yl);
	glVertex2f(0.595+xl,-0.310+yl);
	glVertex2f(0.595+xl,-0.300+yl);
	glEnd();
	glFlush();


	glLineWidth(1);   //shoe2(ojb 1)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.560+xl,-0.310+yl);
	glVertex2f(0.615+xl,-0.310+yl);
	glVertex2f(0.615+xl,-0.335+yl);
	glVertex2f(0.560+xl,-0.335+yl);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0,0.752,1);
	glVertex2f(0.560+xl,-0.310+yl);
	glVertex2f(0.615+xl,-0.310+yl);
	glVertex2f(0.615+xl,-0.335+yl);
	glVertex2f(0.560+xl,-0.335+yl);
	glEnd();
	glFlush();



}
	
void object2()
{
		if(yr<=0.80)
	{
	glLineWidth(1);   //right hand1(obj2)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.660,-0.133);
	//glVertex2f(0.360,-0.15);
	glVertex2f(0.670,-0.133);
	glVertex2f(0.670,-0.22);
	glVertex2f(0.660,-0.22);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(0.660,-0.133);
	//glVertex2f(0.360,-0.15);
	glVertex2f(0.670,-0.133);
	glVertex2f(0.670,-0.22);
	glVertex2f(0.660,-0.22);
	
	glEnd();
	glFlush();
	}
	else
	{
			//if(yr>=0.8);
		
		
	glLineWidth(1);   //right hand1(obj2)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.650,-0.091);
	//glVertex2f(0.360,-0.15);
	glVertex2f(0.650,-0.123);
	glVertex2f(0.679,-0.040);
	glVertex2f(0.668,-0.035);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(0.650,-0.091);
	//glVertex2f(0.360,-0.15);
	glVertex2f(0.650,-0.123);
        glVertex2f(0.679,-0.040);
	glVertex2f(0.668,-0.035);
	glEnd();
	glFlush();

	//balloon();

	glColor3f(0,0,0);
	output(-0.2,0.5,"J A I");
	output(0.3,0.5,"H I N D");

	}
	
	glPointSize(5);
        glBegin(GL_POINTS);	//eye2
	glColor3f(0,0,0);
	glVertex2f(0.684,-0.035);
	glEnd();
	glFlush();
			
	glBegin(GL_POLYGON);  //face2
	drawCircle(0.033,0.70,-0.041);
	glEnd();
	glFlush();

	glLineWidth(3);   //neck2
        glBegin(GL_LINE_LOOP);	
	glColor3f(0.545,0,0);
	glVertex2f(0.697,-0.041);
	//glVertex2f(0.397,-0.091);
	glVertex2f(0.71,-0.041);
	glVertex2f(0.697,-0.091);
	glVertex2f(0.71,-0.091);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.545,0,0);
	glVertex2f(0.697,-0.041);
	//glVertex2f(0.397,-0.091);
	glVertex2f(0.71,-0.041);
	glVertex2f(0.697,-0.091);
	glVertex2f(0.71,-0.091);
	glEnd();
	glFlush();

	glLineWidth(1);   //left arm1(obj2)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.715,-0.093);
	glVertex2f(0.725,-0.093);
	glVertex2f(0.725,-0.155);
	glVertex2f(0.715,-0.155);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.254,0.411,1);
	glVertex2f(0.715,-0.093);
	glVertex2f(0.725,-0.093);
	glVertex2f(0.725,-0.155);
	glVertex2f(0.715,-0.155);
	glEnd();
	glFlush();

		glLineWidth(1);   //left hand1(obj2)
         glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.715,-0.155);
	glVertex2f(0.725,-0.155);
	glVertex2f(0.725,-0.200);
	glVertex2f(0.715,-0.200);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(0.715,-0.155);
	glVertex2f(0.725,-0.155);
	glVertex2f(0.725,-0.200);
	glVertex2f(0.715,-0.200);
	glEnd();
	glFlush();

	if(yr<=0.80)
	{
		glLineWidth(1);   //right arm1(obj2)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.660,-0.091);
	glVertex2f(0.660,-0.133);
	glVertex2f(0.670,-0.133);
	glVertex2f(0.670,-0.091);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.254,0.411,1);
	glVertex2f(0.660,-0.091);
	glVertex2f(0.660,-0.133);
	glVertex2f(0.670,-0.133);
	glVertex2f(0.670,-0.091);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
	}
	else
	{
			glLineWidth(1);   //right arm1(obj2)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.670,-0.091);
	glVertex2f(0.670,-0.113);
	glVertex2f(0.650,-0.113);
	glVertex2f(0.650,-0.091);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.254,0.411,1);
	glVertex2f(0.670,-0.091);
	glVertex2f(0.670,-0.113);
	glVertex2f(0.650,-0.113);
	glVertex2f(0.650,-0.091);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
}


	glLineWidth(1);   //body2
       glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.670,-0.091);
	glVertex2f(0.670,-0.215);
	glVertex2f(0.733,-0.215);
	glVertex2f(0.733,-0.091);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.752,0.752,0.752);
	glVertex2f(0.670,-0.091);
	glVertex2f(0.670,-0.215);
	glVertex2f(0.733,-0.215);
	glVertex2f(0.733,-0.091);
        glEnd();
	glFlush();

	glLineWidth(1);   //right leg4(object 2)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.680,-0.215);
	glVertex2f(0.680,-0.300);
	glVertex2f(0.695,-0.300);
	glVertex2f(0.695,-0.215);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.854,0.647,0.125);
	glVertex2f(0.680,-0.215);
	glVertex2f(0.680,-0.300);
	glVertex2f(0.695,-0.300);
	glVertex2f(0.695,-0.215);
	glEnd();
	glFlush();

	glLineWidth(1);   //left leg4(object 2)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.695,-0.215);
	glVertex2f(0.695,-0.335);
	glVertex2f(0.715,-0.335);
	glVertex2f(0.715,-0.215);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.854,0.647,0.125);
	glVertex2f(0.695,-0.215);
	glVertex2f(0.695,-0.335);
	glVertex2f(0.715,-0.335);
	glVertex2f(0.715,-0.215);
	glEnd();
	glFlush();

	
	glLineWidth(1);   //shoe1(ojb 2)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.670,-0.300);
	glVertex2f(0.670,-0.310);
	glVertex2f(0.695,-0.310);
	glVertex2f(0.695,-0.300);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0,0.752,1);
	glVertex2f(0.670,-0.300);
	glVertex2f(0.670,-0.310);
	glVertex2f(0.695,-0.310);
	glVertex2f(0.695,-0.300);
	glEnd();
	glFlush();


	glLineWidth(1);   //shoe2(ojb 2)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.660,-0.310);
	glVertex2f(0.715,-0.310);
	glVertex2f(0.715,-0.335);
	glVertex2f(0.660,-0.335);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0,0.752,1);
	glVertex2f(0.660,-0.310);
	glVertex2f(0.715,-0.310);
	glVertex2f(0.715,-0.335);
	glVertex2f(0.660,-0.335);
	glEnd();
	glFlush();
}



void object3()
{

		if(yr<=0.80)
		{
		glLineWidth(1);   //right hand1(obj3)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.760,-0.133);
	//glVertex2f(0.360,-0.15);
	glVertex2f(0.770,-0.133);
	glVertex2f(0.770,-0.22);
	glVertex2f(0.760,-0.22);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(0.760,-0.133);
	//glVertex2f(0.360,-0.15);
	glVertex2f(0.770,-0.133);
	glVertex2f(0.770,-0.22);
	glVertex2f(0.760,-0.22);
	glEnd();
	glFlush();
		}
		else
		{
				glLineWidth(1);   //right hand1(obj2)
        glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.750,-0.091);
	//glVertex2f(0.360,-0.15);
	glVertex2f(0.750,-0.123);
	glVertex2f(0.779,-0.040);
	glVertex2f(0.768,-0.035);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(0.750,-0.091);
	//glVertex2f(0.360,-0.15);
	glVertex2f(0.750,-0.123);
        glVertex2f(0.779,-0.040);
	glVertex2f(0.768,-0.035);
	glEnd();
	glFlush();

		}

	
	glPointSize(5);
    glBegin(GL_POINTS);	//eye3
	glColor3f(0,0,0);
	glVertex2f(0.784,-0.035);
	glEnd();
	glFlush();

			
	glBegin(GL_POLYGON);  //face3
	drawCircle(0.033,0.80,-0.041);
	glEnd();
	glFlush();

	glLineWidth(3);   //neck3
    glBegin(GL_LINE_LOOP);	
	glColor3f(0.545,0,0);
	glVertex2f(0.797,-0.041);
	//glVertex2f(0.397,-0.091);
	glVertex2f(0.81,-0.041);
	glVertex2f(0.797,-0.091);
	glVertex2f(0.81,-0.091);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.545,0,0);
	glVertex2f(0.797,-0.041);
	//glVertex2f(0.397,-0.091);
	glVertex2f(0.81,-0.041);
	glVertex2f(0.797,-0.091);
	glVertex2f(0.81,-0.091);
	glEnd();
	glFlush();

		glLineWidth(1);   //left arm1(obj3)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.815,-0.093);
	glVertex2f(0.825,-0.093);
	glVertex2f(0.825,-0.155);
	glVertex2f(0.815,-0.155);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.254,0.411,1);
	glVertex2f(0.815,-0.093);
	glVertex2f(0.825,-0.093);
	glVertex2f(0.825,-0.155);
	glVertex2f(0.815,-0.155);
	glEnd();
	glFlush();

		glLineWidth(1);   //left hand1(obj3)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.815,-0.155);
	glVertex2f(0.825,-0.155);
	glVertex2f(0.825,-0.200);
	glVertex2f(0.815,-0.200);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(0.815,-0.155);
	glVertex2f(0.825,-0.155);
	glVertex2f(0.825,-0.200);
	glVertex2f(0.815,-0.200);
	glEnd();
	glFlush();

		if(yr<=0.80)
		{
		glLineWidth(1);   //right arm1(obj3)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.760,-0.091);
	glVertex2f(0.760,-0.133);
	glVertex2f(0.770,-0.133);
	glVertex2f(0.770,-0.091);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.254,0.411,1);
	glVertex2f(0.760,-0.091);
	glVertex2f(0.760,-0.133);
	glVertex2f(0.770,-0.133);
	glVertex2f(0.770,-0.091);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
		}

	else
	{
			glLineWidth(1);   //right arm1(obj2)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.770,-0.091);
	glVertex2f(0.770,-0.113);
	glVertex2f(0.750,-0.113);
	glVertex2f(0.750,-0.091);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.254,0.411,1);
	glVertex2f(0.770,-0.091);
	glVertex2f(0.770,-0.113);
	glVertex2f(0.750,-0.113);
	glVertex2f(0.750,-0.091);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
}
	
	glLineWidth(1);   //body3
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.770,-0.091);
	glVertex2f(0.770,-0.215);
	glVertex2f(0.833,-0.215);
	glVertex2f(0.833,-0.091);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.752,0.752,0.752);
	glVertex2f(0.770,-0.091);
	glVertex2f(0.770,-0.215);
	glVertex2f(0.833,-0.215);
	glVertex2f(0.833,-0.091);
    glEnd();
	glFlush();


		glLineWidth(1);   //right leg3(object 3)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.780,-0.215);
	glVertex2f(0.780,-0.300);
	glVertex2f(0.795,-0.300);
	glVertex2f(0.795,-0.215);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.854,0.647,0.125);
	glVertex2f(0.780,-0.215);
	glVertex2f(0.780,-0.300);
	glVertex2f(0.795,-0.300);
	glVertex2f(0.795,-0.215);
	glEnd();
	glFlush();

	glLineWidth(1);   //left leg3(object 3)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.795,-0.215);
	glVertex2f(0.795,-0.335);
	glVertex2f(0.815,-0.335);
	glVertex2f(0.815,-0.215);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.854,0.647,0.125);
	glVertex2f(0.795,-0.215);
	glVertex2f(0.795,-0.335);
	glVertex2f(0.815,-0.335);
	glVertex2f(0.815,-0.215);
	glEnd();
	glFlush();


	glLineWidth(1);   //shoe1(ojb 1)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.770,-0.300);
	glVertex2f(0.770,-0.310);
	glVertex2f(0.795,-0.310);
	glVertex2f(0.795,-0.300);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0,0.752,1);
	glVertex2f(0.770,-0.300);
	glVertex2f(0.770,-0.310);
	glVertex2f(0.795,-0.310);
	glVertex2f(0.795,-0.300);
	glEnd();
	glFlush();


	glLineWidth(1);   //shoe2(ojb 2)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(0.760,-0.310);
	glVertex2f(0.815,-0.310);
	glVertex2f(0.815,-0.335);
	glVertex2f(0.760,-0.335);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0,0.752,1);
	glVertex2f(0.760,-0.310);
	glVertex2f(0.815,-0.310);
	glVertex2f(0.815,-0.335);
	glVertex2f(0.760,-0.335);
	glEnd();
	glFlush();

}

void object4()
{
	if(yr<=0.80)
	{
		glLineWidth(1);   //right hand1(obj4)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.625,-0.133);
	//glVertex2f(0.360,-0.15);
	glVertex2f(-0.615,-0.133);
	glVertex2f(-0.615,-0.22);
	glVertex2f(-0.625,-0.22);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(-0.625,-0.133);
	//glVertex2f(.660,-0.15);
	glVertex2f(-0.615,-0.133);
	glVertex2f(-0.615,-0.22);
	glVertex2f(-0.625,-0.22);
	glEnd();
	glFlush();  
	}
	else
	{
			glLineWidth(1);   //right hand1(obj4)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.625,-0.099);
	//glVertex2f(0.360,-0.15);
	glVertex2f(-0.625,-0.133);
		glVertex2f(-0.589,-0.036);
	glVertex2f(-0.600,-0.036);

	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(-0.625,-0.099);
	//glVertex2f(0.360,-0.15);
	glVertex2f(-0.625,-0.133);
	glVertex2f(-0.589,-0.036);
	glVertex2f(-0.600,-0.036);
	
	glEnd();
	glFlush();  

	}


	glPointSize(5);
    glBegin(GL_POINTS);	//eye4
	glColor3f(0,0,0);
	glVertex2f(-0.584,-0.035);
	glEnd();
	glFlush();
	

    glBegin(GL_POLYGON);  //face4
	drawCircle(0.033,-0.60,-0.041);
	glEnd();
	glFlush();

		glLineWidth(1);   //neck4
    glBegin(GL_LINE_LOOP);	
	glColor3f(0.545,0,0);
	glVertex2f(-0.597,-0.041);
	//glVertex2f(0.397,-0.091);
	glVertex2f(-0.61,-0.041);
	glVertex2f(-0.597,-0.091);
	glVertex2f(-0.61,-0.091);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.545,0,0);
	glVertex2f(-0.597,-0.041);
	//glVertex2f(0.397,-0.091);
	glVertex2f(-0.61,-0.041);
	glVertex2f(-0.597,-0.091);
	glVertex2f(-0.61,-0.091);
	glEnd();
	glFlush();

	
	glLineWidth(1);   //left arm1(obj4)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.570,-0.093);
	glVertex2f(-0.560,-0.093);
	glVertex2f(-0.560,-0.155);
	glVertex2f(-0.570,-0.155);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.254,0.411,1);
	glVertex2f(-0.570,-0.093);
	glVertex2f(-0.560,-0.093);
	glVertex2f(-0.560,-0.155);
	glVertex2f(-0.570,-0.155);
	glEnd();
	glFlush();

		glLineWidth(1);   //left hand1(obj4)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.570,-0.155);
	glVertex2f(-0.560,-0.155);
	glVertex2f(-0.560,-0.200);
	glVertex2f(-0.570,-0.200);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(-0.570,-0.155);
	glVertex2f(-0.560,-0.155);
	glVertex2f(-0.560,-0.200);
	glVertex2f(-0.570,-0.200);
	glEnd();
	glFlush();

	if(yr<=0.80)
	{
	glLineWidth(1);   //right arm1(obj4)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.625,-0.091);
	glVertex2f(-0.625,-0.133);
	glVertex2f(-0.615,-0.133);
	glVertex2f(-0.615,-0.091);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(-0.254,0.411,1);
	glVertex2f(-0.625,-0.091);
	glVertex2f(-0.625,-0.133);
	glVertex2f(-0.615,-0.133);
	glVertex2f(-0.615,-0.091);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
	}
	else
	{
		glLineWidth(1);   //right arm1(obj4)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.605,-0.099);
	glVertex2f(-0.625,-0.099);
	glVertex2f(-0.625,-0.118);
	glVertex2f(-0.605,-0.118);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(-0.254,0.411,1);
		glVertex2f(-0.605,-0.099);
	glVertex2f(-0.625,-0.099);
	glVertex2f(-0.625,-0.118);
	glVertex2f(-0.605,-0.118);
	//glVertex2f(0.368,-0.154);

	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();

	}

	
	


	glLineWidth(1);   //body4
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.570,-0.091);
	glVertex2f(-0.570,-0.215);
	glVertex2f(-0.633,-0.215);
	glVertex2f(-0.633,-0.091);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.752,0.752,0.752);
	glVertex2f(-0.570,-0.091);
	glVertex2f(-0.570,-0.215);
	glVertex2f(-0.633,-0.215);
	glVertex2f(-0.633,-0.091);
    glEnd();
	glFlush();


	glLineWidth(1);   //right leg3(object 4)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.580,-0.215);
	glVertex2f(-0.580,-0.300);
	glVertex2f(-0.595,-0.300);
	glVertex2f(-0.595,-0.215);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.854,0.647,0.125);
	glVertex2f(-0.580,-0.215);
	glVertex2f(-0.580,-0.300);
	glVertex2f(-0.595,-0.300);
	glVertex2f(-0.595,-0.215);
	glEnd();
	glFlush();

	glLineWidth(1);   //left leg3(object 4)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.595,-0.215);
	glVertex2f(-0.595,-0.335);
	glVertex2f(-0.615,-0.335);
	glVertex2f(-0.615,-0.215);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.854,0.647,0.125);
	glVertex2f(-0.595,-0.215);
	glVertex2f(-0.595,-0.335);
	glVertex2f(-0.615,-0.335);
	glVertex2f(-0.615,-0.215);
	glEnd();
	glFlush();


	glLineWidth(1);   //shoe1(ojb 4)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.570,-0.300);
	glVertex2f(-0.570,-0.310);
	glVertex2f(-0.595,-0.310);
	glVertex2f(-0.595,-0.300);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0,0.752,1);
	glVertex2f(-0.570,-0.300);
	glVertex2f(-0.570,-0.310);
	glVertex2f(-0.595,-0.310);
	glVertex2f(-0.595,-0.300);
	glEnd();
	glFlush();


	glLineWidth(1);   //shoe2(ojb 4)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.560,-0.310);
	glVertex2f(-0.615,-0.310);
	glVertex2f(-0.615,-0.335);
	glVertex2f(-0.560,-0.335);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0,0.752,1);
	glVertex2f(-0.560,-0.310);
	glVertex2f(-0.615,-0.310);
	glVertex2f(-0.615,-0.335);
	glVertex2f(-0.560,-0.335);
	glEnd();
	glFlush();

}
void object5()
{
	if(yr<=0.80)
	{
		
		glLineWidth(1);   //right hand1(obj5)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.725,-0.133);
	//glVertex2f(0.360,-0.15);
	glVertex2f(-0.715,-0.133);
	glVertex2f(-0.715,-0.22);
	glVertex2f(-0.725,-0.22);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.727,0.478);
	glVertex2f(-0.725,-0.133);
	//glVertex2f(.660,-0.15);
	glVertex2f(-0.715,-0.133);
	glVertex2f(-0.715,-0.22);
	glVertex2f(-0.725,-0.22);
	glEnd();
	glFlush();
	}
	else
	{
			glLineWidth(1);   //right hand1(obj5)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.725,-0.099);
	//glVertex2f(0.360,-0.15);
	glVertex2f(-0.725,-0.133);
		glVertex2f(-0.689,-0.036);
	glVertex2f(-0.700,-0.036);

	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(-0.725,-0.099);
	//glVertex2f(0.360,-0.15);
	glVertex2f(-0.725,-0.133);
	glVertex2f(-0.689,-0.036);
	glVertex2f(-0.700,-0.036);
	
	glEnd();
	glFlush();  

	}
	
		glPointSize(5);
    glBegin(GL_POINTS);	//eye5
	glColor3f(0,0,0);
	glVertex2f(-0.684,-0.035);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);  //face5
	drawCircle(0.033,-0.7,-0.041);
	glEnd();
	glFlush();

		glLineWidth(1);   //neck5
    glBegin(GL_LINE_LOOP);	
	glColor3f(0.545,0,0);
	glVertex2f(-0.697,-0.041);
	//glVertex2f(0.397,-0.091);
	glVertex2f(-0.71,-0.041);
	glVertex2f(-0.697,-0.091);
	glVertex2f(-0.71,-0.091);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.545,0,0);
	glVertex2f(-0.697,-0.041);
	//glVertex2f(0.397,-0.091);
	glVertex2f(-0.71,-0.041);
	glVertex2f(-0.697,-0.091);
	glVertex2f(-0.71,-0.091);
	glEnd();
	glFlush();

	
	glLineWidth(1);   //left arm1(obj5)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.670,-0.093);
	glVertex2f(-0.660,-0.093);
	glVertex2f(-0.660,-0.155);
	glVertex2f(-0.670,-0.155);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.254,0.411,1);
	glVertex2f(-0.670,-0.093);
	glVertex2f(-0.660,-0.093);
	glVertex2f(-0.660,-0.155);
	glVertex2f(-0.670,-0.155);
	glEnd();
	glFlush();

		glLineWidth(1);   //left hand1(obj5)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.670,-0.155);
	glVertex2f(-0.660,-0.155);
	glVertex2f(-0.660,-0.200);
	glVertex2f(-0.670,-0.200);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(-0.670,-0.155);
	glVertex2f(-0.660,-0.155);
	glVertex2f(-0.660,-0.200);
	glVertex2f(-0.670,-0.200);
	glEnd();
	glFlush();

	if(yr<=0.80)
	{
		glLineWidth(1);   //right arm1(obj5)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.725,-0.091);
	glVertex2f(-0.725,-0.133);
	glVertex2f(-0.715,-0.133);
	glVertex2f(-0.715,-0.091);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.254,0.411,1);
	glVertex2f(-0.725,-0.091);
	glVertex2f(-0.725,-0.133);
	glVertex2f(-0.715,-0.133);
	glVertex2f(-0.715,-0.091);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
	}
	


	glLineWidth(1);   //body5
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.670,-0.091);
	glVertex2f(-0.670,-0.215);
	glVertex2f(-0.733,-0.215);
	glVertex2f(-0.733,-0.091);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.752,0.752,0.752);
	glVertex2f(-0.670,-0.091);
	glVertex2f(-0.670,-0.215);
	glVertex2f(-0.733,-0.215);
	glVertex2f(-0.733,-0.091);
    glEnd();
	glFlush();


	glLineWidth(1);   //right leg3(object 5)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.680,-0.215);
	glVertex2f(-0.680,-0.300);
	glVertex2f(-0.695,-0.300);
	glVertex2f(-0.695,-0.215);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.854,0.647,0.125);
	glVertex2f(-0.680,-0.215);
	glVertex2f(-0.680,-0.300);
	glVertex2f(-0.695,-0.300);
	glVertex2f(-0.695,-0.215);
	glEnd();
	glFlush();

	glLineWidth(1);   //left leg3(object 5)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.695,-0.215);
	glVertex2f(-0.695,-0.335);
	glVertex2f(-0.715,-0.335);
	glVertex2f(-0.715,-0.215);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.854,0.647,0.125);
	glVertex2f(-0.695,-0.215);
	glVertex2f(-0.695,-0.335);
	glVertex2f(-0.715,-0.335);
	glVertex2f(-0.715,-0.215);
	glEnd();
	glFlush();


	glLineWidth(1);   //shoe1(ojb 5)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.670,-0.300);
	glVertex2f(-0.670,-0.310);
	glVertex2f(-0.695,-0.310);
	glVertex2f(-0.695,-0.300);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0,0.752,1);
	glVertex2f(-0.670,-0.300);
	glVertex2f(-0.670,-0.310);
	glVertex2f(-0.695,-0.310);
	glVertex2f(-0.695,-0.300);
	glEnd();
	glFlush();


	glLineWidth(1);   //shoe2(ojb 5)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.660,-0.310);
	glVertex2f(-0.715,-0.310);
	glVertex2f(-0.715,-0.335);
	glVertex2f(-0.660,-0.335);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0,0.752,1);
	glVertex2f(-0.660,-0.310);
	glVertex2f(-0.715,-0.310);
	glVertex2f(-0.715,-0.335);
	glVertex2f(-0.660,-0.335);
	glEnd();
	glFlush();
}
void object6()
{
	if(yr<=0.80)
	{
			glLineWidth(1);   //right hand1(obj6)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.825,-0.133);
	//glVertex2f(0.360,-0.15);
	glVertex2f(-0.815,-0.133);
	glVertex2f(-0.815,-0.22);
	glVertex2f(-0.825,-0.22);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.727,0.478);
	glVertex2f(-0.825,-0.133);
	//glVertex2f(.660,-0.15);
	glVertex2f(-0.815,-0.133);
	glVertex2f(-0.815,-0.22);
	glVertex2f(-0.825,-0.22);
	glEnd();
	glFlush();
	}
	else
	{
			glLineWidth(1);   //right hand1(obj6)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.825,-0.099);
	//glVertex2f(0.360,-0.15);
	glVertex2f(-0.825,-0.133);
		glVertex2f(-0.789,-0.036);
	glVertex2f(-0.800,-0.036);

	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(-0.825,-0.099);
	//glVertex2f(0.360,-0.15);
	glVertex2f(-0.825,-0.133);
	glVertex2f(-0.789,-0.036);
	glVertex2f(-0.800,-0.036);
	
	glEnd();
	glFlush();  

	}
	

		glPointSize(5);
    glBegin(GL_POINTS);	//eye6
	glColor3f(0,0,0);
	glVertex2f(-0.784,-0.035);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);  //face6
	drawCircle(0.033,-0.8,-0.041);
	glEnd();
	glFlush();

		glLineWidth(1);   //neck6
    glBegin(GL_LINE_LOOP);	
	glColor3f(0.545,0,0);
	glVertex2f(-0.797,-0.041);
	//glVertex2f(0.397,-0.091);
	glVertex2f(-0.81,-0.041);
	glVertex2f(-0.797,-0.091);
	glVertex2f(-0.81,-0.091);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.545,0,0);
	glVertex2f(-0.797,-0.041);
	//glVertex2f(0.397,-0.091);
	glVertex2f(-0.81,-0.041);
	glVertex2f(-0.797,-0.091);
	glVertex2f(-0.81,-0.091);
	glEnd();
	glFlush();

	
	glLineWidth(1);   //left arm1(obj6)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.770,-0.093);
	glVertex2f(-0.760,-0.093);
	glVertex2f(-0.760,-0.155);
	glVertex2f(-0.770,-0.155);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.254,0.411,1);
	glVertex2f(-0.770,-0.093);
	glVertex2f(-0.760,-0.093);
	glVertex2f(-0.760,-0.155);
	glVertex2f(-0.770,-0.155);
	glEnd();
	glFlush();

		glLineWidth(1);   //left hand1(obj6)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.770,-0.155);
	glVertex2f(-0.760,-0.155);
	glVertex2f(-0.760,-0.200);
	glVertex2f(-0.770,-0.200);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(1,0.627,0.478);
	glVertex2f(-0.770,-0.155);
	glVertex2f(-0.760,-0.155);
	glVertex2f(-0.760,-0.200);
	glVertex2f(-0.770,-0.200);
	glEnd();
	glFlush();

	if(yr<=0.80)
	{
		glLineWidth(1);   //right arm1(obj6)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.825,-0.091);
	glVertex2f(-0.825,-0.133);
	glVertex2f(-0.815,-0.133);
	glVertex2f(-0.815,-0.091);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.254,0.411,1);
	glVertex2f(-0.825,-0.091);
	glVertex2f(-0.825,-0.133);
	glVertex2f(-0.815,-0.133);
	glVertex2f(-0.815,-0.091);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
	}
	else
	{
		
		glLineWidth(1);   //right arm1(obj6)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.805,-0.099);
	glVertex2f(-0.825,-0.099);
	glVertex2f(-0.825,-0.118);
	glVertex2f(-0.805,-0.118);
	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(-0.254,0.411,1);
		glVertex2f(-0.805,-0.099);
	glVertex2f(-0.825,-0.099);
	glVertex2f(-0.825,-0.118);
	glVertex2f(-0.805,-0.118);
	//glVertex2f(0.368,-0.154);

	//glVertex2f(0.368,-0.154);
	glEnd();
	glFlush();

	}
	glLineWidth(1);   //body6
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.770,-0.091);
	glVertex2f(-0.770,-0.215);
	glVertex2f(-0.833,-0.215);
	glVertex2f(-0.833,-0.091);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.752,0.752,0.752);
	glVertex2f(-0.770,-0.091);
	glVertex2f(-0.770,-0.215);
	glVertex2f(-0.833,-0.215);
	glVertex2f(-0.833,-0.091);
    glEnd();
	glFlush();


	glLineWidth(1);   //right leg3(object 6)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.780,-0.215);
	glVertex2f(-0.780,-0.300);
	glVertex2f(-0.795,-0.300);
	glVertex2f(-0.795,-0.215);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.854,0.647,0.125);
	glVertex2f(-0.780,-0.215);
	glVertex2f(-0.780,-0.300);
	glVertex2f(-0.795,-0.300);
	glVertex2f(-0.795,-0.215);
	glEnd();
	glFlush();

	glLineWidth(1);   //left leg3(object 6)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.795,-0.215);
	glVertex2f(-0.795,-0.335);
	glVertex2f(-0.815,-0.335);
	glVertex2f(-0.815,-0.215);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0.854,0.647,0.125);
	glVertex2f(-0.795,-0.215);
	glVertex2f(-0.795,-0.335);
	glVertex2f(-0.815,-0.335);
	glVertex2f(-0.815,-0.215);
	glEnd();
	glFlush();


	glLineWidth(1);   //shoe1(ojb 6)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.770,-0.300);
	glVertex2f(-0.770,-0.310);
	glVertex2f(-0.795,-0.310);
	glVertex2f(-0.795,-0.300);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0,0.752,1);
	glVertex2f(-0.770,-0.300);
	glVertex2f(-0.770,-0.310);
	glVertex2f(-0.795,-0.310);
	glVertex2f(-0.795,-0.300);
	glEnd();
	glFlush();


	glLineWidth(1);   //shoe2(ojb 6)
    glBegin(GL_LINE_LOOP);	
	glColor3f(0,0,0);
	glVertex2f(-0.760,-0.310);
	glVertex2f(-0.815,-0.310);
	glVertex2f(-0.815,-0.335);
	glVertex2f(-0.760,-0.335);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glColor3f(0,0.752,1);
	glVertex2f(-0.760,-0.310);
	glVertex2f(-0.815,-0.310);
	glVertex2f(-0.815,-0.335);
	glVertex2f(-0.760,-0.335);
	glEnd();
	glFlush();
}



void flag()						// for flag appearance
{
	//glTranslatef(0.0f, yLocation, 0.0f); // Translate our object along the y axis  
  	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2f(-0.02,0.0+yr);
	glEnd();
	if(yr>=0.8)
	{
		drawandanimate();						//function calling waving flag
	}
	glFlush();
}

void lineForGreenPolygon()
{
	glLineWidth(1);
	glBegin(GL_LINE_LOOP);	// upper l segment polygon
	glColor3f(0,0,0);
	glVertex2f(-0.25,0.4);
	glVertex2f(-0.25,0.1);	//point
	//glVertex2f(-0.25,0.1);
	glVertex2f(-0.84,0.1);
	glVertex2f(-0.8,0.4);
	glEnd();
	glFlush();

	glBegin(GL_LINE_LOOP);
	glLineWidth(1);
	glColor3f(0,0,0);
	glVertex2f(-0.3,-1);          // lower l segment polygon
	glVertex2f(-0.3,-0.5);	//point
	//glVertex2f(-0.3,-0.5);
	glVertex2f(-0.925,-0.5);
	glVertex2f(-1,-1);
	glEnd();
	glFlush();

	    // upper r segment polygon
	glBegin(GL_LINE_LOOP);
	glLineWidth(1);
	glColor3f(0,0,0);
	glVertex2f(0.25,0.4);  //point
	glVertex2f(0.25,0.1);
	//glVertex2f(0.25,0.1);
	glVertex2f(0.842,0.1);
	glVertex2f(0.8,0.4);
	glEnd();
	glFlush();

	glBegin(GL_LINE_LOOP);      // lower r segment polygon
	glLineWidth(1);
	glColor3f(0,0,0); 
	glVertex2f(0.3,-1);   
	glVertex2f(0.3,-0.5);	//point
	//glVertex2f(0.3,-0.5);
	glVertex2f(0.928,-0.5);
	glVertex2f(1,-1);
	glEnd();
	glFlush();
}

void lineForCarpet()
{
	glColor3f(0,0,0);
	glLineWidth(1);            //line for the red carpet
	glBegin(GL_LINES);
	glVertex2f(0.15,0.4);	//top right
	glVertex2f(0.15,0);
	glVertex2f(0.15,0);
	glVertex2f(0.86,0);
	glVertex2f(0.915,-0.39);  // bottom right
	glVertex2f(0.15,-0.39);
	glVertex2f(0.15,-0.39);
	glVertex2f(0.15,-1);
	glVertex2f(-0.2,-1);		//bottom left
	glVertex2f(-0.2,-0.39);
	glVertex2f(-0.2,-0.39);
	glVertex2f(-0.915,-0.39);
	glVertex2f(-0.2,0.4);		//top left
	glVertex2f(-0.2,0);
	glVertex2f(-0.2,0);
	glVertex2f(-0.86,0);
	glEnd();
	glFlush();
}

void lineForBase()
{
	glBegin(GL_LINE_LOOP);
	glLineWidth(0.5);	//line for top flag's base
	glColor3f(0,0,0);
	glVertex2f(-0.10,-0.04);
	glVertex2f(0.09,-0.04);
	glVertex2f(0.06,-0.21);
	glVertex2f(-0.13,-0.21);
	glEnd();
	glFlush();

	glBegin(GL_LINE_LOOP);
	glLineWidth(0.5);		// line for flag's base
	glColor3f(0,0,0);
	glVertex2f(0.06,-0.21);
	glVertex2f(-0.13,-0.21);
	glVertex2f(-0.13,-0.25);
	glVertex2f(0.06,-0.25);
	glEnd();
	glFlush();

	glBegin(GL_LINE_LOOP);
	glLineWidth(0.5);			// line for flag's base
	glColor3f(0,0,0);
	glVertex2f(0.09,-0.04);
	glVertex2f(0.06,-0.21);
	glVertex2f(0.06,-0.25);
	glVertex2f(0.09,-0.08);
	glEnd();
	glFlush();

	glBegin(GL_LINE_LOOP);
	glLineWidth(0.5);					// bottom line flag's base
	glColor3f(0,0,0);
	glVertex2f(-0.15,0);
	glVertex2f(0.15,0);
	glVertex2f(0.1,-0.3);
	glVertex2f(-0.2,-0.3);
	glEnd();
	glFlush();

	glBegin(GL_LINE_LOOP);
	glLineWidth(0.5);					//line  flag's base
	glColor3f(0,0,0);
	glVertex2f(0.1,-0.3);
	glVertex2f(-0.2,-0.3);
	glVertex2f(-0.2,-0.39);
	glVertex2f(0.1,-0.39);
	glEnd();
	glFlush();

	glBegin(GL_LINE_LOOP);
	glLineWidth(0.5);				// line flag's base
	glColor3f(0,0,0);
	glVertex2f(0.1,-0.3);
	glVertex2f(0.1,-0.39);
	glVertex2f(0.15,-0.1);
	glVertex2f(0.15,0);
	glEnd();
	glFlush();
	
	glColor3f(0,0,0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);            //line  for base
	glVertex3f(0.8,0.4,0);
	glVertex3f(1,-1,0);
	glVertex3f(-1,-1,0);
	glVertex3f(-0.8,0.4,0);
	glEnd();
	glFlush();
}

void flagBase()
{
	glLineWidth(7);            //flag's stick
	//glPointSize(10);
	glColor3f(0,0,0);
	glBegin(GL_LINES);
	glVertex2f(-0.02,-0.12);
	glVertex2f(-0.02,0.8);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);	// top flag's base
	glColor3f(0.117,0.565,1);
	glVertex2f(-0.10,-0.04);
	glVertex2f(0.09,-0.04);
	glVertex2f(0.06,-0.21);
	glVertex2f(-0.13,-0.21);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);	// flag's base
	glColor3f(1,1,0);
	glVertex2f(0.06,-0.21);
	glVertex2f(-0.13,-0.21);
	glVertex2f(-0.13,-0.25);
	glVertex2f(0.06,-0.25);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);	// flag's base
	glColor3f(1,1,0);
	glVertex2f(0.09,-0.04);
	glVertex2f(0.06,-0.21);
	glVertex2f(0.06,-0.25);
	glVertex2f(0.09,-0.08);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);	// bottom flag's base
	glColor3f(0.117,0.565,1);
	glVertex2f(-0.15,0);
	glVertex2f(0.15,0);
	glVertex2f(0.1,-0.3);
	glVertex2f(-0.2,-0.3);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);	// flag's base
	glColor3f(1,1,0);
	glVertex2f(0.1,-0.3);
	glVertex2f(-0.2,-0.3);
	glVertex2f(-0.2,-0.39);
	glVertex2f(0.1,-0.39);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);	// flag's base
	glColor3f(1,1,0);
	glVertex2f(0.1,-0.3);
	glVertex2f(0.1,-0.39);
	glVertex2f(0.15,-0.1);
	glVertex2f(0.15,0);
	glEnd();
	glFlush();
}

void redCarpet()
{
	glBegin(GL_POLYGON);	// horizontal red carpet
	glColor3f(0.9,0,0);
	glVertex2f(-0.86,0);
	glVertex2f(0.86,0);
	glVertex2f(0.915,-0.39);
	glVertex2f(-0.915,-0.39);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);	//  vertical red carpet
	glColor3f(0.9,0,0);
	glVertex2f(-0.2,0.4);
	glVertex2f(0.15,0.4);
	glVertex2f(0.15,-1);
	glVertex2f(-0.2,-1);
	glEnd();
	glFlush();   
}

void bases()
{
	glBegin(GL_POLYGON);	// upper l segment polygon
	glColor3f(0,0.5,0);
	glVertex2f(-0.25,0.4);
	glVertex2f(-0.25,0.1);	//point
	//glVertex2f(-0.25,0.1);
	glVertex2f(-0.84,0.1);
	glVertex2f(-0.8,0.4);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);
	glColor3f(0,0.5,0);
	glVertex2f(-0.3,-1);          // lower l segment polygon
	glVertex2f(-0.3,-0.5);	//point
	//glVertex2f(-0.3,-0.5);
	glVertex2f(-0.925,-0.5);
	glVertex2f(-1,-1);
	glEnd();
	glFlush();
	
	glBegin(GL_POLYGON);		 // upper r segment polygon
	glColor3f(0,0.5,0);
	glVertex2f(0.25,0.4);  //point
	glVertex2f(0.25,0.1);
	//glVertex2f(0.25,0.1);
	glVertex2f(0.842,0.1);
	glVertex2f(0.8,0.4);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);      // lower r segment polygon
	glColor3f(0,0.5,0); 
	glVertex2f(0.3,-1);   
	glVertex2f(0.3,-0.5);	//point
	//glVertex2f(0.3,-0.5);
	glVertex2f(0.928,-0.5);
	glVertex2f(1,-1);
	glEnd();
	glFlush();

	glColor3f(0.7,0.7,0.7);
	glBegin(GL_POLYGON);            //polygon for base
	glVertex3f(0.8,0.4,0);
	glVertex3f(1,-1,0);
	glVertex3f(-1,-1,0);
	glVertex3f(-0.8,0.4,0);
	glEnd();
	glFlush();

}
void myinit()
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1,1,-1,1);
}

void menu(int id)
{
	switch(id)
	{

		case 2:  exit(0);
		break;
	}
	glutPostRedisplay();
}


void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920,1080);
	glutCreateWindow("CG_PROJECT");
	//glutFullScreen();
	glutDisplayFunc(startdisplay);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keystroke);
	glutSpecialFunc(keys);
	myinit();
	glEnable(GLUT_DEPTH);	
	glutCreateMenu(menu);
	glutAddMenuEntry("exit",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}

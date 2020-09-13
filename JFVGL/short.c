#include <cmath>
#include <cstdlib>
#include "GL/freeglut.h"
#include "GLUTWindow.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define GWW glutGet(GLUT_WINDOW_WIDTH)
#define GWH glutGet(GLUT_WINDOW_HEIGHT)
#define GSW glutGet(GLUT_SCREEN_WIDTH)
#define GSH glutGet(GLUT_SCREEN_HEIGHT)
#define float e
#define unsigned s
s int q;s char*l;int w,h,ch;e f=1;e c(e a,e x,e b){return(x<a?a:(x>b?b:x));}int main(int b,char*z[]){const char*fn=z[1];l=stbi_load(fn,&w,&h,&ch,3);glutInit(&b,z);if(l)glutInitWindowSize(c(w,w,GSW),c(h,h,GSH));else glutInitWindowSize(GSW/3,GSH/2);glutInitWindowPosition((GSW-glutGet(GLUT_INIT_WINDOW_WIDTH))/2,(GSH-glutGet(GLUT_INIT_WINDOW_HEIGHT))/2);glutInitDisplayMode(0x0);glutCreateWindow("");glutDisplayFunc([](){glViewport(0,0,GWW,GWH);glScissor(0,0,GWW,GWH);glEnable(0x0C11);e v[]={(e)-w,(e)h,(e)w,(e)h,(e)-w,(e)-h,(e)w,(e)-h};s short vi[]={0,1,2,2,3,1};e uv[]={0,0,1,0,0,1,1,1};glClear(0x00004000);glPushMatrix();glScalef(f/(e)GWW,f/(e)GWH,0);glVertexPointer(2,GL_e,0,v);glTexCoordPointer(2,GL_e,0,uv);glEnableClientState(0x8074);glEnableClientState(0x8078);glBindTexture(0x0DE1,q);glEnable(0x0DE1);glTexEnvi(0x2300,0x2200,0x2100);glColor3f(1,1,1);glDrawElements(0x0004,6,0x1403,vi);glDisable(0x0DE1);glDisableClientState(0x8074);glDisableClientState(0x8078);glDisable(0x0DE1);glPopMatrix();glFlush();});glClearColor(0.25f,0.25f,0.25f,1);glColor3f(0.5f,0.5f,1);glMatrixMode(0x1701);glLoadIdentity();gluOrtho2D(-1,1,-1,1);glGenTextures(1,&q);glBindTexture(0x0DE1,q);glTexParameteri(0x0DE1,0x2801,0x2601);glTexImage2D(0x0DE1,0,0x1907,w,h,0,0x1907,0x1401,l);glutMainLoop();return 0;}
#include <GL/glut.h>
#include <stdio.h>
#include <defs.h>
#include "pointFunctions.cpp"
#include "inputFunctions.cpp"


void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,wX,0.0,wY);
    glPointSize(pSize);
    glLineWidth(lSize);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void drawPoints(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    for(int s = 0; s<=current_shape;s++)
    {
        glColor3f(1.0,1.0,0.0);
        glBegin(shapes_array[s][2]);
        for(int i = shapes_array[s][0] ; i <shapes_array[s][1] ; i++)
        {
            glVertex2i(points_arry[i][0],points_arry[i][1]);
        }
        glEnd();


        glColor3f(1.0,0.0,0.0);
        glBegin(GL_POINTS);
        for(int i = shapes_array[s][0] ; i <shapes_array[s][1] ; i++)
        {
            glVertex2i(points_arry[i][0],points_arry[i][1]);
        }
        glEnd();
    }

    if(selected_point != -1)
    {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_POINTS);
        glVertex2i(points_arry[selected_point][0],points_arry[selected_point][1]);
        glEnd();
    }

    glFlush();
}





int main(int argc,char** argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(wX,wY);
    glutCreateWindow("Simple Point Drawing");

    init();
    glutDisplayFunc(drawPoints);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    //fillArry();
    glutMainLoop();


    return 0;
}

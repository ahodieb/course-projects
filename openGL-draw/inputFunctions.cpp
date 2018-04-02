#include <defs.h>
#include <GL/glut.h>

void generateCode()
{

    FILE* f = fopen("generated.txt","w");
    fprintf(f,"//Vertix Count %d\n",current_point);
    fprintf(f,"//Window Size  %d,%d\n",wX,wY);
    fprintf(f,"void displayfunction() {\n");
    fprintf(f,"glClear(GL_COLOR_BUFFER_BIT);\n");
    fprintf(f,"glColor3f(0.0,0.0,0.0);\n");
    fprintf(f,"glBegin(GL_LINE_STRIP);\n");

    for(int i = 0;i<current_point ; i++)
    {
        fprintf(f,"glVertex2i(%d,%d);\n",points_arry[i][0],points_arry[i][1]);
    }
    fprintf(f,"glEnd();\nglFlush();\n}");

    fclose(f);
}

void motion(int x, int y)
{
    if(selected_point != -1)
    {
        points_arry[selected_point][0] = x;
        points_arry[selected_point][1] = wY - y;

    }
    glutPostRedisplay();
}

void mouse( int button, int state, int x, int y )
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        selectPoint(x,y);
        if (selected_point == -1)
        {
            addPoint(x,wY-y);
        }
    }

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        selectPoint(x,y);
        if (selected_point !=-1)
        {
            deletePoint(selected_point);
            selected_point = -1;
        }
    }
    glutPostRedisplay();
}


void keyboard(unsigned char key , int x ,int y)
{
    if(key == 'c')
    {
        current_point = 0;
        current_shape = -1;
        selected_point = -1;

    }

    else if (key == 'g')
    {
        generateCode();

    }
    else if (key == 'n')
    {
        newShape();
    }

    else if ( key == '1')
    {
        shapes_array[current_shape][2] = GL_LINES;
    }
    else if ( key == '2')
    {
        shapes_array[current_shape][2] = GL_LINE_STRIP;
    }
    else if ( key == '3')
    {
        shapes_array[current_shape][2] = GL_LINE_LOOP;
    }
    else if ( key == '4')
    {
        shapes_array[current_shape][2] = GL_POINTS;
    }

    else if ( key == '5')
    {
        shapes_array[current_shape][2] = 6
                                         ;
    }

    glutPostRedisplay();
}


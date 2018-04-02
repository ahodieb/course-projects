#include <defs.h>
#include <GL/glut.h>

void addPoint(int x , int y)
{
    if(current_shape == -1)
        newShape();

    if (current_point < maxPoints)
    {
        points_arry[current_point][0] = x;
        points_arry[current_point][1] = y;

        current_point ++;

        shapes_array[current_shape][1] = current_point;
        selected_point = current_point -1;
    }
}



int selectPoint(int x , int y)
{
    for (int i = 0 ;i<current_point;i++)
    {
        int cx =points_arry[i][0];
        int cy = wY - points_arry[i][1];
        int p = pSize/2;

        if ( cx < x + p && cx > x - p)
        {
            if ( (cy > y - p) &&  (cy < y+p))
            {
                selected_point = i;
                return i;
            }
        }

    }
    selected_point = -1;
    return -1;

}

void deletePoint(int indx)
{
    for (int i = indx ;i< current_point-1 ; i ++  )
    {
        points_arry[i][0] = points_arry[i+1][0];
        points_arry[i][1] = points_arry[i+1][1];
    }
    current_point --;
}


void newShape()
{
    current_shape ++;
    shapes_array[current_shape][0] = current_point;
    shapes_array[current_shape][2] = GL_LINE_LOOP;

}




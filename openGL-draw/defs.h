#ifndef DEFFINITIONS_H
#define DEFFINITIONS_H
#define wX 800
#define wY 500

#define pSize 10
#define lSize 4

#define maxPoints 200


void addPoint(int x , int y);
int selectPoint(int x,int y);
void deletePoint(int indx);
void newShape();


int points_arry[maxPoints][2];
int shapes_array[maxPoints][3];

int current_shape = -1;
int current_point = 0;
int selected_point = 0;


#endif // DEFFINITIONS_H

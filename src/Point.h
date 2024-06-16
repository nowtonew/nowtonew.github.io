#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>

using namespace std;

#ifndef _POINT_H_
#define _POINT_H_

class Point
{
private:
    int p_x;
    int p_y;

public:
    void setPoint(int x, int y);
    int getPX();
    int getPY();
};

#endif
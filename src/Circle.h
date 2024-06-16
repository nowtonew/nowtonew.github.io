// #pragma once
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include "Point.h"

using namespace std;

class Circle
{
private:
    int c_r;        // 半径
    Point c_center; // 圆心

public:
    void setCR(int r);
    void setCenter(int x, int y);
    int getCX();
    int getCY();
    int getCR();
    void getDistence(Point &p);
};
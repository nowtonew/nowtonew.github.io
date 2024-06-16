#include "Circle.h"
#include "Point.h"

void Circle::setCR(int r)
{
    c_r = r;
}
void Circle::setCenter(int x, int y)
{
    c_center.setPoint(x, y);
}
int Circle::getCX()
{
    return c_center.getPX();
}
int Circle::getCY()
{
    return c_center.getPY();
}
int Circle::getCR()
{
    return c_r;
}
void Circle::getDistence(Point &p)
{
    int dis = (p.getPX() - c_center.getPX()) * (p.getPX() - c_center.getPX()) + (p.getPY() - c_center.getPY()) * (p.getPY() - c_center.getPY());
    if (dis == c_r * c_r)
        cout << "点在圆上" << endl;
    if (dis < c_r * c_r)
        cout << "点在圆内" << endl;
    if (dis > c_r * c_r)
        cout << "点在圆外" << endl;
}
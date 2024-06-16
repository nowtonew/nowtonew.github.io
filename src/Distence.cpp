#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>

#include "Point.h"
#include "Circle.h"

using namespace std;

int trap(vector<int> &height)
{
    int n = height.size();
    cout << "n的值为: " << n << endl;
    int start = 0, sum = 0;
    int end = start + 1;
    cout << "end的值为: " << end << endl;
    while (end < n)
    {
        if (height[end] < height[start])
        {
            end++;
            if (start < n && end == n)
            {
                start = start + 1;
                end = start + 1;
            }
        }
        else
        {
            cout << "此时end的值为: " << end << endl;
            for (int t = start + 1; t < end; t++)
            {
                sum += height[start] - height[t];
                cout << "此时sum的值为: " << sum << endl;
            }
            start = end;
            end++;
        }
    }
    return sum;
}

// int main()
// {
//     cout << "test---------" << endl;
//     vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
//     int res = trap(height);
//     cout << res << endl;
// }

// int main()
// {
//     Circle c;
//     Point p;
//     c.setCR(10);
//     c.setCenter(1, 1);
//     p.setPoint(1, 11);
//     c.getDistence(p);
//     return 0;
// }
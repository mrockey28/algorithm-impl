#include "ConvexHull.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

void OrderArray(vector<Point2D>& input, uint32_t lowIndex)
{
    Point2D s(input[lowIndex]);
    std::sort(input.begin(), input.end(), [&s] (Point2D a, Point2D b) {
        if (a == s) return true;
        else if (b == s) return false;
        else if (a.y - s.y == 0 && b.y - s.y == 0) return a.x < b.x;
        else if (a.y - s.y == 0) return true;
        else if (b.y - s.y == 0) return false;
        else if (a.x - s.x == 0 && b.x - s.x == 0) return a.y < b.y;
        else if (a.x - s.x == 0) return b.x - s.x < 0;
        else if (b.x - s.x == 0) return a.x - s.x > 0;
        else if (a.x - s.x > 0 && b.x - s.x < 0) return true;
        else if (a.x - s.x < 0 && b.x - s.x > 0) return true;
        else 
        {
            float slopea = float(a.y - s.y)/float(a.x - s.x);
            float slopeb = float(b.y - s.y)/float(b.x - s.x);
            if (slopea == slopeb) return (abs(a.x) < abs(b.x));
            else return (slopea < slopeb);
        }
        return false;
    });
}

//Time O(n)
uint32_t GetStartPoint(const vector<Point2D>& input)
{
    uint32_t lp = 0;
    for (uint32_t i = 0; i < input.size(); i++)
    {
        if (input[i].y < input[lp].y || (input[i].y == input[lp].y && input[i].x < input[lp].x))
        {
            lp = i;
        }
    }
    return lp;
}

int GetCrossProduct(Point2D& p1, Point2D& p2, Point2D& p3)
{
    return (p2.x - p1.x)*(p3.y - p1.y) -
            (p2.y - p1.y)*(p3.x - p1.x);
}


vector<Point2D> convexhull(vector<Point2D>& input)
{
    if (input.size() < 3) throw std::runtime_error("Need more than 2 points to compute hull!");

    //Get lowest starting point (and furthest to left, if tie)
    uint32_t sI = GetStartPoint(input);

    //Order the array, in order of angle from X-axis.
    OrderArray(input, sI);

    //Start by assuming the first two points are on the hull.
    vector<Point2D> hull({input[0], input[1]});
    for (uint32_t i = 2; i < input.size(); i++)
    {
        while (hull.size() > 1 && GetCrossProduct(*(hull.end()-2), *(hull.end()-1), input[i]) <= 0) hull.pop_back();
        hull.push_back(input[i]);
    }

    return hull;
}



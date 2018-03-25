#include <stdint.h>

class Point2D
{
public:
    Point2D(int inX, int inY) : x(inX), y(inY) {};
    bool operator==(const Point2D& o) const { return (x == o.x && y == o.y);};
    int32_t x;
    int32_t y;
};

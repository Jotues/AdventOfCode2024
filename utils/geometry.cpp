#include "geometry.hh"

namespace utils
{
    std::ostream& operator<<(std::ostream& os, const Point& pt)
    {
        os<< "P{" << pt.x << ", " << pt.y << "}\n";
        return os;
    }

    Point Point::operator+(const Point& pt) const
    {
        return Point{x + pt.x, y + pt.y};
    }

    Point& Point::operator+=(const Point& pt)
    {
        x += pt.x;
        y += pt.y;
        return *this;
    }

    Point Point::operator*(const int32_t val) const
    {
        return Point{x*val, y*val};
    }

    Point& Point::operator*=(const int32_t val)
    {
        x *= val;
        y *= val;
        return *this;
    }

    // bool Point::operator==(const Point& pt) const
    // {
    //     return (x == pt.x && y == pt.y);
    // }
}
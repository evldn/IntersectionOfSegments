#include "Segments.h"

//-------------------------[POINT]-------------------------

Point::Point(const Point& point)
{
	x = point.x;
	y = point.y;
	type = point.type;
	id = point.id;
}

bool Point::operator< (const Point& point)
{
	if ((x < point.x) || ((x == point.x) && (y < point.y)))
	{
		return true;
	}
	return false;
}
bool Point::operator> (const Point& point)
{
	if ((x > point.x) || ((x == point.x) && (y > point.y)))
	{
		return true;
	}
	return false;
}
Point& Point::operator=(const Point& point)
{
	if (this == &point)
	{
		return *this;
	}
	x = point.x;
	y = point.y;
	id = point.id;
	type = point.type;
	return *this;
}

//-------------------------[SEGMENT]-------------------------

Segment::Segment(Point a, Point b, int _id)
{
	id = _id;
	if (a < b)
	{
		begin = a;
		end = b;
	}
	else
	{
		begin = b;
		end = a;
	}
	begin.type = -1;
	end.type = 1;
	begin.id = id;
	end.id = id;
}
Segment::Segment(const Segment& segment)
{
	begin = segment.begin;
	end = segment.end;
	id = segment.id;
}
Segment::Segment(double x1, double y1, double x2, double y2, int _id) : id(_id)
{
	begin = Point(x1, y1, -1, id);
	end = Point(x2, y2, 1, id);
}

Segment& Segment::operator=(Segment& segment)
{
	if (this == &segment)
	{
		return *this;
	}
	begin = segment.begin;
	end = segment.end;
	id = segment.id;
	return *this;
}
double Segment::GetY(double x) const
{
	if (abs(begin.x - end.x) < EPS)  return begin.y;
	return begin.y + (end.y - begin.y) * (x - begin.x) / (end.x - begin.x);
}
bool Segment::operator==(const Segment& segment)
{
	if (id == segment.id)
		return true;
	return false;
}
bool Segment::operator!=(const Segment& segment)
{
	if (id != segment.id)
		return true;
	return false;
}
bool Segment::operator< (const Segment& b)
{
	double x = std::max(std::min(begin.x, end.x), std::min(b.begin.x, b.end.x));
	return GetY(x) < b.GetY(x);
}
bool Segment::operator>(const Segment& b)
{
	double x = std::max(std::min(begin.x, end.x), std::min(b.begin.x, b.end.x));
	return GetY(x) > b.GetY(x);
}
bool Segment::operator<=(const Segment& b)
{
	double x = std::max(std::min(begin.x, end.x), std::min(b.begin.x, b.end.x));
	return GetY(x) <= b.GetY(x);
}
bool Segment::operator>=(const Segment& b)
{
	double x = std::max(std::min(begin.x, end.x), std::min(b.begin.x, b.end.x));
	return GetY(x) >= b.GetY(x);
}
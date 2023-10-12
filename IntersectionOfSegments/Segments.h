#pragma once
#ifndef INTERSECTION_OF_SEGMENTS_SEGMENTS_H_
#define INTERSECTION_OF_SEGMENTS_SEGMENTS_H_
#include <ostream>
#include <algorithm>

struct Point {
	//-------------------------[FIELDS]-------------------------
	double x, y;
	int id; //segment id
	char type; //-1 - begin, 1 - end, 0 - default
	Point(double _x = 0, double _y = 0, char _type = 0, int _id = -1) : 
		x(_x), y(_y), type(_type), id(_id) {}
	//-------------------------[CONSTRUCTORS]-------------------------
	Point(const Point& point)
	{
		x = point.x;
		y = point.y;
		type = point.type;
		id = point.id;
	}

	//-------------------------[OPERATORS]-------------------------
	bool operator< (const Point& point)
	{
		if ((this->x < point.x) || ((this->x == point.x) && (this->y < point.y)))
		{
			return true;
		}
		return false;
	}
	Point& operator=(const Point& point)
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

	//-------------------------[OUTPUT]-------------------------
	friend std::ostream& operator<<(std::ostream& out, const Point& point)
	{
		return out << "( " << point.x << " , " << point.y << " )";
	}
};

struct Segment {
	//-------------------------[FIELDS]-------------------------
	Point begin, end;
	int id;
public:
	//-------------------------[CONSTRUCTORS]-------------------------
	Segment(const Segment& segment)
	{
		begin = segment.begin;
		end = segment.end;
		id = segment.id;
	}
	Segment(double x1, double y1, double x2, double y2, int _id) : id(_id)
	{
		begin = Point(x1, y1, -1, id);
		end = Point(x2, y2, 1, id);
	}

	//-------------------------[OPERATORS]-------------------------
	Segment& operator=(Segment& segment)
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
	bool operator<(const Segment& segment)
	{
		if (begin.y <= segment.begin.y)
		{
			return true;
		}
		return false;
	}
	bool operator>(const Segment& segment)
	{
		if (begin.y >= segment.begin.y)
		{
			return true;
		}
		return false;
	}
	bool operator==(const Segment& segment)
	{
		if(id == segment.id)
			return true;
		return false;
	}
};
#endif
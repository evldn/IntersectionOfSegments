#pragma once
#ifndef INTERSECTION_OF_SEGMENTS_SEGMENTS_H_
#define INTERSECTION_OF_SEGMENTS_SEGMENTS_H_

#include <ostream>
#include <algorithm>
const double EPS = 1E-9;

struct Point 
{
	//-------------------------[FIELDS]-------------------------
	double x, y;
	int id; //segment id
	char type; //-1 - begin, 1 - end, 0 - default
	//-------------------------[CONSTRUCTORS]-------------------------
	Point(double _x = 0, double _y = 0, char _type = 0, int _id = -1) : x(_x), y(_y), type(_type), id(_id) {}
	Point(const Point& point);
	//-------------------------[OPERATORS]-------------------------
	bool operator< (const Point& point);
	bool operator> (const Point& point);
	Point& operator=(const Point& point);
	//-------------------------[OUTPUT]-------------------------
	friend std::ostream& operator<<(std::ostream& out, const Point& point)
	{
		return out << "( " << point.x << " , " << point.y << " )";
	}
};

struct Segment 
{
	//-------------------------[FIELDS]-------------------------
	Point begin, end;
	int id;
public:
	//-------------------------[CONSTRUCTORS]-------------------------
	Segment() : begin(0, 0), end(0, 0), id(-1) {}
	Segment(Point a, Point b, int _id);
	Segment(const Segment& segment);
	Segment(double x1, double y1, double x2, double y2, int _id);
	//-------------------------[OPERATORS]-------------------------
	Segment& operator=(Segment& segment);
	double GetY(double x) const;
	bool operator==(const Segment& segment);
	bool operator!=(const Segment& segment);
	bool operator< (const Segment& b);
	bool operator>(const Segment& b);
	bool operator<=(const Segment& b);
	bool operator>=(const Segment& b);
};
#endif
#pragma once
#include "AVLTree.h"
#include "2,3-Tree.h"
#include "Segments.h"

int Vec(const Point& a, const Point& b, const Point& c);
bool IntersectProjection(double b1, double e1, double b2, double e2);
bool Intersect(Segment& a, Segment& b);
namespace AVL 
{
	bool IntersectionEffective(std::vector<Segment>& S);
}
namespace TwoThird
{
	bool IntersectionEffective(std::vector<Segment>& S);
}
#pragma once
#include "AVLTree.h"

double Area(Point& a, Point& b, Point& c);
bool IntersectProjection(double& b1, double& e1, double& b2, double& e2);
bool Intersect(Segment& a, Segment& b);
bool IntersectionEffective(std::vector<Segment>& S);
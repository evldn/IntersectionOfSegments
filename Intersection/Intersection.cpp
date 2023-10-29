#include "Intersection.h"

bool IntersectProjection(double l1, double r1, double l2, double r2) 
{
	if (l1 > r1)  std::swap(l1, r1);
	if (l2 > r2)  std::swap(l2, r2);
	return std::max(l1, l2) <= std::min(r1, r2) + EPS;
}
int Vec(const Point& a, const Point& b, const Point& c) 
{
	double multiply = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	return abs(multiply) < EPS ? 0 : multiply > 0 ? +1 : -1;
}
bool Intersect(Segment& a, Segment& b) 
{
	return IntersectProjection(a.begin.x, a.end.x, b.begin.x, b.end.x)
		&& IntersectProjection(a.begin.y, a.end.y, b.begin.y, b.end.y)
		&& Vec(a.begin, a.end, b.begin) * Vec(a.begin, a.end, b.end) <= 0
		&& Vec(b.begin, b.end, a.begin) * Vec(b.begin, b.end, a.end) <= 0;
}
namespace AVL 
{
	bool IntersectionEffective(std::vector<Segment>& S)
	{
		AVLTree<Segment> L;
		std::vector<Point> point;
		for (int i = 0; i < S.size(); ++i)
		{
			point.push_back(S[i].begin);
			point.push_back(S[i].end);
		}
		std::sort(point.begin(), point.end());
		for (int i = 0; i < 2 * S.size(); ++i)
		{
			Point p = point[i];
			Segment s = S[p.id];
			if (p.type == -1)
			{
				L.Insert(s);
				Segment s1 = L.Over(s);
				Segment s2 = L.Under(s);
				if (Intersect(s1, s) || Intersect(s2, s))
				{
					return true;
				}
			}
			else
			{
				Segment s1 = L.Over(s);
				Segment s2 = L.Under(s);
				if (Intersect(s1, s2))
				{
					return true;
				}
				L.Remove(s);
			}
		}
		return false;
	}
}
namespace TwoThree
{
	bool IntersectionEffective(std::vector<Segment>& S)
	{
		TwoThirdTree::TwoThreeTree<Segment> L;
		std::vector<Point> point;
		for (int i = 0; i < S.size(); ++i)
		{
			point.push_back(S[i].begin);
			point.push_back(S[i].end);
		}
		std::sort(point.begin(), point.end());
		for (int i = 0; i < 2 * S.size(); ++i)
		{
			Point p = point[i];
			Segment s = S[p.id];
			if (p.type == -1)
			{
				L.Insert(s);
				Segment s1 = L.Under(s);
				Segment s2 = L.Over(s);
				if (Intersect(s1, s) || Intersect(s2, s))
				{
					return true;
				}
			}
			else
			{
				Segment s1 = L.Under(s);
				Segment s2 = L.Over(s);
				if (Intersect(s1, s2))
				{
					return true;
				}
				L.Remove(s);
			}
		}
		return false;
	}
}
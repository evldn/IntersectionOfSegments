#include "AVLTree.h"
#include "Segments.h"
#include <vector>

const int n = 2;

double Area(Point a, Point b, Point c) {
	double s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	return abs(s) < EPS ? 0 : s > 0 ? +1 : -1;
	//return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool IntersectProjection(double b1, double e1, double b2, double e2)
{
	if (b1 > e1)  std::swap(b1, e1);
	if (b2 > e2)  std::swap(b2, e2);
	return std::max(b1, b2) <= std::min(e1, e2) + EPS;
}

bool Intersect(const Segment& a, const Segment& b) {
	if ((&a == nullptr) || (&b == nullptr))
		return false;
	return IntersectProjection(a.begin.x, a.end.x, b.begin.x, b.end.x)
		&& IntersectProjection(a.begin.y, a.end.y, b.begin.y, b.end.y)
		&& ((Area(a.begin, a.end, b.begin) * Area(a.begin, a.end, b.end)) <= 0)
		&& ((Area(b.begin, b.end, a.begin) * Area(b.begin, b.end, a.end)) <= 0);
}

bool IntersectionEffective(std::vector<Segment> S)
{
	AVLTree<Segment> L;
	std::vector<Point> point;
	for (int i = 0; i < n; ++i)
	{
		point.push_back(S[i].begin);
		point.push_back(S[i].end);
	}
	std::sort(point.begin(), point.end()); // лексикографическая сортировка 2n концов отрезков
	for (int i = 0; i < 2 * n; ++i)
	{
		Point p = point[i];
		Segment s = S[p.id];
		s.intersection_point = p;
		if (point[i].type == -1)
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



int main()
{
	std::vector<Segment> segments;
	segments.push_back(Segment(-2, 1, 1, 2, 0));
	segments.push_back(Segment(1, 2.5, 1.5, 2.5, 1));
	std::cout << IntersectionEffective(segments);
	return 0;
}
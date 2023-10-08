#include "AVLTree.h"
#include "Segments.h"
#include <vector>

const int n = 2;

double Area(Point a, Point b, Point c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool IntersectProjection(double b1, double e1, double b2, double e2)
{
	if (b1 > e1)  std::swap(b1, e1);
	if (b2 > e2)  std::swap(b2, e2);
	return std::max(b1, b2) <= std::min(e1, e2);
}

bool Intersect(const Segment& a, const Segment& b) {
	return IntersectProjection(a.begin.x, a.end.x, b.begin.x, b.end.x)
		&& IntersectProjection(a.begin.y, a.end.y, b.begin.y, b.end.y)
		&& Area(a.begin, a.end, b.begin) * Area(a.begin, a.end, b.end) <= 0
		&& Area(b.begin, b.end, a.begin) * Area(b.begin, b.end, a.end) <= 0;
}

bool IntersectionEffective(Segment S[])
{
	AVLTree<Segment> L;
	Point p;
	AVLTree<Point> begins_ends;
	for (int i = 0; i < n; ++i)
	{
		begins_ends.Insert(S[i].begin);
		begins_ends.Insert(S[i].end);
	}
	Point point[2 * n];
	int j = 0;
	begins_ends.Content(point, j); // лексикографическая сортировка 2n концов отрезков
	Node<Segment>* s;
	Node<Segment>* s1;
	Node<Segment>* s2;
	for (int i = 0; i < 2 * n; ++i)
	{
		p = point[i];
		s = new Node<Segment>(*p.segment);
		if (p.left == true)
		{
			L.InsertNode(s);
			s1 = L.OverNode(s);
			s2 = L.UnderNode(s);
			if ((Intersect(s1->key, s->key)) || (Intersect(s2->key, s->key)))
			{
				return true;
			}
		}
		else
		{
			L.InsertNode(s);
			s1 = L.OverNode(s);
			s2 = L.UnderNode(s);
			if (Intersect(s1->key, s2->key))
			{
				return true;
			}

		}
	}
	return true;
}



int main()
{
	Point p1(4, 5), p2(2, 4), p3(2, 7), p4(3, 5);
	Segment segments[2];
	segments[0].begin = p1;
	segments[0].end = p2;
	segments[1].begin = p3;
	segments[1].end = p4;
	IntersectionEffective(segments);
	return 0;
}
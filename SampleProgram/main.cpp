#include <vector>
#include "Intersection.h"
#include <fstream>
#include <chrono>

int main()
{
	std::fstream in("input.txt");
	double x1, y1, x2, y2;
	int i = 0;
	std::vector<Segment> segments;
	while (!in.eof())
	{
		in >> x1;
		in >> y1;
		in >> x2;
		in >> y2;
		Point a(x1, y1);
		Point b(x2, y2);
		segments.push_back(Segment(a, b, i));
		++i;
	}
	std::cout << AVL::IntersectionEffective(segments) << std::endl;
	std::cout << TwoThird::IntersectionEffective(segments) << std::endl;
	return 0;
}
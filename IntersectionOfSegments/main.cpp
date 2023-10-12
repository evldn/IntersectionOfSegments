#include <vector>
#include "Intersection.h"

int main()
{
	std::vector<Segment> segments;
	segments.push_back(Segment(1.5, 1.8, 4, 7, 0));
	segments.push_back(Segment(3, 1, 4, 6, 1));
	segments.push_back(Segment(3, 0, 7, 4, 2));
	segments.push_back(Segment(3, -1, 9, 1, 3));
	std::cout << IntersectionEffective(segments);
	return 0;
}
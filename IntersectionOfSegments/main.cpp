#include <vector>
#include "Intersection.h"
#include "2,3-Tree.h"
#include "SegmentGenerator.h"
#include <fstream>
#include <chrono>
#include "time.h"

int main()
{
	/*std::fstream in("input.txt");
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
	}*/
	SegmentGenerator gen;
	std::vector<Segment> segments;
	std::ofstream out;
	out.open("results.txt");
	for (int n = 1; n < 10'000 + 1; n+=100)
	{
		//long long time[] = { LLONG_MAX, LLONG_MAX, LLONG_MAX };
		long long time;
		for (int i = 0; i < n; ++i)
		{
			segments.push_back(gen.GenerateSegment(i));
		}
		//for (int number_test = 0; number_test < 3; ++number_test)
		{
			auto start_time = std::chrono::steady_clock::now();
			//clock_t start_time = clock();
			AVL::IntersectionEffective(segments);
			//clock_t end_time = clock();
			//time[number_test] = std::min((double)(end_time - start_time) / CLOCKS_PER_SEC, time[number_test]);
			auto end_time = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
			time = duration.count();
			//time[number_test] = std::min(duration.count(), time[number_test]);
		}
		if (out.is_open())
		{
			//double time_average = (time[0] + time[1] + time[2]) / 3;
			//long long time_min = std::min(time[0], std::min(time[1], time[2]));
			out << n << " " << time << std::endl;
		}
		segments.clear();
	}
	//std::cout << TwoThird::IntersectionEffective(segments) << std::endl;
	return 0;
}
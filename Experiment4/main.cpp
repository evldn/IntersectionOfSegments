#include <vector>
#include "Intersection.h"
#include "SegmentGenerator.h"
#include <fstream>
#include <chrono>

int main()
{
	SegmentGenerator gen;
	std::vector<Segment> segments;
	std::ofstream out;
	out.open("results.txt");
	int n = 10'000;
	for (double r = 0.0001; r <= 0.01; r += 0.0001)
	{
		long long time_1, time_2;
		for (int i = 0; i < n; ++i)
		{
			segments.push_back(gen.GenerateSegmentWithLength(i,r));
		}
		auto start_time_1 = std::chrono::steady_clock::now();
		AVL::IntersectionEffective(segments);
		auto end_time_1 = std::chrono::steady_clock::now();
		auto duration_1 = std::chrono::duration_cast<std::chrono::microseconds>(end_time_1 - start_time_1);
		time_1 = duration_1.count();
		auto start_time_2 = std::chrono::steady_clock::now();
		TwoThird::IntersectionEffective(segments);
		auto end_time_2 = std::chrono::steady_clock::now();
		auto duration_2 = std::chrono::duration_cast<std::chrono::microseconds>(end_time_2 - start_time_2);
		time_2 = duration_2.count();
		if (out.is_open())
		{
			out << r << " " << time_1 << " " << time_2 << std::endl;
		}
		segments.clear();
	}
	return 0;
}
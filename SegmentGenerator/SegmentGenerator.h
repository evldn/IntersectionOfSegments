#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include "Segments.h"
#include "Intersection.h"

const double PI = 3.141592653589793;

class SegmentGenerator
{
public:
    SegmentGenerator() : randomEngine(std::random_device()()) {}
    Segment GenerateSegment(int id);
    Segment GenerateSegmentWithLength(int id, double r);
    std::vector<Segment> GenerateSegmentsWithProperties(int n, int k, std::vector<Segment>& segments);
    //std::vector<Segment> GenerateSegmentsWithProperties(int n, int k, std::vector<Segment>& segments);

private:
    std::mt19937 randomEngine;
};
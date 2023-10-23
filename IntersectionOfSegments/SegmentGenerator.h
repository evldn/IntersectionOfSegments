#pragma once
#include <iostream>
#include <random>
#include "Segments.h"

class SegmentGenerator
{
public:
    SegmentGenerator() : randomEngine(std::random_device()()) {}

    Segment GenerateSegment(int id)
    {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        double x_1 = distribution(randomEngine);
        double y_1 = distribution(randomEngine);
        double x_2 = distribution(randomEngine);
        double y_2 = distribution(randomEngine);
        Point a(distribution(randomEngine), distribution(randomEngine));
        Point b(distribution(randomEngine), distribution(randomEngine));
        Segment segment(a, b, id);
        return segment;
    }
private:
    std::mt19937 randomEngine;
};
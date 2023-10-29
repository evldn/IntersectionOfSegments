#pragma once
#include <iostream>
#include <random>
#include <vector>
#include "Segments.h"
#include "Intersection.h"

const double PI = 3.141592653589793;

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
    Segment GenerateSegmentWithLength(int id, double r)
    {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        double center_x = distribution(randomEngine);
        double center_y = distribution(randomEngine);
        double angle = distribution(randomEngine); // Angle in radians
        double half_length = r / 2.0;
        double delta_x = half_length * cos(angle);
        double delta_y = half_length * sin(angle);

        Point a(center_x - delta_x, center_y - delta_y);
        Point b(center_x + delta_x, center_y + delta_y);
        Segment segment(a, b, id);
        return segment;
    }
    std::vector<Segment> GenerateSegmentsWithProperties(int n, int k, std::vector<Segment>& segments)
    {
        int flag = 1;
        // √енераци€ первых k отрезков (непересекающиес€)
        for (int i = 0; i < k; ++i)
        {
            while (true)
            {
                Segment segment = GenerateSegment(i);
                for (int j = 0; j < segments.size(); ++j)
                {
                    if (Intersect(segment, segments[j]))
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1)
                {
                    segments.push_back(segment);
                    break;
                }
                flag = 1;
            }
        }
        flag = 1;
        while (true)
        {
            Segment segment1 = GenerateSegment(k);
            Segment segment2 = GenerateSegment(k + 1);
            for (int j = 0; j < segments.size(); ++j)
            {
                if (!(Intersect(segment1, segment2)) && (Intersect(segment1, segments[j])) && (Intersect(segment2, segments[j])))
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
            {
                segments.push_back(segment1);
                segments.push_back(segment2);
                break;
            }
            flag = 1;
        }
        flag = 1;
        for (int i = k + 2; i < n; ++i)
        {
            while (true)
            {
                Segment segment = GenerateSegment(i);
                for (int j = 0; j < k; ++j)
                {
                    if (Intersect(segment, segments[j]))
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1)
                {
                    segments.push_back(segment);
                    break;
                }
                flag = 1;
            }
        }
        return segments;
    }
private:
    std::mt19937 randomEngine;
};
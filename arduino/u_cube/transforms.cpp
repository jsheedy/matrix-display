#include "utils.h"

Point_t LUT_distort(Point_t p, float s, float c)
{
    float t = WIDTH / 2.0;
    Point_t pp;

    float xt = (float)p.x - t;
    float yt = (float)p.y - t;

    pp.x = (xt * c - yt * s) + t + 0.5;
    pp.y = (xt * s + yt * c) + t + 0.5;

    return pp;
}

Point_t LUT_distort2(Point_t p, long t)
{
    Point_t pp;

    float xt = ((p.x - WIDTH/2) * p.y) / 32;
    // float yt = (float)p.y - t;

    pp.x = xt;
    pp.y = (p.y + t /100) % HEIGHT;

    return pp;
}
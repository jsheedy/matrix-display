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

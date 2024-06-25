#pragma once
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

struct Marker {
    double pos;
    double ID;
};

struct Markers{
    int nMarkers;
    std::vector<Marker> markers;
};

namespace PTR{
    struct Point {
        double missingCounter;
        bool missing = false;
        bool estimated = false;
        double lastSeen;
        double prevPos;
        double pos;
        double dpos;
        double ID;
        double prevID;
    };

    Point makePoint(Marker mrkr);

}



// Markers markers; 
// std::vector<Point> Points;
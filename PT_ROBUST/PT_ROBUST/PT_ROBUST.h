#pragma once
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>


int MAX_drop = 2;

int counter = 0;
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


struct Marker {
    double pos;
    double ID;
};

struct Markers{
    int nMarkers;
    std::vector<Marker> markers;
};

// Markers markers; 
// std::vector<Point> Points;
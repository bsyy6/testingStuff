#pragma once
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "FFIFO/FFIFO.h"

struct Marker {
    double pos;
    double ID;
};

struct Markers{
    int nMarkers = 0;
    std::vector<Marker> markers;
};

namespace PTR{
    struct Point {
        double missingCounter;
        bool missing = false;
        bool estimated = false;
        double lastSeen;
        FFIFO<double,10> prevPos;
        double pos;
        double dpos;
        double ID;
        FFIFO<double,5> prevIDs;
        double goalPosition;
    };
    
    struct Points{
        int nPoints = 0;
        std::vector<PTR::Point> points;
    };

    Point makePoint(Marker mrkr); // track a marker as a point
    void updatePointPos(Point &pt, const Marker& mrkr); // update the point position
    void updatePoints(Points &points, const Markers& markers); // update all tracked points positions
    void makePointPosfollowMarker(Point &pt);

    void estimatePoint(Point &pt); // estimate a point postition.
    bool findClosePoint(Point &pt, const Points &points,const Markers& markers); // find if new marker ID is close to the previous point position, assign it to that.

}



// Markers markers; 
// std::vector<Point> Points;
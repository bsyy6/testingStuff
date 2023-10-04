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

Markers markers; 
std::vector<Point> Points;



double subPoints (double p1, double p2){
    // returns p1 - p2    
    return p1-p2;
}
double addPoints (double p1, double p2){
    // returns p1 + p2
    
    return p1+p2;
}


void makePoint(double pos,double id) {
    Point p;
    p.pos = pos;
    p.missingCounter = 0;
    
    p.estimated = false;

    p.ID = id;
    p.prevID = 0;
    
    Points.push_back(p);
}

void updatePointPos(Point &pt, Marker mrkr) {
    // chceks if the ID is the same
    if (pt.ID == mrkr.ID) {
        pt.prevPos = pt.pos;
        pt.pos = mrkr.pos;
        pt.dpos = subPoints(pt.pos, pt.prevPos);
        pt.missing = false;
    }
    // resets missing flag in case it was set
    
}



void updatePoint(Point &pt, Marker mrkr) {
    pt.prevID = pt.ID;
    pt.ID = mrkr.ID; // now we updated the ID, we can update the position
    updatePointPos(pt, mrkr);
    pt.estimated = false;
}


void checkPt(Point &pt, std::vector<int> listIDs){
    // check if the PointID exists in the listIDs
    if (std::find(listIDs.begin(), listIDs.end(), pt.ID) != listIDs.end()) {
        pt.missingCounter = 0;
        pt.missing = false;
    } else {
        pt.missing = true;
        pt.missingCounter++;
    }
}

double distPoints(double p1, double p2){
    //retunrs the distance between two points in 3D
    return (abs(p1 - p2));
}

void estimate(Point &pt) {
    if(!pt.estimated){
        // first time claculate the speed
        pt.dpos = subPoints(pt.pos, pt.prevPos);
        pt.estimated = true; 
        pt.lastSeen = pt.pos;
    }
    if (pt.missingCounter <= MAX_drop) {
        // if both are missing keep the speed
        pt.prevPos = pt.pos;
        pt.pos = addPoints(pt.pos,pt.dpos);
    }
}


int numberOfMarkersToTrack = 2;
double temp; 
int main()
{
        
       for(int i =0; i <5; i++){
            Marker mrkr;
            mrkr.ID = i+1;
            mrkr.pos = i+10; // make sure thy are really far away from each other
            markers.markers.push_back(mrkr);
            markers.nMarkers++;
        }

        

        // make 2 fake Points
        for (int i = 0; i < 2; i++) {
            makePoint(markers.markers[i].pos, markers.markers[i].ID);
        }
            
        for (int rounds = 0; rounds <10; rounds++){
            markers.markers[0].pos++;
            if (rounds  == 5){
            //delete markers.markers[0];
            markers.markers[4].ID = 99;
            temp = markers.markers[0].pos+0.005-1;
            markers.markers.erase(markers.markers.begin());
            }
            if (rounds  == 9){
                // add it back on step 9
                markers.markers[3].ID = 1;
                markers.markers[3].pos = temp;
            }

            markers.nMarkers = markers.markers.size();
            std::vector<int> markerIDs;
            std::vector<int> pointIDs;
            for (int i = 0; i < Points.size(); i++) {
                pointIDs.push_back(Points[i].ID);
            }
            for (int i = 0; i < markers.nMarkers; i++) {
                markerIDs.push_back(markers.markers[i].ID);
            }
            // check if the point exists in the list of markers
            for (int i = 0; i < Points.size(); i++) {
                for (int j = 0; j < markers.nMarkers; j++) {
                    updatePointPos(Points[i], markers.markers[j]);  
                }
                checkPt(Points[i], markerIDs);
                // not found in the list of markers!
                if(Points[i].missing){
                    estimate(Points[i]);
                    if(markers.nMarkers >= numberOfMarkersToTrack){
                        // find the closest marker to be this point
                        double minDist = 0.01; // within 1 cm
                        int minIndex = 0;
                        // make sure it doesn't inlcude markers already in the list
                        for (int j = 0; j < markers.nMarkers; j++) {

                            if(markers.markers[j].ID == Points[i].ID){
                                updatePointPos(Points[i], markers.markers[j]);
                                Points[i].prevID = 0; // set it to zero so it can be updated
                                continue;
                            }
                            
                            if(std::find(pointIDs.begin(), pointIDs.end(), markers.markers[j].ID) != pointIDs.end()){
                                continue;
                            }

                            double dist = distPoints(markers.markers[j].pos, Points[i].lastSeen); 
                            if (dist < minDist) {
                                minDist = dist;
                                minIndex = j;
                            }
                        }
                        // update the point with the new ID
                        if(minDist < 0.01){
                            updatePoint(Points[i], markers.markers[minIndex]);
                        }else{
                            std::cout<<"No marker found for point: "<< Points[i].ID << "-" << minDist <<std::endl;
                        }
                    }
                }
                }
            }
    return 0;
        }


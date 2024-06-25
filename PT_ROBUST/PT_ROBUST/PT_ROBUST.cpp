#include "PT_ROBUST.h"


namespace PTR{

    Point makePoint(Marker mrkr){
            Point p;
            p.pos = mrkr.pos;
            p.missingCounter = 0;
            p.estimated = false;
            p.ID = mrkr.ID;
            p.prevIDs.push_back(p.ID);
            return(p);
    }


    void updatePointPos(Point &pt, const Marker& mrkr) {
        if (pt.ID == mrkr.ID) {
            pt.prevPos = pt.pos;
            pt.pos = mrkr.pos;
            pt.dpos = pt.pos - pt.prevPos;
            if (std::abs(pt.dpos) < 0.001) pt.dpos = 0;
            pt.missingCounter = 0;
            pt.missing = false;
            pt.estimated = false;
        }
    }

    void updatePoints(Points& points, const Markers& markers){    
        for (auto& point: points.points){
            bool found = false;
            for (const auto& marker: markers.markers){
                if (marker.ID == point.ID){
                    updatePointPos(point,marker);
                    found = true;
                    break; // go to next point
                }
            }
            if(!found){
                point.missing = true;
                if(!findClosePoint(point,points,markers)){
                    estimatePoint(point);
                    point.missingCounter++;
                }
            }
        }
    }

    void estimatePoint(Point& pt){
        if(pt.missingCounter < 10){
            pt.estimated = true;
            pt.prevPos = pt.pos;
            pt.pos += pt.dpos;
        }
        else{
            // point not found anymore and I lost hope :(

        }
    }

    bool findClosePoint(Point &pt, const Points &points,const Markers& markers){
        // find if new marker ID is close to the previous point position, assign it to that.
        // returns false when it fails.
        int closestMarkerId = NULL;
        bool foundCloseMarker = false;
        float closestMarkerDist =100;
        int maximumDistance = 0.01; // 1 cm seems close enogh to me.
        
        for (const auto& marker : markers.markers){
            bool markerIsAlreadyAssigned = false;
            for(const auto& point: points.points){
                if(point.ID == marker.ID){
                    markerIsAlreadyAssigned = true;
                }
                break;
            }
            if(!markerIsAlreadyAssigned){
                float distToPoint = std::abs(marker.pos - pt.pos);
                if( distToPoint< maximumDistance
                    && distToPoint < closestMarkerDist
                   ){
                        closestMarkerDist = distToPoint;
                        closestMarkerId = marker.ID;
                   }
            }
        }
        if(foundCloseMarker){
            pt.prevIDs.push_back(pt.ID);
            pt.ID = closestMarkerId;
            pt.estimated = true;
            pt.missing = false;
        }
        
        return(foundCloseMarker);

        
    };





}


// void updatePoint(Point &pt, Marker mrkr) {
//     pt.prevID = pt.ID;
//     pt.ID = mrkr.ID; // now we updated the ID, we can update the position
//     updatePointPos(pt, mrkr);
//     pt.estimated = false;
// }




// double distPoints(double p1, double p2){
//     //retunrs the distance between two points in 3D
//     return (abs(p1 - p2));
// }

// void estimate(Point &pt) {
//     if(!pt.estimated){
//         // first time claculate the speed
//         pt.dpos = subPoints(pt.pos, pt.prevPos);
//         pt.estimated = true; 
//         pt.lastSeen = pt.pos;
//     }
//     if (pt.missingCounter <= MAX_drop) {
//         // if both are missing keep the speed
//         pt.prevPos = pt.pos;
//         pt.pos = addPoints(pt.pos,pt.dpos);
//     }
// }


// int numberOfMarkersToTrack = 2;
// double temp; 
// int main()
// {
        
//     for(int i =0; i <5; i++){
//         Marker mrkr;
//         mrkr.ID = i+1;
//         mrkr.pos = i+10; // make sure thy are really far away from each other
//         markers.markers.push_back(mrkr);
//         markers.nMarkers++;
//     }

    

//     // make 2 fake Points
//     for (int i = 0; i < 2; i++) {
//         makePoint(markers.markers[i].pos, markers.markers[i].ID);
//     }
            
//     for (int rounds = 0; rounds <10; rounds++){
//             markers.markers[0].pos++;
//             if (rounds  == 5)
//             //delete markers.markers[0];
//             markers.markers.erase(markers.markers.begin());
//         markers.nMarkers = markers.markers.size();
//         std::vector<int> markerIDs;
//         std::vector<int> pointIDs;
//         for (int i = 0; i < Points.size(); i++) {
//             pointIDs.push_back(Points[i].ID);
//         }
//         for (int i = 0; i < markers.nMarkers; i++) {
//             markerIDs.push_back(markers.markers[i].ID);
//         }
//         // check if the point exists in the list of markers
//         for (int i = 0; i < Points.size(); i++) {
//             for (int j = 0; j < markers.nMarkers; j++) {
//                 updatePointPos(Points[i], markers.markers[j]);  
//             }
//             checkPt(Points[i], markerIDs);
//             // not found in the list of markers!
//             if(Points[i].missing){
//                 estimate(Points[i]);
//                 if(markers.nMarkers >= numberOfMarkersToTrack){
//                     // find the closest marker to be this point
//                     double minDist = 0.01; // within 1 cm
//                     int minIndex = 0;
//                     // make sure it doesn't inlcude markers already in the list
//                     for (int j = 0; j < markers.nMarkers; j++) {

//                         if(markers.markers[j].ID == Points[i].ID){
//                             // if the marker is found, update the point.
//                             updatePointPos(Points[i], markers.markers[j]);
//                             continue;
//                         }
                        
//                         if(std::find(pointIDs.begin(), pointIDs.end(), markers.markers[j].ID) != pointIDs.end()){
//                             // if the maker is already in the list, skip it.
//                             continue;
//                         }

//                             double dist = distPoints(markers.markers[j].pos, Points[i].lastSeen); 
//                             if (dist < minDist) {
//                                 minDist = dist;
//                                 minIndex = j;
//                             }
//                         }
//                         // update the point with the new ID
//                         if(minDist < 0.01){
//                             updatePoint(Points[i], markers.markers[minIndex]);
//                         }else{
//                             std::cout<<"No marker found for point: "<< Points[i].ID << "-" << minDist <<std::endl;
//                         }
//                     }
//                 }
//                 }
//             }
//         }

//     return 0;
//         }

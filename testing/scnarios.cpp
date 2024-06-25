/* initial position */

for(int i =0; i <2; i++){
    Marker mrkr;
    mrkr.ID = i+1;
    mrkr.pos = i+1;
    markers.markers.push_back(mrkr);
    markers.nMarkers++;
}

std::vector<int> markerIDs;

for (int i = 0; i < markers.nMarkers; i++) {
    markerIDs.push_back(markers.markers[i].ID);
}

// make 2 fake Points
for (int i = 0; i < markers.nMarkers; i++) {
    makePoint(markers.markers[i].pos, markers.markers[i].ID);
}

/* see more markers than Points */

for(int i =0; i <5; i++){
    Marker mrkr;
    mrkr.ID = i+1;
    mrkr.pos = i+1;
    markers.markers.push_back(mrkr);
    markers.nMarkers++;
}

std::vector<int> markerIDs;

for (int i = 0; i < markers.nMarkers; i++) {
    markerIDs.push_back(markers.markers[i].ID);
}

// make 2 fake Points
for (int i = 0; i < 2; i++) {
    makePoint(markers.markers[i].pos, markers.markers[i].ID);
}
            
/* a marker is moving */
        for(int i =0; i <5; i++){
            Marker mrkr;
            mrkr.ID = i+1;
            mrkr.pos = i+1;
            markers.markers.push_back(mrkr);
            markers.nMarkers++;
        }

        std::vector<int> markerIDs;

        for (int i = 0; i < markers.nMarkers; i++) {
            markerIDs.push_back(markers.markers[i].ID);
        }

        // make 2 fake Points
        for (int i = 0; i < 2; i++) {
            makePoint(markers.markers[i].pos, markers.markers[i].ID);
        }
            
        for (int rounds = 0; rounds <10; rounds++){
            markers.markers[0].pos++;

/* lose a marker[0] at step 5 */
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
            if (rounds  == 5)
            //delete markers.markers[0];
            markers.markers.erase(markers.markers.begin());

/* lose a a marker on round 5, it shows back on round 5 with ID 99 */
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
            temp = markers.markers[0].pos+0.005-1;
            markers.markers.erase(markers.markers.begin());
            }
            if( rounds == 9){
                // add it back on step 9
                markers.markers[3].ID = 99;
                markers.markers[3].pos = temp;
            }


/* lose a marker and findit with the same ID on step 9*/
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
            if( rounds == 9){
                // add it back on step 9
                markers.markers[3].ID = 1;
                markers.markers[3].pos = temp;
            }



















            
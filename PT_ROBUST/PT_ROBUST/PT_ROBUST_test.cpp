#include <gtest/gtest.h>
#include <string>
#include <PT_ROBUST/PT_ROBUST.h>

// Test fixture for the unit test
class PointTest : public ::testing::Test {
    

    public:

    Markers markers;
    PTR::Points points;

    PointTest(){}  
    ~PointTest(){}

    void SetUp() override{
        markers.nMarkers = 0; 
        // Set up the markers and points for the test
        for (int i = 0; i < 5; i++) {
            Marker mrkr;
            mrkr.ID = i + 1;
            mrkr.pos = i*5 + 1; // make sure they are really far away from each other
            markers.markers.push_back(mrkr);
            markers.nMarkers++;
        }

        // Make 2 fake Points
        for (int i = 0; i < 2; i++) {
            PTR::Point P = PTR::makePoint(markers.markers[i]);
            points.points.push_back(P);
            points.nPoints++;
        }
    }

    void TearDown() override{
        // Clean up the points after the test
        points.nPoints = 0;
        points.points.clear();
    }
};

TEST_F(PointTest, MarkersAreCreatedCorrectly) {
    ASSERT_EQ(markers.nMarkers, 5);
    ASSERT_EQ(points.nPoints, 2);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(markers.markers[i].ID, i + 1);
        EXPECT_EQ(markers.markers[i].pos, i*5 + 1);
    }
}


TEST_F(PointTest, MakersHaveCorrectIDandPos){
     for (int i = 0; i < 5; i++) {
        PTR::Point p = PTR::makePoint(markers.markers[i]);
        EXPECT_EQ(p.ID, markers.markers[i].ID);
    }
}

TEST_F(PointTest, UpdatePointPosition_single){
    EXPECT_EQ(points.points[0].pos, markers.markers[0].pos);
    EXPECT_EQ(points.points[0].ID, markers.markers[0].ID);
    markers.markers[0].pos += 2;
    PTR::updatePointPos(points.points[0],markers.markers[0]); 
    EXPECT_EQ(points.points[0].pos, markers.markers[0].pos);
    EXPECT_EQ(points.points[0].ID, markers.markers[0].ID);
}

TEST_F(PointTest, UpdatePoints_allOk){
    EXPECT_EQ(points.points[0].pos, markers.markers[0].pos);
    EXPECT_EQ(points.points[0].ID, markers.markers[0].ID);
    markers.markers[0].pos += 2;
    markers.markers[2].pos -= 3;
    PTR::updatePoints(points,markers); 
    EXPECT_EQ(points.points[0].pos, markers.markers[0].pos);
    EXPECT_EQ(points.points[0].ID, markers.markers[0].ID);
}

TEST_F(PointTest, UpdatePoints_missingMarker){
    EXPECT_EQ(points.points[0].pos, markers.markers[0].pos);
    EXPECT_EQ(points.points[0].ID, markers.markers[0].ID);
    markers.markers[0].pos += 2;
    markers.markers[1].pos -= 3;
    PTR::updatePoints(points,markers);
    std::cout << "Positions:" << points.points[0].pos;
    markers.markers.erase(markers.markers.begin());
    markers.nMarkers--;
    PTR::updatePoints(points,markers);
    // detect it was missing
    EXPECT_TRUE(points.points[0].missing);
    EXPECT_FALSE(points.points[1].missing);
    // estimation worked.
    EXPECT_TRUE(points.points[0].estimated);
    EXPECT_FALSE(points.points[1].estimated);
    // linear estimation
    // first
    EXPECT_NEAR(points.points[0].pos - points.points[0].prevPos.back(), points.points[0].dpos, 0.001);
    EXPECT_DOUBLE_EQ(points.points[1].pos - points.points[1].prevPos.back(),0);
    std::cout <<"->" << points.points[0].pos;
    // second
    PTR::updatePoints(points,markers);
    EXPECT_NEAR(points.points[0].pos - points.points[0].prevPos.back(), points.points[0].dpos, 0.001);
    EXPECT_DOUBLE_EQ(points.points[1].pos - points.points[1].prevPos.back(),0);
    std::cout <<"->"<< points.points[0].pos <<std::endl;   
}

TEST_F(PointTest, UpdatePoints_missingMarkerComesBack){
    EXPECT_EQ(points.points[0].pos, markers.markers[0].pos);
    EXPECT_EQ(points.points[0].ID, markers.markers[0].ID);
    markers.markers[0].pos += .04; //12
    markers.markers[1].pos -= 3;
    PTR::updatePoints(points,markers);
    std::cout << "Positions:" << points.points[0].pos;
    Marker missingMarker = markers.markers[0];
    markers.markers.erase(markers.markers.begin());
    markers.nMarkers--;
    PTR::updatePoints(points,markers);
    // detect it was missing
    EXPECT_TRUE(points.points[0].missing);
    EXPECT_FALSE(points.points[1].missing);
    // estimation worked.
    EXPECT_TRUE(points.points[0].estimated);
    EXPECT_FALSE(points.points[1].estimated);
    // linear estimation
    // first
    EXPECT_NEAR(points.points[0].pos - points.points[0].prevPos.back(), points.points[0].dpos, 0.001);
    EXPECT_DOUBLE_EQ(points.points[1].pos - points.points[1].prevPos.back(),0);
    std::cout <<"->" << points.points[0].pos; //14 estimated
    // bring back missing marker
    missingMarker.pos +=.04;
    markers.markers.push_back(missingMarker);
    markers.nMarkers++;
    PTR::updatePoints(points,markers);
    EXPECT_FALSE(points.points[0].estimated);
    EXPECT_FALSE(points.points[0].missing);
    EXPECT_EQ(points.points[0].pos, missingMarker.pos);
    EXPECT_DOUBLE_EQ(points.points[1].pos - points.points[1].prevPos.back(),0);
    std::cout <<"->"<< points.points[0].pos <<std::endl;   
}

TEST_F(PointTest, UpdatePoints_closeMarkerIsFound){
    EXPECT_EQ(points.points[0].pos, markers.markers[0].pos);
    EXPECT_EQ(points.points[0].ID, markers.markers[0].ID);
    markers.markers[0].pos += 0.5;
    markers.markers[1].pos -= 3;
    PTR::updatePoints(points,markers);
    std::cout << "Positions:" << points.points[0].pos;
    Marker missingMarker = markers.markers[0];
    markers.markers.erase(markers.markers.begin());
    markers.nMarkers--;
    PTR::updatePoints(points,markers);
    // detect it was missing
    EXPECT_TRUE(points.points[0].missing);
    EXPECT_FALSE(points.points[1].missing);
    // estimation worked.
    EXPECT_TRUE(points.points[0].estimated);
    EXPECT_FALSE(points.points[1].estimated);
    // linear estimation
    // first
    EXPECT_NEAR(points.points[0].pos - points.points[0].prevPos.back(), points.points[0].dpos, 0.001);
    EXPECT_DOUBLE_EQ(points.points[1].pos - points.points[1].prevPos.back(),0);
    std::cout <<"->" << points.points[0].pos; //14 estimated
    // bring back missing marker
    missingMarker.pos +=0.005; //13 real
    missingMarker.ID = 99;
    markers.markers.push_back(missingMarker);
    markers.nMarkers++;
    PTR::updatePoints(points,markers);
    EXPECT_TRUE(points.points[0].estimated);
    EXPECT_FALSE(points.points[0].missing);
    //EXPECT_EQ(points.points[0].pos, missingMarker.pos);
    //EXPECT_EQ(points.points[0].ID, missingMarker.ID);
    //EXPECT_DOUBLE_EQ(points.points[1].pos - points.points[1].prevPos.back(),0);
    std::cout <<"->"<< points.points[0].pos <<std::endl;   
}
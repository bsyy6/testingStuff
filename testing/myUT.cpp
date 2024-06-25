#include <gtest/gtest.h>
#include "unitTestPoint.cpp"

// Test fixture for the unit test
class PointTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up the markers and points for the test
        for (int i = 0; i < 5; i++) {
            Marker mrkr;
            mrkr.ID = i + 1;
            mrkr.pos = i + 10; // make sure they are really far away from each other
            markers.markers.push_back(mrkr);
            markers.nMarkers++;
        }

        // Make 2 fake Points
        for (int i = 0; i < 2; i++) {
            makePoint(markers.markers[i].pos, markers.markers[i].ID);
        }
    }

    void TearDown() override {
        // Clean up the points after the test
        Points.clear();
    }
};

// Test the logic in the main function
TEST_F(PointTest, TestMainLogic) {
    for (int rounds = 0; rounds < 10; rounds++) {
        // Modify the markers based on the round number
        if (rounds == 5) {
            markers.markers[4].ID = 99;
            markers.markers.erase(markers.markers.begin());
        } else if (rounds == 9) {
            markers.markers[3].ID = 1;
            markers.markers[3].pos = temp;
        } else {
            markers.markers[0].pos++;
        }

        // Update the points
        updatePoints();

        // Check that the expected number of markers and points are present
        EXPECT_EQ(markers.nMarkers, markers.markers.size());
        EXPECT_EQ(numberOfMarkersToTrack, Points.size());

        // Check that the marker IDs and point IDs match
        std::vector<int> markerIDs;
        std::vector<int> pointIDs;
        for (int i = 0; i < Points.size(); i++) {
            pointIDs.push_back(Points[i].ID);
        }
        for (int i = 0; i < markers.nMarkers; i++) {
            markerIDs.push_back(markers.markers[i].ID);
        }
        EXPECT_EQ(markerIDs, pointIDs);
    }
}
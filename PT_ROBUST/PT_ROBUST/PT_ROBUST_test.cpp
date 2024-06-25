#include <gtest/gtest.h>
#include <string>
#include <PT_ROBUST/PT_ROBUST.h>

// Test fixture for the unit test
class PointTest : public ::testing::Test {
    

    public:

    Markers markers; 

    PointTest(){}  
    ~PointTest(){}

    void SetUp() override{
        
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
            PTR::Point P = PTR::makePoint(markers.markers[i]);
        }
    }

    void TearDown() override{
        // Clean up the points after the test
        // Points.clear();
    }
};

TEST_F(PointTest, MarkersAreCreatedCorrectly) {
    ASSERT_EQ(markers.nMarkers, 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(markers.markers[i].ID, i + 1);
        EXPECT_EQ(markers.markers[i].pos, i + 10);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
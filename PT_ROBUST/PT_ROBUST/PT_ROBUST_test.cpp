#include <gtest/gtest.h>
#include <string>
#include <PT_ROBUST/PT_ROBUST.h>

// Test fixture for the unit test
class PointTest : public gtest::testing::Test {
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


TEST(generalTest, canCallPT)
{
    GTEST_ASSERT_EQ("1",fizzbuzz::fizzbuzz(1));
}
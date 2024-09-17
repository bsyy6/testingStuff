#pragma once
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "FFIFO/FFIFO.h"
#include <cmath>

class MA {
private:
    std::vector<double> window;  // Queue to store the data points
    int windowSize;             // Fixed size of the sliding window
    double sum;                 // Sum of the elements in the current window
    std::vector<double> recentAverages; // Maintain the last 5 moving averages
    bool hasEnoughData;         // Flag to check if there are enough data points
    double intercept;           // Intercept of the linear regression line
    double slope;               // Slope of the linear regression line
    double estimationNumber;    // Number of estimations made

public:
    MA(int size);

    double predict();
    double velocity;            // Velocity of the object


    void correct(double newDataPoint);
    void updateVelocity();
};


// // Function to calculate the slope and intercept of a linear regression line
void linearRegression(std::vector<double>& y, double &slope, double &intercept);
double mean(std::vector<double>& v);
#include "MA.h"

MA::MA(int size) :  windowSize(size), sum(0), intercept(0),
                    slope(0), estimationNumber(0), hasEnoughData(false) {
    window.reserve(size); // Reserve space for the window
}

double MA::predict() {
    if (window.empty()) {
        return 0.0;
    }
    double movingAverage = sum / window.size();
    if (!hasEnoughData) {
        return movingAverage;
    }
    else {
        if(estimationNumber > 0) {
            estimationNumber++;
            return slope * (estimationNumber) + intercept;
        }
        else{
        // estimate the next value based on the last 5 ma's and draw a line
            linearRegression(recentAverages, slope, intercept);
            estimationNumber++; 
            return velocity/windowSize * (windowSize + 1) + intercept;
        }
    }
}

void MA::correct(double newDataPoint) {
    if (window.size() == windowSize) {
        sum -= window.front();
        window.erase(window.begin());
    }
    
    window.push_back(newDataPoint);
    sum += newDataPoint;

    recentAverages.push_back(sum / window.size());
    if (recentAverages.size() > 5) { // Maintain the last 5 moving averages
        recentAverages.erase(recentAverages.begin());
    }
    updateVelocity();
    hasEnoughData = recentAverages.size() > 1;
    estimationNumber = 0;
}

void MA::updateVelocity() {
    if (recentAverages.size() < 2) {
        return; // Not enough data to calculate velocity
    }

    // Calculate the average change between consecutive moving averages
    double totalChange = 0;
    for (size_t i = 1; i < recentAverages.size(); ++i) {
        totalChange += (recentAverages[i] - recentAverages[i - 1]);
    }

    velocity = totalChange / (recentAverages.size() - 1); // average
}


void linearRegression(std::vector<double>& y, double &slope, double &intercept) {
    std::vector<double> x(y.size());
    for (int i = 0; i < x.size(); i++) {
        x[i] = i;
    }
    double x_mean = mean(x);
    double y_mean = mean(y);
    double numerator = 0.0;
    double denominator = 0.0;
    for (int i = 0; i < x.size(); i++) {
        numerator += (x[i] - x_mean) * (y[i] - y_mean);
        denominator += pow(x[i] - x_mean, 2);
    }
    slope = numerator / denominator;
    intercept = y_mean - slope * x_mean;
}

double mean(std::vector<double>& v) {
    double sum = 0.0;
    for (int i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    return sum / v.size();
}
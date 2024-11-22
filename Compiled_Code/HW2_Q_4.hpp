#ifndef HW2_Q_4_HPP
#define HW2_Q_4_HPP

#include <vector>
#include <string>
#include "opencv2/opencv.hpp"

struct DataPoint {
    double x;
    double pressureCoefficient;
};

void processCSV(const std::string& filename);
void plotData(const std::vector<DataPoint>& data);

#endif // HW2_Q_4_HPP

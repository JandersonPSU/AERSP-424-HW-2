#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "opencv2/opencv.hpp"

struct DataPoint {
    double x;
    double pressureCoefficient;
};

int main() {
    std::ifstream file("surface_flow.csv"); // Open the CSV file
    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line); // Read the header row

    // Define the column indices (B -> 1, L -> 11)
    const int xColumnIndex = 1;  // Column B (0-based index)
    const int pressureColumnIndex = 11; // Column L (0-based index)

    std::vector<DataPoint> data;

    // Read each subsequent line
    while (std::getline(file, line)) {
        std::istringstream rowStream(line);
        std::string value;
        DataPoint dp;

        int colIndex = 0;
        while (std::getline(rowStream, value, ',')) {
            if (colIndex == xColumnIndex) {
                dp.x = std::stod(value); // Extract x value from column B
            } else if (colIndex == pressureColumnIndex) {
                dp.pressureCoefficient = std::stod(value); // Extract Pressure_Coefficient from column L
            }
            ++colIndex;
        }

        if (colIndex > std::max(xColumnIndex, pressureColumnIndex)) {
            data.push_back(dp); // Store the data point if columns are valid
        }
    }

    file.close(); // Close the file

    if (data.empty()) {
        std::cerr << "No data to plot!" << std::endl;
        return 1;
    }

    // Output the extracted data
    std::cout << "Extracted Data:" << std::endl;
    std::cout << "x, Pressure_Coefficient" << std::endl;
    for (const auto& dp : data) {
        std::cout << dp.x << ", " << dp.pressureCoefficient << std::endl;
    }

    // Find min and max values for normalization
    double xMin = data.front().x, xMax = data.front().x;
    double yMin = data.front().pressureCoefficient, yMax = data.front().pressureCoefficient;

    for (const auto& dp : data) {
        xMin = std::min(xMin, dp.x);
        xMax = std::max(xMax, dp.x);
        yMin = std::min(yMin, dp.pressureCoefficient);
        yMax = std::max(yMax, dp.pressureCoefficient);
    }

    // Create a canvas for plotting
    const int width = 800, height = 600, margin = 50;
    cv::Mat graph = cv::Mat::zeros(height, width, CV_8UC3);

    // Draw axes
    cv::line(graph, {margin, height - margin}, {width - margin, height - margin}, {255, 255, 255}, 2); // X-axis
    cv::line(graph, {margin, margin}, {margin, height - margin}, {255, 255, 255}, 2); // Y-axis

    // Normalize the data
    auto normalize = [](double value, double min, double max, double newMin, double newMax) {
        return (value - min) / (max - min) * (newMax - newMin) + newMin;
    };

    // Add only 0 and 1 axis markers
    // X-axis
    cv::putText(graph, "0", {margin - 10, height - margin + 20},
                cv::FONT_HERSHEY_SIMPLEX, 0.5, {255, 255, 255}, 1);
    cv::putText(graph, "1", {width - margin - 10, height - margin + 20},
                cv::FONT_HERSHEY_SIMPLEX, 0.5, {255, 255, 255}, 1);

    // Y-axis (flipped)
    cv::putText(graph, "0", {margin - 30, height - margin + 5},
                cv::FONT_HERSHEY_SIMPLEX, 0.5, {255, 255, 255}, 1);
    cv::putText(graph, "1", {margin - 30, margin + 5},
                cv::FONT_HERSHEY_SIMPLEX, 0.5, {255, 255, 255}, 1);

    // Plot the data points
    for (const auto& dp : data) {
        int plotX = static_cast<int>(normalize(dp.x, xMin, xMax, margin, width - margin));
        int plotY = static_cast<int>(normalize(dp.pressureCoefficient, yMin, yMax, margin, height - margin)); // Flip y-axis

        cv::circle(graph, {plotX, plotY}, 2, {0, 0, 255}, -1); // Draw points
    }

    // Add labels
    cv::putText(graph, "X", {width - margin + 10, height - margin + 5}, cv::FONT_HERSHEY_SIMPLEX, 0.5, {255, 255, 255}, 1);
    cv::putText(graph, "Pressure Coefficient", {margin - 40, margin - 10}, cv::FONT_HERSHEY_SIMPLEX, 0.5, {255, 255, 255}, 1);

    // Display the graph
    cv::imshow("Pressure Coefficient Plot", graph);
    cv::waitKey(0); // Wait for a key press

    return 0;
}

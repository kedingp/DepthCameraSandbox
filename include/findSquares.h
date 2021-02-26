#pragma once

#include <vector>

#include <opencv2/opencv.hpp>


// The "Square Detector" program.
// It loads several images sequentially and tries to find squares in
// each image
void findSquares(const cv::Mat& image, std::vector<std::vector<cv::Point> >& squares);
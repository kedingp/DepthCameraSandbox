#pragma once
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

namespace helper
{
// Convert rs2::frame to cv::Mat
cv::Mat frame_to_mat(const rs2::frame &f);

} // namespace helper

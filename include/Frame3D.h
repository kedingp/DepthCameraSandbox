#pragma once
#include <string>

#pragma warning(push, 0)
#include <opencv2/opencv.hpp>
#pragma warning(pop)

namespace camera
{
struct Frame3D {
    void write(const std::string& path) const
    {
        const std::string filename_color = path + "\\image" + std::to_string(id) + ".png";
        const std::string filename_depth = path + "\\depthImage" + std::to_string(id) + ".png";
        cv::imwrite(filename_color, color_image);
        cv::imwrite(filename_depth, depth_image);
    }

    int id;
    cv::Mat color_image;
    cv::Mat depth_image;
};
} // namespace camera

#pragma once
#include <string>

#pragma warning(push, 0)
#include <opencv2/opencv.hpp>
#pragma warning(pop)

namespace camera
{
class Frame3D
{
public:
    Frame3D(int id, cv::Mat colorImage, cv::Mat depthImage)
        : id(id), color_image(colorImage), depth_image(depthImage){};

    void write(const std::string& path) const
    {
        const std::string filename_color = path + "\\image" + std::to_string(id) + ".png";
        const std::string filename_depth = path + "\\depthImage" + std::to_string(id) + ".png";
        cv::imwrite(filename_color, color_image);
        cv::imwrite(filename_depth, depth_image);
    }

    const cv::Mat getDepthImage() const { return depth_image; };
    const cv::Mat getColorImage() const { return color_image; };
    const int getId() const { return id; };

private:
    int id;
    cv::Mat color_image;
    cv::Mat depth_image;
};
} // namespace camera

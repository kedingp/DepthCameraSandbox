#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include <chrono>
#include <filesystem>
#include <iostream>

#pragma warning(push, 0)
#include <opencv2/opencv.hpp>
#pragma warning(pop)

#include "CameraInterface.h"
#include "DepthCamera.h"
#include "helper.h"

int main()
{
    camera::DepthCamera depthCamera;
    depthCamera.start();

    const auto window_name = "Display Depth Image";
    const auto color_window_name = "Display Color Image";
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(color_window_name, cv::WINDOW_AUTOSIZE);

    const std::string path = "testImages";
    std::string finalPath = path + '0';
    for (int i = 1; std::filesystem::is_directory(finalPath); ++i) {
        finalPath = path + std::to_string(i);
    }
    std::filesystem::create_directory(finalPath);

    for (auto frame = std::make_unique<const camera::Frame3D>(); cv::waitKey(0) != 32;) {
        frame = depthCamera.grabFrame();

        frame->write(finalPath);

        cv::imshow(window_name, frame->depth_image);
        cv::imshow(color_window_name, frame->color_image);
        std::cout << "Frame id is: " << frame->id << '\n';
    }

    return EXIT_SUCCESS;
}

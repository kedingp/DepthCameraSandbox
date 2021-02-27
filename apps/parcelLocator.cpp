#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include <chrono>
#include <iostream>

#pragma warning(push, 0)
#include <opencv2/opencv.hpp>
#pragma warning(pop)

#include "CameraInterface.h"
#include "DepthCamera.h"
#include "ParcelLocatorAlgo.h"
#include "helper.h"

int main()
{
    camera::DepthCamera depthCamera;
    depthCamera.start();

    const auto window_name = "Display Depth Image";
    const auto color_window_name = "Display Color Image";
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(color_window_name, cv::WINDOW_AUTOSIZE);

    for (auto [frame, parcelLocator] =
             std::make_tuple<std::unique_ptr<const camera::Frame3D>, parcel_locator::ParcelLocatorAlgo>(
                 nullptr, parcel_locator::ParcelLocatorAlgo());
         cv::waitKey(0) != 32;) {
        frame = depthCamera.grabFrame();

        const auto parcel = parcelLocator.findParcel(*frame);
        cv::polylines(frame->getColorImage(), parcel.topCorners, true, cv::Scalar(0, 255, 0), 3, cv::LINE_AA);

        cv::imshow(window_name, frame->getDepthImage());
        cv::imshow(color_window_name, frame->getColorImage());
        std::cout << "Frame id is: " << frame->getId() << '\n';
    }

    return EXIT_SUCCESS;
}

#pragma once

#include <iostream>
#include <librealsense2/rs.hpp>
#include <memory>
#include <opencv2/opencv.hpp>

#include "CameraInterface.h"
#include "Frame3D.h"
#include "helper.h"

namespace camera
{

class DepthCamera : public CameraTemplate<DepthCamera, Frame3D>
{
private:
    void startImpl()
    {
        pipe.start();
        std::cout << "Depth camera started\n";
    }
    std::unique_ptr<const Frame3D> grabFrameImpl()
    {
        try {
            rs2::frameset data = pipe.wait_for_frames();
            // Wait for next set of frames from the camera
            const rs2::frame image = data.get_color_frame();
            const rs2::frame depth = data.get_depth_frame().apply_filter(color_map);
            
            return std::make_unique<Frame3D>(frameId++, helper::frame_to_mat(image), helper::frame_to_mat(depth));
        } catch (const rs2::error &e) {
            std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args()
                      << "):\n    " << e.what() << std::endl;
            return nullptr;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return nullptr;
        }
    }
    friend CameraTemplate;

    rs2::colorizer color_map;
    rs2::pipeline pipe;
    rs2::config cfg;
    int frameId = 0;
};
} // namespace camera

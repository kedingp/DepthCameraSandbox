#pragma once
#include <vector>

#pragma warning(push, 0)
#include <opencv2/opencv.hpp>
#pragma warning(pop)

#include "Frame3D.h"
#include "ParcelLocator.h"
#include "findSquares.h"

namespace parcel_locator
{
struct Parcel {
    double width;
    double height;
    double depth;

    std::array<cv::Point, 4> topCorners;
};

class ParcelLocatorAlgo : public ParcelLocator<ParcelLocatorAlgo, camera::Frame3D, Parcel>
{
private:
    Parcel findParcelImpl(const camera::Frame3D& inputFrame)
    {
        std::vector<std::vector<cv::Point>> squares;
        findSquares(inputFrame.color_image, squares);

        Parcel result;
        result.depth = 0.;
        result.height = 0.;
        result.width = 0.;

        if (squares.size() > 0) {
            const auto square = squares[0];
            for (auto i = 0; i < square.size(); ++i) {
                result.topCorners[i] = square[i];
            }
        }

        return result;
    }
    friend ParcelLocator;
};
} // namespace parcel_locator

#pragma once
#include <iostream>
#include <memory>

namespace camera
{

template <class CameraType, class FrameType>
class CameraTemplate
{
public:
    void start()
    {
        static_cast<CameraType*>(this)->startImpl();
    }
    std::unique_ptr<const FrameType> grabFrame()
    {
        return static_cast<CameraType*>(this)->grabFrameImpl();
    }
};
} // namespace camera

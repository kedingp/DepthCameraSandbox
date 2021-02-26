#pragma once
#include <iostream>
#include <memory>

#include "CameraInterface.h"

namespace camera
{
struct DummyFrame {
    int id;
};

class DummyCamera2 : public CameraTemplate<DummyCamera2, DummyFrame>
{
public:
    void startImpl() { std::cout << "Camera started\n"; }
    std::unique_ptr<const DummyFrame> grabFrameImpl() { return std::make_unique<DummyFrame>(5); }
};

} // namespace camera

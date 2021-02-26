cmake_minimum_required (VERSION 3.12)

project("DepthCameraSandbox")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
message ("cxx Flags:" ${CMAKE_CXX_FLAGS})

file(GLOB include_files CONFIGURE_DEPENDS "include/*.h")
file(GLOB source_files CONFIGURE_DEPENDS "src/*.cpp")

add_library(DepthCameraSandbox SHARED ${include_files} ${source_files})
target_include_directories(DepthCameraSandbox PRIVATE include)
set_target_properties(DepthCameraSandbox PROPERTIES LINKER_LANGUAGE CXX)

add_executable (FrameRecorder "apps/frameRecorder3D.cpp")
target_include_directories(FrameRecorder PRIVATE include)
target_link_libraries(FrameRecorder DepthCameraSandbox)

add_executable (ParcelLocator "apps/parcelLocator.cpp")
target_include_directories(ParcelLocator PRIVATE include)
target_link_libraries(ParcelLocator DepthCameraSandbox)
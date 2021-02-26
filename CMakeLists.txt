cmake_minimum_required (VERSION 3.12)

project("DepthCameraSandbox")

# Use C++ 20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export all symbols of dlls (important for windows)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Output all binaries, object and lib files in the same folder, respectively
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/obj)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Enable folder structure in IDE, eg. Visual Studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Compile with highest warning level and put it out in command line
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
message ("cxx Flags:" ${CMAKE_CXX_FLAGS})

file(GLOB include_files CONFIGURE_DEPENDS "include/*.h")
file(GLOB source_files CONFIGURE_DEPENDS "src/*.cpp")

# Thirdparty configuration
# =============================================================================

set(VCPKG_PATH "C:/dev/alt_vcpkg/vcpkg" CACHE PATH "Folder to the root of a vcpkg checkout. See https://vcpkg.readthedocs.io/")
if(VCPKG_PATH STREQUAL "")
    message(FATAL_ERROR "Please set VCPKG_PATH. See https://vcpkg.readthedocs.io/")
endif()
if(NOT EXISTS "${VCPKG_PATH}")
    message(FATAL_ERROR "VCPKG_PATH=${VCPKG_PATH} does not point to an existing directory")
endif()

# Add integration for find_package()
set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "")
include(${VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake)

ADD_DEFINITIONS(-DBUILD_SHARED_LIBS=1)


# Add 3rdparty
# =============================================================================
FIND_PACKAGE(realsense2 REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)



add_library(DepthCameraSandbox SHARED ${include_files} ${source_files})
target_include_directories(DepthCameraSandbox PRIVATE include)
target_link_libraries(DepthCameraSandbox
    # External link dependencies
    ${OpenCV_LIBS}
    realsense2::realsense2
    )
set_target_properties(DepthCameraSandbox PROPERTIES LINKER_LANGUAGE CXX)
SET_TARGET_PROPERTIES(DepthCameraSandbox PROPERTIES
    FOLDER "lib"
    )

add_executable (FrameRecorder "apps/frameRecorder3D.cpp")
target_include_directories(FrameRecorder PRIVATE include)
target_link_libraries(FrameRecorder DepthCameraSandbox)
SET_TARGET_PROPERTIES(FrameRecorder PROPERTIES
    FOLDER "exe"
    )

add_executable (ParcelLocator "apps/parcelLocator.cpp")
target_include_directories(ParcelLocator PRIVATE include)
target_link_libraries(ParcelLocator DepthCameraSandbox)
SET_TARGET_PROPERTIES(ParcelLocator PROPERTIES
    FOLDER "exe"
    )

# Add tests
# =============================================================================
ADD_SUBDIRECTORY(tests)

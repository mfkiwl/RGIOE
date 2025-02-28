cmake_minimum_required(VERSION 3.17)

project(RGIOE)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "release")
#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER clang++)


include_directories(
        Inc
)

file(GLOB_RECURSE SOURCE
        Src/*.*
        )


#add_compile_options(-O3)
#

#target_link_libraries(test_kalman Eigen3::Eigen)

find_package(Eigen3 REQUIRED)


#find_package(mklibs REQUIRED)

#add_definitions(-DEIGEN_USE_LAPACK)
#add_definitions(-DEIGEN_USE_MKL_ALL)
#add_definitions(-DEIGEN_USE_MKL_ALL)

add_compile_options(-fPIC)
add_compile_options(-O3)
set(PROJECT_VERSION 1.00)
add_library(LooselyCouple STATIC
        Src/LooselyCouple.cpp
        Src/KalmanFilter.cpp
        Src/DataFusion.cpp
        Src/InsCore.cpp
        Src/Earth.cpp
        Src/Convert.cpp
        Src/Alignment.cpp
        Src/StaticDetect.cpp
        Src/StaticDetect.cpp Inc/StaticDetect.h)
set_target_properties(LooselyCouple PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER Inc/DataFusion.h)
target_link_libraries(LooselyCouple
        Eigen3::Eigen
        )
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Lib)
#set(CUSTOM_OUTDIR Lib/)
set_target_properties(LooselyCouple PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CUSTOM_OUTDIR}"
        )

message("check for Qt5")
find_package(Qt5 COMPONENTS Core)
if (Qt5_FOUND)
    message("found Qt-${Qt5_VERSION} at ${Qt5_DIR}")
    add_subdirectory(App/UiDataFusion)
else (Qt5_FOUND)
    message(WARNING"Qt5 not found,disable UiDataFusion")
endif (Qt5_FOUND)

find_package(yaml-cpp REQUIRED)
find_package(glog REQUIRED)
find_package(lapack REQUIRED)
add_subdirectory(App/PostDataFusion)
#add_subdirectory(App/RtSimulation/src)
add_subdirectory(Tools)
add_subdirectory(Test)
#add_link_options(-lgfortran -lm)


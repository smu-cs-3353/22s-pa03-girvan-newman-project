cmake_minimum_required(VERSION 3.16)
project(22s_pa03_girvan_newman_a_loner_s_regret)

add_executable(22s_pa03_girvan_newman_a_loner_s_regret
        src/main.cpp src/LabelPropagationAlgo.h src/LabelPropagationAlgo.cpp src/GirvanNewman.cpp src/GirvanNewman.h)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.71.0 REQUIRED COMPONENTS graph system filesystem)
message(STATUS "Boost version: ${Boost_VERSION}")

if (NOT TARGET Boost::filesystem)
    add_library(Boost::filesystem IMPORTED INTERFACE)
    set_property(TARGET Boost::filesystem PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
    set_property(TARGET Boost::filesystem PROPERTY INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
endif()

target_link_libraries(22s_pa03_girvan_newman_a_loner_s_regret PUBLIC Boost::graph PUBLIC Boost::system PUBLIC Boost::filesystem)

set(CMAKE_CXX_STANDARD 14)

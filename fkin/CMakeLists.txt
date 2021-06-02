################################################################################
#                                                                              #
# Copyright (C) 2021 Fondazione Istitito Italiano di Tecnologia (IIT)          #
# All Rights Reserved.                                                         #
#                                                                              #
################################################################################

cmake_minimum_required(VERSION 3.12)
project(fkin)

find_package(YARP REQUIRED COMPONENTS os sig math)
find_package(ICUB REQUIRED COMPONENTS ctrlLib iKin)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE YARP::YARP_os YARP::YARP_sig YARP::YARP_math
                                              ICUB::ctrlLib ICUB::iKin)

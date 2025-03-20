# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 23)

include(${CMAKE_CURRENT_LIST_DIR}/components/CMakeLists.txt)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(ESP_Network)

target_sources(app PRIVATE main/main.cpp)

cmake_minimum_required(VERSION 3.15)
project(cronscheduler CXX)

add_compile_options("-v")

find_package(Boost COMPONENTS asio REQUIRED)

include_directories(src)

add_executable(${PROJECT_NAME} 
                src/main.cpp
                src/cronscheduler.cpp)


target_link_libraries(${PROJECT_NAME} PRIVATE Boost::headers)

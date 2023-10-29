cmake_minimum_required(VERSION 3.15)
project(cronscheduler CXX)

add_compile_options("-v")

find_package(Boost COMPONENTS asio REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(src)

add_executable(${PROJECT_NAME} 
                src/main.cpp
                src/cronscheduler.cpp)

add_executable(CronSchedulerTest src/cronscheduler.cpp test/test.cpp)

target_link_libraries(CronSchedulerTest
                      PRIVATE Boost::headers)
enable_testing()

add_test(NAME CronSchedulerTest COMMAND CronSchedulerTest)

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::headers)

cmake_minimum_required(VERSION 3.16)
project(pub1-3)

set(CMAKE_CXX_STANDARD 14)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(turtle_teleop src/turtle_teleop.cpp)
ament_target_dependencies(turtle_teleop
    rclcpp
    geometry_msgs
)

install(TARGETS turtle_teleop
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()


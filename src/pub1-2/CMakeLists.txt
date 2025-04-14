cmake_minimum_required(VERSION 3.16)
project(pub1-2)  # 프로젝트명 변경

set(CMAKE_CXX_STANDARD 14)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)  # 의존성 변경

add_executable(pub1 src/pub1.cpp)
ament_target_dependencies(pub1
    rclcpp
    geometry_msgs  # 의존성 변경
)

install(TARGETS pub1
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()


cmake_minimum_required(VERSION 3.16)
project(pub1-1)  # 프로젝트명 변경

# C++14 표준 사용
set(CMAKE_CXX_STANDARD 14)

# 컴파일 옵션
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 종속성 패키지 검색
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# 실행 파일 빌드
add_executable(pub1 src/pub1.cpp)
ament_target_dependencies(pub1
    rclcpp
    std_msgs
)

# 설치 경로 설정
install(TARGETS
    pub1
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()


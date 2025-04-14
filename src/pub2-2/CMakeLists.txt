cmake_minimum_required(VERSION 3.5)
project(pub2-2)

# 종속성 설정 (geometry_msgs 사용)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)  # std_msgs → geometry_msgs 변경

# 실행 파일 생성
add_executable(pub2_2
  src/pub.cpp
)

# 종속성 연결
ament_target_dependencies(pub2_2
  rclcpp
  geometry_msgs  # 종속 패키지 변경
)

# 설치 규칙
install(TARGETS 
  pub2_2 
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()


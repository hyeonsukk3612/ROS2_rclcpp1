#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"  // 헤더 파일 변경
#include <iostream>

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("pub2_2_node");
  
  // Vector3 타입 퍼블리셔 생성
  auto publisher = node->create_publisher<geometry_msgs::msg::Vector3>("my_topic", 10);

  while(rclcpp::ok()) {
    double x, y, z;
    std::cout << "세 실수 입력 (x y z): ";
    std::cin >> x >> y >> z;  // 키보드 입력 처리

    // 메시지 생성 및 발행
    auto msg = geometry_msgs::msg::Vector3();
    msg.x = x;
    msg.y = y;
    msg.z = z;
    publisher->publish(msg);
    
    RCLCPP_INFO(node->get_logger(), 
      "발행 완료: x=%.2f, y=%.2f, z=%.2f", x, y, z);
  }

  rclcpp::shutdown();
  return 0;
}


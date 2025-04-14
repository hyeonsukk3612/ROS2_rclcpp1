#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"  // Int32 헤더 변경

using namespace std::chrono_literals;

// 콜백 함수: 정수 값 발행
void callback(
  rclcpp::Node::SharedPtr node,
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub  // Int32 타입으로 변경
) {
  static int count = 0;  // 정수 카운터 초기화
  auto message = std_msgs::msg::Int32();
  message.data = count++;
  
  pub->publish(message);
  RCLCPP_INFO(node->get_logger(), "발행 값: %d", message.data);
}

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("pub2_1_node");  // 노드명 변경
  
  // Int32 타입 퍼블리셔 생성
  auto publisher = node->create_publisher<std_msgs::msg::Int32>("my_topic", 10);
  
  // 500ms 주기 타이머 설정
  auto timer = node->create_wall_timer(
    500ms,
    [node, publisher]() { callback(node, publisher); }
  );
  
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}


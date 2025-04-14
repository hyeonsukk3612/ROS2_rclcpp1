#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include <memory>
#include <chrono>
#include <functional>

using namespace std::chrono_literals;

void callback(rclcpp::Node::SharedPtr node,
              rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub) {
    static int count = 0;  // 정수 값 초기화
    auto message = std_msgs::msg::Int32();
    message.data = count++;  // 정수 값 증가
    RCLCPP_INFO(node->get_logger(), "Publish: %d", message.data);  // 로그 출력
    pub->publish(message);  // 메시지 발행
}

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("pub_node");  // 노드 이름 설정
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));    // QoS 설정

    // 퍼블리셔 생성 (토픽 이름: "int_topic")
    auto pub = node->create_publisher<std_msgs::msg::Int32>("int_topic", qos_profile);

    // 타이머를 이용한 주기적 발행 설정 (50ms마다 실행)
    std::function<void()> fn = std::bind(callback, node, pub);
    auto timer = node->create_wall_timer(50ms, fn);

    rclcpp::spin(node);  // 노드 실행
    rclcpp::shutdown();
    return 0;
}

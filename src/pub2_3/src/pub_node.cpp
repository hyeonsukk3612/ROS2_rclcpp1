#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class TurtleCircler : public rclcpp::Node {
public:
  TurtleCircler() : Node("turtle_circler") {
    publisher_ = create_publisher<geometry_msgs::msg::Twist>(
      "/turtle1/cmd_vel", 10);  // 토픽 이름 설정
    
    timer_ = create_wall_timer(
      500ms, std::bind(&TurtleCircler::publish_velocity, this));
    
    RCLCPP_INFO(get_logger(), "원형 운동 제어 노드 시작!");  // 로그 출력
  }

private:
  void publish_velocity() {
    auto message = geometry_msgs::msg::Twist();
    
    // 선속도 설정 (x축 방향으로 2.0 m/s)
    message.linear.x = 2.0;    // 전진 속도
    message.linear.y = 0.0;
    message.linear.z = 0.0;
    
    // 각속도 설정 (z축 기준 1.0 rad/s)
    message.angular.x = 0.0;
    message.angular.y = 0.0;
    message.angular.z = 1.0;   // 회전 속도
    
    publisher_->publish(message);
    RCLCPP_INFO(get_logger(), "명령 발행: 선속도 %.1f m/s, 각속도 %.1f rad/s", 
               message.linear.x, message.angular.z);  // 로그 출력
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TurtleCircler>());
  rclcpp::shutdown();
  return 0;
}


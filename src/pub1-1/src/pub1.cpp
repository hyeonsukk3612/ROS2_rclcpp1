#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"  // 헤더 파일 변경
#include <memory>
#include <chrono>

using namespace std::chrono_literals;

class Int32Publisher : public rclcpp::Node {  // 클래스명 변경
public:
    Int32Publisher() : Node("int32_publisher"), count_(0) {
        publisher_ = this->create_publisher<std_msgs::msg::Int32>("counter", 10);  // 토픽명 변경
        timer_ = this->create_wall_timer(
            1s,  // 1초 주기 (1Hz)
            std::bind(&Int32Publisher::timer_callback, this));
    }

private:
    void timer_callback() {
        auto message = std_msgs::msg::Int32();
        message.data = count_++;
        RCLCPP_INFO(this->get_logger(), "Publishing: %d", message.data);
        publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;  // 타입 변경
    int32_t count_;  // 정수 카운터
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Int32Publisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}


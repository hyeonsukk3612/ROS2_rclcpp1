#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"  // 헤더 변경
#include <memory>
#include <iostream>

using namespace std::chrono_literals;

class Vector3Publisher : public rclcpp::Node {  // 클래스명 변경
public:
    Vector3Publisher() : Node("vector3_publisher") {
        publisher_ = this->create_publisher<geometry_msgs::msg::Vector3>("coordinates", 10);  // 토픽명 변경
        timer_ = this->create_wall_timer(
            1s, [this]() { this->timer_callback(); });
    }

private:
    void timer_callback() {
        auto message = geometry_msgs::msg::Vector3();
        std::cout << "Enter x y z (separated by spaces): ";
        std::cin >> message.x >> message.y >> message.z;
        
        RCLCPP_INFO(this->get_logger(), 
            "Publishing: x=%.2f, y=%.2f, z=%.2f", 
            message.x, message.y, message.z);
            
        publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr publisher_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Vector3Publisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}


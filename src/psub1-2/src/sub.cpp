#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

class IntSubscriber : public rclcpp::Node {
public:
    IntSubscriber() : Node("sub_node") {  // 노드 이름 설정
        subscription_ = this->create_subscription<std_msgs::msg::Int32>(
            "int_topic", rclcpp::QoS(10),
            std::bind(&IntSubscriber::callback, this, std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "구독 노드 시작!");
    }

private:
    void callback(const std_msgs::msg::Int32::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "Subscribed: %d", msg->data);  // 수신된 데이터 출력
    }

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<IntSubscriber>());
    rclcpp::shutdown();
    return 0;
}

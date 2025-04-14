#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <termios.h>
#include <unistd.h>

using namespace std::chrono_literals;

class TurtleTeleop : public rclcpp::Node {
public:
    TurtleTeleop() : Node("turtle_teleop") {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        timer_ = this->create_wall_timer(100ms, [this]() { this->key_loop(); });
        init_terminal();
    }

    ~TurtleTeleop() {
        reset_terminal();
    }

private:
    void init_terminal() {
        tcgetattr(STDIN_FILENO, &orig_termios_);
        struct termios new_termios = orig_termios_;
        new_termios.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    }

    void reset_terminal() {
        tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_);
    }

    void key_loop() {
        char key;
        if (read(STDIN_FILENO, &key, 1) > 0) {
            auto msg = geometry_msgs::msg::Twist();
            
            switch(key) {
                case 'f': msg.linear.x = 2.0; break;
                case 'b': msg.linear.x = -2.0; break;
                case 'l': msg.angular.z = 1.5; break;
                case 'r': msg.angular.z = -1.5; break;
                default: return;
            }

            publisher_->publish(msg);
            RCLCPP_INFO(this->get_logger(), 
                "Published: linear.x=%.1f, angular.z=%.1f", 
                msg.linear.x, msg.angular.z);
        }
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    struct termios orig_termios_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleTeleop>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}


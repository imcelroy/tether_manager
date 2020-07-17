#include "tether_manager/sim_imu.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "sim_imu_node");

    ros::NodeHandle nh_p("");

    std::string topic;

    // outputs
    nh_p.param<std::string>("imu_input", topic, "imu_input");
    ros::Publisher imu_output_pub = nh_p.advertise<sensor_msgs::Imu>(topic, 5);

    double x   = 0;
    double y   = 0;
    double yaw = 0;

    SimIMU sim_imu(x, y, yaw, ros::Time::now());

    while (ros::ok()) {
        ros::spinOnce();
        // publish transformed data
        sim_imu.update_imu(ros::Time::now());
        imu_output_pub.publish(sim_imu.imu_msg());
    }

    return 0;
}

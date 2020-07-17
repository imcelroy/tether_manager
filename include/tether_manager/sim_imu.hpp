#pragma once

#include <cmath>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include <tf2/LinearMath/Quaternion.h>

class SimIMU {
  public:
    SimIMU(double init_x, double init_y, double init_yaw, ros::Time init_time)
      : current_x_(init_x)
      , current_y_(init_y)
      , current_yaw_(init_yaw)
      , current_z_(0)
      , init_time_(init_time) {}

    void update_imu(ros::Time time) {
        // get new northing
        current_y_ = current_y_ + 0.1 * sin(current_yaw_);

        // get new easting
        current_x_ = current_x_ + 0.1 * cos(current_yaw_);

        // get new heading
        current_yaw_ = 0.05 * (time.toSec() - init_time_.toSec());
    }

    sensor_msgs::Imu imu_msg() {
        sensor_msgs::Imu msg;

        geometry_msgs::Quaternion quat_msg;

        tf2::Quaternion q;

        // set msg
        q.setRPY(0, 0, current_yaw_);
        q.normalize();

        // tf2::convert(q, quat_msg);
        quat_msg        = tf2::toMsg(q);
        msg.orientation = quat_msg;

        return msg;
    }

  private:
    double current_x_;
    double current_y_;
    double current_yaw_;

    double current_z_;

    ros::Time init_time_;
};

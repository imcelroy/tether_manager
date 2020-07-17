#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "tether_manager/sim_imu.hpp"

using testing::AllOf;
using testing::Eq;
using testing::Gt;
using testing::Lt;
using testing::NiceMock;
using testing::StrEq;

class SimIMUTest : public ::testing::Test {
  protected:
    ros::NodeHandle nh;
    ros::NodeHandle nh_p;

  public:
    SimIMUTest()
      : nh(ros::NodeHandle())
      , nh_p(ros::NodeHandle("~"))
      , sim_imu_(0.0, 0.0, 0.0, ros::Time::now()) {}

    ~SimIMUTest() {}

  protected:
    SimIMU sim_imu_;
};

TEST_F(SimIMUTest, ZeroYawAtZeroTime) {
    EXPECT_EQ(0.0, sim_imu_.imu_msg().orientation.z);
}

TEST_F(SimIMUTest, YawNonZeroAfterOneSecondTest) {
    ros::Duration(1.0).sleep();
    sim_imu_.update_imu(ros::Time::now());
    EXPECT_TRUE(sim_imu_.imu_msg().orientation.z > 0.02);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    ros::init(argc, argv, "test_tether_manager_sim");
    ros::start();

    return RUN_ALL_TESTS();
}

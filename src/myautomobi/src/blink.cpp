#include "ros/ros.h"
#include <string>
#include <std_msgs/String.h>
#include <sstream>
int main(int argc,char **argv)
{
    ros::init(argc,argv,"talker");
    ros::NodeHandle n;
    ros::Publisher chatter_pub=n.advertise<std_msgs::String>("toggle_led",1000);//发布节点
    ros::Rate loop_rate(0.5);//0.5Hz发送消息

    while(ros::ok())
    {
        std_msgs::String msg;
        std::stringstream ss;
        ss<<"toogle_led";
        msg.data=ss.str();
        ROS_INFO("%s",msg.data.c_str());//打印发送消息
        chatter_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
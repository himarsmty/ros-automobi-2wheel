#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

class teleop_automobi{
private:
    ros::NodeHandle _nh;
    ros::Publisher _cmd_vel_pub;
public:
    teleop_automobi(ros::NodeHandle nh)
    {
        _nh=nh;
        _cmd_vel_pub=_nh.advertise<geometry_msgs::Twist>("cmd_vel",1);
    }
    bool keyboardloop()
    {
        std::cout<<"\npress 'w' to forward";
        std::cout<<"\npress 's' to backward";
        std::cout<<"\npress 'a' to turn left";
        std::cout<<"\npress 'd' to turn right\n";
        geometry_msgs::Twist cmd_msg;
        char cmd[50];
        while(_nh.ok())
        {
            std::cin.getline(cmd,50);
            if(cmd[0]!='w'&&cmd[0]!='a'&&cmd[0]!='d'&&cmd[0]!='s'&&cmd[0]!='q')
            {
                std::cout<<"unknown command:"<<cmd<<std::endl;
                continue;
            }
            cmd_msg.linear.x=cmd_msg.angular.z=cmd_msg.linear.y=0;
            switch(cmd[0])
            {
                case 'w':
                {
                cmd_msg.linear.x=20;
                cmd_msg.angular.z=0;
                break;
                }
                case 'a':
                {
                cmd_msg.linear.x=0;
                cmd_msg.angular.z=-20;
                break;
                }
                case 's':
                {
                cmd_msg.linear.x=-20;
                cmd_msg.angular.z=0;
                break;
                }
                case 'd':
                {
                cmd_msg.linear.x=0;
                cmd_msg.angular.z=20;
                break;
                case 'q':
                {
                    cmd_msg.linear.x=0;
                    cmd_msg.angular.z=0;
                    break;
                }
                default:
                {
                    cmd_msg.linear.x=0;
                    cmd_msg.angular.z=0;
                }
                }
            }
            _cmd_vel_pub.publish(cmd_msg);
        }
        return true;
    }
};

int main(int argc,char **argv)
{
    ros::init(argc,argv,"teleop_automobi_keyboard");
    ros::NodeHandle nh;
    teleop_automobi teleop_control(nh);
    teleop_control.keyboardloop();
    ros::spin();
}
#include <ros/ros.h>

using namespace std;
int main(int argc,char **argv)
{
    ros::init(argc,argv,"param");
    ros::NodeHandle n;
    ros::NodeHandle pn("~my_namespace");
    string s;
    int num;
    n.param<string>("string_param",s,"first");
    pn.param<int>("int_param",num,1);

    n.setParam("string_param","second");
    pn.setParam("int_param",2);

    printf("string_param:%s",s.c_str());
    printf("int_param:%d",num);

    ros::Rate loop_rate(0.5);

       while (ros::ok())
    {
        n.getParam("string_param",s);   
        printf("string_param:  %s\n", s.c_str());
        pn.getParam("int_param",num);
        printf("int_param:  %d\n\n", num);

        ros::spinOnce();
        loop_rate.sleep();
    }
}
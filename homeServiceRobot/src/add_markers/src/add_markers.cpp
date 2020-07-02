#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <complex>

float goal_pickup[3] = {-1, -2, 1};
float goal_dropoff[3] = { -2, -4, 1};
float delta = 0.2;
bool pickup = false;
bool dropoff = false;
bool haveobject = false;

void callback(const nav_msgs::Odometry::ConstPtr& msg)
{ 
  
//Pick up
if (std::abs(goal_pickup[0] -msg->pose.pose.position.x) < delta && std::abs(goal_pickup[1] -msg->pose.pose.position.y) < delta)
   { 
    if(!pickup)
    {
     pickup = true;
    }
   }
else{pickup = false;}

//Drop off
if (std::abs(goal_dropoff[0] -msg->pose.pose.position.x) < delta && std::abs(goal_dropoff[1] -msg->pose.pose.position.y) < delta)
  { 
    if(!dropoff)
    {
     dropoff = true;
    }
   }else{dropoff = false;}

}



int main( int argc, char** argv )
{
  ROS_INFO("Main");
  ros::init(argc, argv, "basic_shapes");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("odom", 1000, callback);
  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "odom";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = goal_pickup[0];
    marker.pose.position.y = goal_pickup[1];
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = goal_pickup[2];

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);


    ROS_INFO("Pick-up marker displayed");
   
   //Wait for Pick-Up
   while(!pickup)
   {
    ros::spinOnce();
   }
   
   if(pickup && !haveobject)
   {
    ros::Duration(3.0).sleep();
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    ROS_INFO("Pick-up marker removed");
    haveobject = true;
   }  
   
   //Wait for Drop-Off
   while(!dropoff)
   {
    ros::spinOnce();
   }

   if(dropoff && haveobject)
   {
    marker.pose.position.x = goal_dropoff[0];
    marker.pose.position.y = goal_dropoff[1];
    marker.pose.orientation.w = goal_dropoff[2];
    ros::Duration(3.0).sleep();
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    ROS_INFO("Drop-off marker displayed");
    haveobject = false;

    ros::Duration(5.0).sleep();
    return 0;
    // r.sleep();
   }
  }
}

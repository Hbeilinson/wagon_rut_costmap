// #include <ros/ros.h>
#include <convert_to_grid/convert_to_grid.h>
// #include "grid_map_ros/GridMapRosConverter.hpp"
// #include <grid_map_core/grid_map_core.hpp>


// using namespace cv;
// using namespace grid_map;

ConvertToGrid::ConvertToGrid()
{
  ROS_INFO_STREAM("on line 12");
  ros::NodeHandle nh;
  costmap_sub = nh.subscribe("/move_base/global_costmap/costmap", 1, &ConvertToGrid::costmap_callback, this);
  gridmap_pub = nh.advertise<grid_map_msgs::GridMap>("/gridmap", 1, true);
  // gridmap_pub.advertise()
  const std::vector<std::string>& layers = std::vector<std::string>{"costmap"};
  // GridMap mapIn({"layer"});
  map = GridMap(layers); //look at something in cmake lists possibly?
  // map.add("costmap");
  map.setFrameId("map");
  map.setGeometry(Length(2.0, 2.00), 0.05);

}

void ConvertToGrid::costmap_callback(const nav_msgs::OccupancyGrid& costmap)
{
  GridMapRosConverter::fromOccupancyGrid(costmap, "costmap", map);
  grid_map_msgs::GridMap message;
  GridMapRosConverter::toMessage(map, message);
  gridmap_pub.publish(message);
  cv::Mat image;
  string cost = string("costmap");
  GridMapCvConverter::toImage<unsigned short, 1>(map, cost, CV_16UC1, image); //go look at grid map tests
  const std::string &dispwin = "Display window";
  //namedWindow(dispwin);// Create a window for display.
  //imshow( "Display window", image);
  imwrite("map.jpg", image);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "convert_to_grid");
  ROS_INFO_STREAM("on line 41");
  // ros::NodeHandle n;
  ConvertToGrid cg;
  ros::spin();
  return 0;
}

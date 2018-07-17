#include <ros/ros.h>
#include <convert_to_grid/convert_to_grid.h>

ConvertToGrid::ConvertToGrid()
{
  ros::NodeHandle nh;
  costmap_sub = nh.subscribe("/move_base/global_costmap/costmap", 1, &ConvertToGrid::costmap_callback, this);
  // gridmap_pub.advertise()
  map({"costmap"});
  map.setFrameId("map");
  map.setGeometry(Length(200, 200), 0.05);
}

ConvertToGrid::costmap_callback(const OccupancyGrid& costmap)
{
  GridMapRosConverter::fromOccupancyGrid(costmap, "costmap", map);
  GridMapCvConverter::toImage(map, "costmap", image);
  namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Display window", image );
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "convert_to_grid");
//  ROS_INFO_STREAM("here");
  // ros::NodeHandle n;
  ConvertToGrid cg(n);
  ros::spin();
  return 0;
}

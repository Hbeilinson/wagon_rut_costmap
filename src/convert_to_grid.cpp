#include <convert_to_grid/convert_to_grid.h>

//to read in parameter in constructor, use this syntax: navigatorNode.param("map_inflation_radius", mInflationRadius, 1.0);


ConvertToGrid::ConvertToGrid()
{
  ROS_INFO_STREAM("on line 12");
  ros::NodeHandle nh;
  costmap_sub = nh.subscribe("my_costmap", 1, &ConvertToGrid::costmap_callback, this);
  update_sub = nh.subscribe("/move_base/global_costmap/costmap_updates", 1, &ConvertToGrid::convert_occupancy_grid, this);
  gridmap_pub = nh.advertise<grid_map_msgs::GridMap>("/gridmap", 1, true);
  update_pub = nh.advertise<nav_msgs::OccupancyGrid>("my_costmap", 1, true);
  // publish_image = nh.advertise("camera/image", 1);
  const std::vector<std::string>& layers = std::vector<std::string>{"costmap"};
  // GridMap mapIn({"layer"});
  map = GridMap(layers); //look at something in cmake lists possibly?
  map.add("elevation", 0.0);
  // elevation = GridMap({"elevation"});
  // map.add("costmap");
  map.setFrameId("map");
  map.setGeometry(Length(2.0, 2.00), 0.05);

}

void ConvertToGrid::convert_occupancy_grid(const map_msgs::OccupancyGridUpdate& gridupdate)
{
  nav_msgs::OccupancyGrid ocgrid = nav_msgs::OccupancyGrid();
  nav_msgs::MapMetaData metadata = nav_msgs::MapMetaData();
  metadata.map_load_time.sec = 0;
  metadata.map_load_time.nsec = 0;
  metadata.resolution = 0.05;
  metadata.width = gridupdate.width;
  metadata.height = gridupdate.height;
  metadata.origin.position.x = 0.0;
  metadata.origin.position.y = 0.0;
  metadata.origin.position.z = 0.0;
  metadata.origin.orientation.x = 0.0;
  metadata.origin.orientation.y = 0.0;
  metadata.origin.orientation.z = 0.0;
  metadata.origin.orientation.w = 1.0;
  ocgrid.info = metadata;
  ocgrid.header = gridupdate.header;
  ocgrid.data = gridupdate.data;
  update_pub.publish(ocgrid);

}

void ConvertToGrid::costmap_callback(const nav_msgs::OccupancyGrid& costmap)
{
  GridMapRosConverter::fromOccupancyGrid(costmap, "costmap", map);
  grid_map_msgs::GridMap message;
  GridMapRosConverter::toMessage(map, message);
  gridmap_pub.publish(message);
  cv::Mat image;
  string cost = string("costmap");
  GridMapCvConverter::toImage<unsigned short, 1>(map, cost, CV_16UC1, 0.0, 100.0, image); //go look at grid map tests
  const std::string &dispwin = "Display window";
  //namedWindow(dispwin);// Create a window for display.
  //imshow( "Display window", image);
  imwrite("/home/strider/catkin_ws/src/simple_costmap_layer/world_files/even_older_map.pgm", image);
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

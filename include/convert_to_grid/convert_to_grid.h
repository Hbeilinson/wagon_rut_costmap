#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include "grid_map_ros/GridMapRosConverter.hpp"
#include <grid_map_msgs/GridMap.h>
// #include <iostream>

#include "nav_msgs/OccupancyGrid.h"
#include "map_msgs/OccupancyGridUpdate.h"
#include "nav_msgs/MapMetaData.h"

#include <grid_map_cv/GridMapCvConverter.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

using namespace std;
using namespace grid_map;
using namespace cv;


class ConvertToGrid
{
  public:
    ros::Subscriber costmap_sub;
    ros::Publisher gridmap_pub;
    ros::Subscriber update_sub;
    ros::Publisher update_pub;
    ConvertToGrid();
    void costmap_callback(const nav_msgs::OccupancyGrid& costmap);
    void convert_occupancy_grid(const map_msgs::OccupancyGridUpdate& gridupdate);
    GridMap map;
    GridMap elevation;
    // cv::Mat& image;
};

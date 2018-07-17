#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map/grid_map.hpp>
#include "nav_msgs/OccupancyGrid.h"
#include "GRIDMAP2D_GRIDMAP2D_H_"
#include <GridMapRosConverter.hpp>
#include <GridMapCvConverter.hpp>

using namespace nav_msgs;
using namespace cv;


class ConvertToGrid:
{
  public:
    ros::Subscriber costmap_sub;
    ros::Publisher gridmap_pub;
    ConvertToGrid();
    void costmap_callback(const OccupancyGrid& costmap);
    GridMap map;
    cv::Mat& image;
};

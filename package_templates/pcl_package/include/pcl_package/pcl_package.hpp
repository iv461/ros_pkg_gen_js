#ifndef {{PackageNameUpperCase}}_HPP
#define {{PackageNameUpperCase}}_HPP
#include <sensor_msgs/PointCloud2.h>

// ros headers
#include <ros/ros.h>
#include <tf/transform_listener.h>

// PCL ROS
#include <pcl_ros/point_cloud.h>

// STL
#include <vector>
#include <algorithm>
#include <chrono>
#include <memory>
#include <numeric>
#include <sstream>
#include <thread>

{% if bond_used %}
// bonds
#include <bondcpp/bond.h>
{% endif %}

// Eigen
#include <Eigen/Dense>

{% if dynamic_reconfigure_used %}
// dynamic reconfigure
#include <dynamic_reconfigure/server.h>
#include <{{PackageName}}/{{PackageName}}Config.h>
{% endif %}

namespace {{Namespace}} {

using std::string;
using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::cout;
using std::endl;
using std::begin;
using std::end;
using std::thread;

/**
 * @brief {{PackageClassName}}
 */
class {{PackageClassName}} {
public:
    {{PackageClassName}}(ros::NodeHandle& node_handle,
                        ros::NodeHandle& private_node_handle);

/**
 * @brief init_on_param_change this is called every time
 * the dynamic reconfigure parameters are changed.
 * So here you do all what is necessary when
 * the parameters are changed, like relocating memory etc.
 */
void init_on_param_change();
/**
 * @brief loop a loop function which can be used to do work.
 * @param do_spin if this is true the call to this function calls
 * the ros spinning and blocks
 */
void loop(bool do_spin);

/**
 * @brief pcl_callback a example callback for a pointcloud2 message
 * @param points
 */
void pcl_callback(pcl::PointCloud<pcl::PointXYZ> const &points);

private:
ros::NodeHandle m_node_handle;
ros::NodeHandle m_private_node_handle;
ros::Subscriber m_subscriber;
ros::Publisher m_publisher;

{% if bond_used %}
bond::Bond m_alive_bond;
{% endif %}

tf::TransformListener tf_listener;

{% if dynamic_reconfigure_used %}
using dyn_cfg_t = {{PackageName}}::{{PackageName}}Config;
dynamic_reconfigure::Server<dyn_cfg_t> m_reconfigure_server;
/**
 * @brief m_cfg copy of the dynamic reconfigure struct, updated in reconfigure_callback
 */
dyn_cfg_t m_cfg;

/**
 * @brief reconfigure_callback this function gets called when a dynamic
 * reconfigure parameter is changed
 * @param config the config
 * @param level mask to indicate which param was changed
 */
void reconfigure_callback(dyn_cfg_t &config, uint32_t level);
{% else %}
struct Config {
  string input_topic;
  string output_topic;
};
Config m_cfg;
{% endif %}

};

} // end namespace {{Namespace}}

#endif // {{PackageNameUpperCase}}_HPP

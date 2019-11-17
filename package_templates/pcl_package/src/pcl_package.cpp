#include <{{PackageName}}.hpp>

#include <stdexcept>

namespace {{Namespace}} {

{{PackageClassName}}::{{PackageClassName}}(ros::NodeHandle &node_handle,
ros::NodeHandle &private_node_handle) :

    m_node_handle(node_handle),
    m_private_node_handle(private_node_handle)
{% if dynamic_reconfigure_used %}
    ,m_reconfigure_server(private_node_handle)
{% endif %}
{% if bond_used %}
    ,m_alive_bond("alive",
                 private_node_handle.getNamespace().substr(1),
                 node_handle, true)
{% endif %}
{
{% if dynamic_reconfigure_used %}
    m_reconfigure_server.setCallback
            (boost::bind(&{{PackageClassName}}::reconfigure_callback, this, _1, _2));
{% else %}
    m_private_node_handle.getParam("input_topic", m_cfg.input_topic);
    m_private_node_handle.getParam("output_topic", m_cfg.output_topic);
    init_on_param_change();
{% endif %}
{% if bond_used %}
    m_alive_bond.start();
{% endif %}
}

void {{PackageClassName}}::init_on_param_change() {
    string err;
    if(m_cfg.input_topic == "") {
        err = "input_topic cannot be empty";
    }
    if(m_cfg.output_topic == "") {
        err = "output_topic cannot be empty";
    }
    if(err != "") {
        ROS_ERROR("error in config, cannot continue");
        throw std::invalid_argument(err);
    }
    m_publisher = m_node_handle.advertise<pcl::PointCloud<pcl::PointXYZ>>
            (m_cfg.output_topic , 1);

    m_subscriber = m_node_handle.subscribe(m_cfg.input_topic, 1,
                                        &{{PackageClassName}}::pcl_callback,
                                        this);

    // change here all other things which depend on parameters
}


void {{PackageClassName}}::pcl_callback
(pcl::PointCloud<pcl::PointXYZ> const &points) {
      // some silly offsetting
      auto out_pcl = points;
      for(auto &point : out_pcl) {
{% if dynamic_reconfigure_used %}
        point.z += m_cfg.pcl_offset;
{% else %}
        point.z += 20.;
{% endif %}
      }
      m_publisher.publish(out_pcl);
}

void {{PackageClassName}}::loop(bool do_spin) {
    thread spin_thread([&]() {
        ros::Rate r(20); // 20Hz
        // main loop. ok() is false when node is killed
        while(ros::ok()) {

            // publish here something

            if(do_spin) {
                ros::spinOnce();
            }
            // sleep a period to reach the rate
            r.sleep();
        }
    });
    if(do_spin) {
        // the loop function does not return until the thread returns if we call
        // join (join blocks here)
        spin_thread.join();
    } else {
        // if we don't want to block we call detach so the
        // thread can run independently of its std::thread object (which
        // gets destructed on returning of this function )
        spin_thread.detach();
    }
}
{% if dynamic_reconfigure_used %}
void {{PackageClassName}}::reconfigure_callback(dyn_cfg_t &config, uint32_t level) {
    m_cfg = config;
    init_on_param_change();
}
{% endif %}

} // end namespace {{Namespace}}

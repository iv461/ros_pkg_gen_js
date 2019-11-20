#include <memory>

#include <ros/ros.h>

#include "{{PackageName}}.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "{{PackageName}}");
    ros::NodeHandle nh, pnh("~");
    auto class_instance =
    std::make_unique<{{Namespace}}::{{PackageClassName}}>(nh, pnh);
    class_instance->loop(true);
    return 0;
}

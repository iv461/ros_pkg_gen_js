#include <memory>

#include <ros/ros.h>

#include "{{PackageName}}.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "{{PackageName}}");
    ros::NodeHandle nh, pnh("~");
    auto class_instance =
    std::unique_ptr<{{Namespace}}::{{PackageClassName}}>(
                new {{Namespace}}::{{PackageClassName}}(nh, pnh));
    class_instance->loop(true);
    return 0;
}

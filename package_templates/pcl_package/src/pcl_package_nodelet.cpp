#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>

#include <memory>

#include "{{PackageName}}.hpp"

namespace {{Namespace}} {
class {{PackageClassName}}Nodelet : public nodelet::Nodelet {
public:
    virtual void onInit() override {
        m_class_instance = std::unique_ptr<{{PackageClassName}}>(
                    new {{PackageClassName}}(getMTNodeHandle(),
                     getMTPrivateNodeHandle()));
        // loop is false because the onInit should not block
        m_class_instance->loop(false);
    }
private:
    std::unique_ptr<{{PackageClassName}}> m_class_instance;
};
} // end namespace {{Namespace}}

PLUGINLIB_EXPORT_CLASS({{Namespace}}::{{PackageClassName}}Nodelet, nodelet::Nodelet)

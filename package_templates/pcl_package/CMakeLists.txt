cmake_minimum_required(VERSION 3.2.2)

project({{PackageName}})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  pcl_conversions
  pcl_ros
  tf
{% if dynamic_reconfigure_used %}
  dynamic_reconfigure
{% endif %}
{% if bond_used %}
  bondcpp
{% endif %}
)

{% if dynamic_reconfigure_used %}
generate_dynamic_reconfigure_options(
    cfg/{{PackageName}}.cfg
    )
{% endif %}

catkin_package(
    #  INCLUDE_DIRS include
    #  LIBRARIES pcl_package_nodelet
    #  CATKIN_DEPENDS roscpp
    #  DEPENDS system_lib
    )

include_directories(
    include
    include/{{PackageName}}
    ${catkin_INCLUDE_DIRS}
    )

{% if nodelet_used %}
add_library(${PROJECT_NAME}
    src/{{PackageName}}.cpp
    src/{{PackageName}}_nodelet.cpp
)
{% endif %}

{% if nodelet_used %}
add_dependencies(${PROJECT_NAME}
    ${${PROJECT_NAME}_EXPORTED_TARGETS}
    ${catkin_EXPORTED_TARGETS}
{% if dynamic_reconfigure_used %}
    ${PROJECT_NAME}_gencfg
{% endif %}
)
{% endif %}

add_executable(${PROJECT_NAME}_node
    src/{{PackageName}}.cpp
    src/{{PackageName}}_node.cpp
)

add_dependencies(${PROJECT_NAME}_node
    ${${PROJECT_NAME}_EXPORTED_TARGETS}
    ${catkin_EXPORTED_TARGETS}
{% if dynamic_reconfigure_used %}
    ${PROJECT_NAME}_gencfg
{% endif %}
)

target_link_libraries(${PROJECT_NAME}_node
    ${catkin_LIBRARIES}
)

{% if nodelet_used %}
target_link_libraries(${PROJECT_NAME}
    ${catkin_LIBRARIES}
)
{% endif %}

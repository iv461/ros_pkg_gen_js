# ROS Package Generator JS

Supports creating Nodes, nodelets with dynamic reconfigure and other options.

[Nunjucks](https://mozilla.github.io/nunjucks/) is used as template engine,
so new templates with new functionality can be added easily.

# Usage

### Install dependencies
``` npm install ```

### Example

An example C++ package named ``pcl_package`` is provided in the ``package_templates`` folder.

`` node create_package.js '{ "template_name":"pcl_package",
"name" :"<package name>", "nodelet_used":<bool value>,
"dynamic_reconfigure_used":<bool ovalue>}' ``

The package generator now writes the package to the default location ``~/catkin_ws/src`` (customizable with ``path`` parameter).
It also sets necessary permissions in the case ``dynamic_reconfigure`` is used so the package 
can be build immediatly e.g with ``catkin_make``.

# TODOs

- Move parameter definitions to the templates.

# License

Licensed under the BSD-3 license.

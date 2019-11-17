# ROS Package Generator JS

Supports creating Nodes, nodelets with dynamic reconfigure and other options.

[Nunjucks](https://mozilla.github.io/nunjucks/) is used as template engine,
so new templates with new functionality can be added easily.

# Usage

### Install dependencies
``` npm install ```

### Example:

``` node create_package.js '{ "<template_name>":"pcl_package",
"name" :"<package name>", "nodelet_used":<bool value>,
"dynamic_reconfigure_used":<bool ovalue>}' ```

#### TODOs

- Move parameter definitions to the templates.

# License

Licensed under the BSD-3 license.

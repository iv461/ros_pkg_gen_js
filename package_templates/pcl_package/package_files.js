"use strict";
const get_files = (params) => {
  let files =
[
    {
      "source": "README_TEMPLATE.md",
      "target": "README.md"
    },
    {
        "source": "package.xml",
        "target": "package.xml"
    },
    {
        "source": "include/pcl_package/pcl_package.hpp",
        "target": `include/${params.PackageName}/${params.PackageName}.hpp`
    },
    {
      "source": "src/pcl_package.cpp",
      "target": `src/${params.PackageName}.cpp`
    },
    {
      "source": "src/pcl_package_node.cpp",
      "target": `src/${params.PackageName}_node.cpp`
    },
    {
        "source": "CMakeLists.txt",
        "target": "CMakeLists.txt"
    },
    {
        "source": "launch/test_node.launch",
        "target": "launch/test_node.launch"
    },
    {
        "source": "launch/params.yaml",
        "target": "launch/params.yaml"
    }
];
if(params.nodelet_used) {
  files.push(
  {
      "source": "nodelet_plugins.xml",
      "target": "nodelet_plugins.xml"
  },
  {
    "source": "src/pcl_package_nodelet.cpp",
    "target": `src/${params.PackageName}_nodelet.cpp`
  },
  {
      "source": "launch/test_nodelet.launch",
      "target": "launch/test_nodelet.launch"
  }
);
}
if(params.dynamic_reconfigure_used) {
  files.push(
    {
          "source": "cfg/pcl_package.cfg",
          "target": `cfg/${params.PackageName}.cfg`,
          "add_executable_permission": true
      });
}
return files;
};

module.exports.get_files = get_files;

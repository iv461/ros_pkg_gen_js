"use strict";
const path = require('path');
const nj = require("nunjucks")
const fs = require('fs');
const os = require('os');

// these nice SO code snippets
const ensure_directory_existence = (filePath) => {
  var dirname = path.dirname(filePath);
  if (fs.existsSync(dirname)) {
    return true;
  }
  ensure_directory_existence(dirname);
  fs.mkdirSync(dirname);
}

const isDirectory = source => fs.lstatSync(source).isDirectory();

const getDirectories = source =>
  fs.readdirSync(source).map(name =>
    path.join(source, name)).filter(isDirectory);

const snake_case_to_pascal_case = (str) => {
  let first_upper = str.charAt(0).toUpperCase() + str.slice(1);
  return first_upper.replace(/([-_][a-z])/g, (group) =>
      group.toUpperCase()
                    .replace('-', '')
                    .replace('_', ''));
};

const rem_first_after_underscore = (str) => str.substring(str.indexOf('_') + 1);

const package_name_to_class_name = (str) => snake_case_to_pascal_case
(rem_first_after_underscore(str));

const check_params = (params) => {
  if(!params.PackageName) {
    console.log("Parameter error: name cannot be empty");
    return false;
  }
  params.TargetPath += params.PackageName;
  return true;
}

const main = () => {
  nj.configure({ "autoescape": false, "throwOnUndefined": true,
   "trimBlocks": true});
  if(process.argv[2] === "-h"
     || process.argv[2] === "--help"
     || !process.argv[2]) {
    const available_options_str = 'node create_package.js \
\'{ \
"template_name":"<template_name>", "name":"<package_name>", ["nodelet_used":<bool value>], ["bond_used":<bool value>],\
["dynamic_reconfigure_used":<bool value>], ["author":"<author>"], ["author_mail":"\
<author_mail>"], ["license":"<license>"], ["description": "<description>"],\
["license": "<license>"], ["path": "<path>"]\
}\'';
    console.log("Usage: " + available_options_str);
    return;
  }
  let options;
  try {
     options = JSON.parse(process.argv[2]);
  } catch(e) {
    console.log("Error in parsing command line: " + e);
    return;
  }
  if(!options) {
    console.log("Error in parsing command line: empty object");
    return;
  }
  let params = {
    "PackageName": (options.name || ""),
    "TargetPath": (options.path || (os.homedir() + "/catkin_ws/src/")),
    "PackageNameUpperCase": (options.name || "").toUpperCase(),
    "PackageClassName": package_name_to_class_name(options.name || ""),
	"Namespace" : (options.namespace || "ns"),
    "Author": (options.author || "TODO"),
    "AuthorMail": (options.author_mail || "todo@example.com"),
    "License": (options.license || "All rights reserved."),
    "Description": (options.description || "A Package"),
    "dynamic_reconfigure_used" : (options.dynamic_reconfigure_used === undefined ? true : options.dynamic_reconfigure_used),
    "nodelet_used" : (options.nodelet_used === undefined ? true : options.nodelet_used),
    "bond_used" : (options.bond_used === undefined ? true : options.bond_used)
  };
  if(!check_params(params)) {
    return;
  }
  console.log("params are");
  console.log(params);
  const used_path = __dirname + "/package_templates/" + options.template_name;
  const used_path_files = used_path + "/package_files.js";
    let files;
    if (fs.existsSync(used_path_files)) {
      files = require(used_path_files).get_files(params);
    } else {
      console.log("Template does not exist!");
      return;
    }

    files.forEach((file) => {
    let file_str = fs.readFileSync(used_path + "/" + file.source, "utf8");

    let replaced = nj.renderString(file_str, params);

    let target_file_path = params.TargetPath + "/" + file.target;
    ensure_directory_existence(target_file_path);
    console.log(`writing to ${target_file_path}`);
    fs.writeFileSync(target_file_path, replaced, "utf8");
    if(file.add_executable_permission) {
      fs.chmodSync(target_file_path, 0o765);
    }
    });
    console.log("Created successfully.");
}

main();

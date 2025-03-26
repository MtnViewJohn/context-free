#!/usr/bin/env node

var cfdg = require('./cfdg.js');
var fs = require('fs');

cfdg.onRuntimeInitialized = () => {
  // console.log(cfdg);
  // console.log(cfdg.FS);
  // console.log(process.cwd());
  // console.log(cfdg.FS.cwd());
  // console.log(cfdg.FS.readdir(cfdg.FS.cwd()));
  var [_node, _script, ...args] = [...process.argv];
  cfdg.callMain(args);
};


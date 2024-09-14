#!/usr/bin/env node

var cfdg = require('./cfdg.js');
cfdg.onRuntimeInitialized = () => {
  var [_node, _script, ...args] = [...process.argv];
  cfdg.callMain(args);
};


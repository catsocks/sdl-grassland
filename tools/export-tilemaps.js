#!/usr/bin/env node
const fs = require('fs');
const path = require('path');
const {spawnSync} = require('child_process');
const yargs = require('yargs');

const argv = yargs
    .scriptName('export-tilemaps')
    .usage('Export Tiled maps to CSV files')
    .help()
    .alias('help', 'h')
    .version(false)
    .options({
      'output-folder': {
        alias: 'o',
        description: 'path to the folder the tilemaps will be exported to',
        requiresArg: true,
        required: true,
      },
    })
    .argv;

argv.outputFolder = path.join(argv.outputFolder, 'tilemaps');

try {
  fs.mkdirSync(argv.outputFolder);
} catch (err) {
  if (err.code !== 'EEXIST') {
    throw err;
  }
}

const sourceFolder = path.join('assets', 'Tiled');
fs.readdirSync(sourceFolder).forEach((file) => {
  const filePath = path.join(sourceFolder, file);
  const extname = path.extname(file);
  if (fs.statSync(filePath).isDirectory() || extname !== '.tmx') {
    return;
  }

  const output = path.join(argv.outputFolder, path.basename(file, extname));
  const result = spawnSync(`tiled`, ['--export-map', 'csv', filePath, output]);
  if (result.status !== 0) {
    if (result.stderr) {
      throw new Error(msg + ': ' + result.stderr.toString().trim());
    }
    throw new Error(msg);
  }
});

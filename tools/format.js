const fs = require('fs');
const path = require('path');

const commentBegin = '//******************************************************************************';
const commentEnd = '--*/';
const newComment = `//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://iMonitorSDK.com

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact admin@iMonitorSDK.com
  
--*/`.replace(/\n/g, '\r\n');

function isIgnoreDir(dir) {
  return dir.indexOf('third_party') !== -1;
}

function formatFile(file) {
  const ext = path.extname(file);
  if (ext !== '.h' && ext !== '.cpp') {
    return;
  }
  const text = fs.readFileSync(file).toString('latin1');
  if (!text.startsWith(commentBegin)) {
    return;
  }
  const end = text.indexOf(commentEnd);
  if (end === -1) {
    return;
  }
  const newText = newComment + text.substr(end + commentEnd.length);
  fs.writeFileSync(file, Buffer.from(newText, 'latin1'));
  console.log('format file: ' + file);
}

function formatDir(dir) {
  if (isIgnoreDir(dir)) {
    return;
  }
  fs.readdirSync(dir, {withFileTypes: true}).forEach((file) => {
    const filepath = path.join(dir, file.name);
    if (file.isDirectory()) {
      formatDir(filepath);
      return;
    }
    formatFile(filepath);
  });
}

formatDir(__dirname + '/../src');

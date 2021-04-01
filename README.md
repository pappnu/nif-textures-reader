# Nif Textures Reader

A Node addon for fetching the index, name, texture paths, material path and wet
material path from each shape in a NIF file (Gamebryo/NetImmerse File Format).

## Installation

[Node-addon-api](https://github.com/nodejs/node-addon-api) and
[CMake.js](https://github.com/cmake-js/cmake-js) are required for compiling. If
they aren't already present, install them:
```
npm install --save-dev node-addon-api cmake-js
```

Install this package with:
```
npm install pappnu/nif-textures-reader
```

## Usage
```
import { nifTexturesReader } from 'nif-textures-reader';

let shapes = nifTexturesReader.read('path/to/file.nif');
console.log(shapes);
```

## C++ libraries used

- [nifly](https://github.com/ousnius/nifly)
- [JSON for Modern C++](https://github.com/nlohmann/json)

## License

MIT for all parts that don't fall under nifly's GPL-3.0.

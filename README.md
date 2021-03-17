# Nif Textures Reader

A Node addon for fetching the index, name and texture paths for each shape in a NIF file
(Gamebryo/NetImmerse File Format).

## Installation
Installation using npm:

```
npm install https://github.com/pappnu/nif-textures-reader.git
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

const nifTexturesReader = require('bindings')('nif-textures-reader.node');

module.exports = {
    read: (path) => {
        let shapesStr = nifTexturesReader.read(path);
        return JSON.parse(shapesStr);
    }
};

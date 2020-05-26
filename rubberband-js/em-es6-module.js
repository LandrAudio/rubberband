// EXPORT_ES6 option does not work as described at
// https://github.com/kripken/emscripten/issues/6284, so we have to
// manually add this by '--post-js' setting when the Emscripten compilation.
export default Module;

Module.createFloatArray = function(length) {
    let pointer = _malloc(length * 4);
    return {
        length,
        pointer,
        array: new Float32Array(this.HEAPF32.buffer, pointer, length),
    };
};

Module.destroyFloatArray = function(arr) {
    arr.array = null;
    arr.length = 0;
    _free(arr.pointer);
};

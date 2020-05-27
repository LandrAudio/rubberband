Module["createFloatArray"] = function(length) {
    const pointer = _malloc(length * 4);
    return {
        length,
        pointer,
        array: new Float32Array(this.HEAPF32.buffer, pointer, length),
    };
};

Module["destroyFloatArray"] = function(arr) {
    arr.array = null;
    arr.length = 0;
    _free(arr.pointer);
};

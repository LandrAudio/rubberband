
# Rubber Band JS bindings

## How to build
The following instructions were only tested on macOS and are not expected to work on other platforms. Use at your own risk.

1. Install Emscripten:
    ```
    brew install emscripten
    ```

1. Build rubberband with Emscripten, using the libraries built in the previous steps:
    ```
    emconfigure ./configure CXXFLAGS='-DNO_THREADING' --disable-vamp --disable-programs --disable-ladspa --enable-speex --enable-kissfft
    emmake make
    ```
    + Then generate the bindings:
        ```
        emcc --bind -o rubberband.js rubberband-js/Exports.cpp -I. -Llib -lrubberband
        ```

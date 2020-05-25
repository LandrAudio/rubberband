
# Rubber Band JS bindings

## How to build
The following instructions were only tested on macOS and are not expected to work on other platforms. Use at your own risk.

1. Install Emscripten:
    ```
    brew install emscripten
    ```

1. Create a new folder that we'll use to install the executables compiled with Emscripten:
    ```
    sudo mkdir /usr/local/em
    ```

1. Build fftw3 with Emscripten and install it to `/usr/local/em`:
    ```
    curl http://fftw.org/fftw-3.3.8.tar.gz -O fftw-3.3.8.tar.gz
    tar -xzf fftw-3.3.8.tar.gz
    cd fftw-3.3.8
    emconfigure ./configure --prefix=/usr/local/em --disable-shared
    emmake make
    sudo emmake make install
    ```

1. Build libsamplerate with Emscripten and install it to `/usr/local/em`:
    ```
    curl http://www.mega-nerd.com/SRC/libsamplerate-0.1.9.tar.gz -O libsamplerate-0.1.9.tar.gz
    tar -xzf libsamplerate-0.1.9.tar.gz
    cd libsamplerate-0.1.9
    sed -i "" 's/examples //g' Makefile.in
    emconfigure ./configure --prefix=/usr/local/em --disable-shared
    emmake make
    sudo emmake make install
    ```

1. Build rubberband with Emscripten, using the libraries built in the previous steps:
    ```
    emconfigure ./configure --prefix=/usr/local/em PKG_CONFIG_PATH=/usr/local/em/lib/pkgconfig CXXFLAGS='-DNO_THREADING -DNO_FILESYSTEM' --disable-vamp --disable-programs --disable-ladspa
    emmake make
    ```
    + Then generate the bindings:
        ```
        emcc --bind -o rubberband.js rubberband-js/Exports.cpp -I. -Llib -L/usr/local/em/lib -lrubberband -lfftw3 -lsamplerate
        ```

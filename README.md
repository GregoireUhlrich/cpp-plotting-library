# cpp-plotting-library
Scientific plotting library for C++

## Build

``` bash
    mkdir build
    cd build
    cmake ..
    make
```

To build the doc an explicit target must be given to `make`:
``` bash
    make doc
```
The main page can then be found at `build/doc/index.html`.

## Run tests

Once the package has been built, just run
``` bash
    ctest
```

## Run tests with code coverage

To enable code coverage, the package must be built in coverage mode:
``` bash
    mkdir build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Coverage
    make
    make coverage_units
```
The coverage report is then available at `build/coverage_units/units/index.html`.

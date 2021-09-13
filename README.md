# Barthes

A terminal text editor

## Usage

Barthes requires a single argument: a path to a file.

Example:
```bash
barthes path/to/file.cpp
```

## Build

Currently, this project relies on `cmake` to build from source. Please make sure that you have this program downloaded on your system.

To build, run the following to build `barthes` from source:

```bash
cmake -S . -B build -DCMAKE_OSX_SYSROOT=$(xcrun --show-sdk-path)  # omit `DCMAKE_OSX_SYSROOT` if not on OSX
cmake --build build
```

## Testing

Follow the steps above to build the program from source, then run the following command:

```bash
ctest --test-dir build/test --output-on-failure
```

#!/bin/bash

BUILD_DIR="$(pwd)/build"
COMPILER_DIR="$(pwd)/external/esp32-toolchain/xtensa-esp32-elf/bin/"

export PATH="$COMPILER_DIR:${PATH}"

TAG="$(git describe --abbrev=0)"
LATEST_COMMIT="$(git rev-parse --short HEAD)"
NBR_COMMITS_NOW="$(git rev-list $LATEST_COMMIT --count)"
NBR_COMMITS_TAG="$(git rev-list $TAG --count)"

VERSION_MAJOR="${TAG%.*}"
VERSION_MINOR="${TAG#*.}"
VERSION_BUILD=`expr $NBR_COMMITS_NOW - $NBR_COMMITS_TAG`

which xtensa-esp32-elf-gcc && xtensa-esp32-elf-gcc --version
which ninja-build && ninja-build --version
which cmake && cmake --version

if [ $# -eq 0 ]; then
  rm -rf build
  mkdir build
  cmake -S . -B build -D_VERSION_MAJOR=$VERSION_MAJOR -D_VERSION_MINOR=$VERSION_MINOR -D_VERSION_BUILD=$VERSION_BUILD -DCMAKE_TOOLCHAIN_FILE=external/freertos/tools/cmake/toolchains/xtensa-esp32.cmake -G Ninja
  cmake --build build
elif [[ $# -eq 2 ]] && [[ $1 = "debug" ]] && [[ "${2}" =~ ^[0-9]+$ ]]; then
  echo Setting DEBUG_PRINT_LEVEL to $2
  rm -rf build
  mkdir build
  cmake -S . -B build -D_DEBUG_PRINT_LEVEL=$2 -DIDF_SDK_CONFIG_DEFAULTS=config/esp32/sdkconfig.defaults -DCMAKE_TOOLCHAIN_FILE=external/freertos/tools/cmake/toolchains/xtensa-esp32.cmake -G Ninja
  cmake --build build
elif [[ $# -eq 2 ]] && [[ $1 = "release" ]] && [[ "${2}" =~ ^[0-9]+$ ]]; then
  rm -rf build
  mkdir build
  cmake -S . -B build -D_VERSION_MAJOR=$VERSION_MAJOR -D_VERSION_MINOR=$VERSION_MINOR -D_VERSION_BUILD=$2 -DCMAKE_TOOLCHAIN_FILE=external/freertos/tools/cmake/toolchains/xtensa-esp32.cmake -G Ninja
  cmake --build build
elif [[ $# -eq 1 ]] && [[ $1 = "flash" ]]; then
  cmake --build build --target flash
elif [[ $# -eq 1 ]] && [[ $1 = "erase" ]]; then
  ./external/freertos/vendors/espressif/esp-idf/tools/idf.py erase_flash
elif [[ $# -eq 2 ]] && [[ $1 = "monitor" ]]; then
  echo "Trying to monitor with device $2. If your connection is using another device, please change in script"
  ./external/freertos/vendors/espressif/esp-idf/tools/idf.py monitor -p $2 -B build
elif [[ $# -eq 2 ]] && [[ $1 = "all" ]]; then
  rm -rf build
  mkdir build
  cmake -S . -B build -D_DEBUG_PRINT_LEVEL=9 -D_VERSION_MAJOR=$VERSION_MAJOR -D_VERSION_MINOR=$VERSION_MINOR -D_VERSION_BUILD=$VERSION_BUILD -DIDF_SDK_CONFIG_DEFAULTS=config/esp32/sdkconfig.defaults -DCMAKE_TOOLCHAIN_FILE=external/freertos/tools/cmake/toolchains/xtensa-esp32.cmake -G Ninja
  cmake --build build --target flash
  ./external/freertos/vendors/espressif/esp-idf/tools/idf.py monitor -p $2 -B build
else
  echo "Unknown command! Usage:"
  echo "./build.sh                - compile"
  echo "./build.sh debug <level>  - compile with debug logs enabled at provided level"
  echo "./build.sh flash          - flash"
  echo "./build.sh monitor <port> - monitor output"
  echo "./build.sh erase          - erase flash"
  echo "./build.sh all <port>     - builds with max highest debug resolution, flashes and starts monitoring"
fi

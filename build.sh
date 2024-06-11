set -xe

watch() {
    ls ./CMakeLists.txt | entr -sc "./build.sh clean build"
}

build() {
    cmake --no-warn-unused-cli \
          -DCMAKE_BUILD_TYPE:STRING=Debug \
          -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
          -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang \
          -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ \
          -S$(pwd) \
          -B$(pwd)/build \
          -G Ninja
}

clean() {
    rm -rf ./build/*
}

run() {
    cmake --build ./build --config Debug --target all --
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH/usr/local/lib:
    ./$(find build -maxdepth 1 -type f -executable)
}


av_args=(run build clean watch)

if [ ! -d "build" ]; then
    mkdir build
fi

for arg in "$@"; do
    if echo ${av_args[@]} | grep -q -w $arg; then
        $arg 
    else
        echo -e "COMMAND NOT FOUND: $arg";
        echo -e "Available commands: \n\t- $(echo ${av_args[@]} | sed -e 's/ /\n\t\- /g')"
    fi
done

#g++ ./src/main.cpp src/glad.c -Iinclude -lglfw -ldl -o myapp
BUILD_DIRECTORY="./build"

if [ $1 = "build" ]
then
    if [ ! -d "$BUILD_DIRECTORY" ]
    then
        mkdir build
    fi
    cd build
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
    make
elif [ $1 = "run" ]
then
    cd src/
    ../build/graphics
fi

#g++ ./src/main.cpp src/glad.c -Iinclude -lglfw -ldl -o myapp
if [ $1 = "build" ]
then
    cd build
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
    make
elif [ $1 = "run" ]
then
    cd src/
    ../build/graphics
fi

@echo off

mkdir .\real-engine
mkdir .\real-engine\lib

xcopy /e .\template\include .\real-engine\include\
copy .\template\src\build_project.py .\real-engine
gcc -I .\template\include  -c .\template\src\glad.c -o glad.o
ar -crv .\real-engine\lib\libglad.a glad.o
del /q glad.o

::wget https://github.com/glfw/glfw/archive/3.3.4.zip
7z x 3.3.4.zip
::del 3.3.4.zip
mkdir .\glfw-3.3.4\build
xcopy /e .\glfw-3.3.4\include\GLFW .\real-engine\include\GLFW\
cd .\glfw-3.3.4\build
cmake -DBUILD_SHARED_LIBS=ON -G "MinGW Makefiles" ..
mingw32-make -j12
move .\src\glfw3.dll ..\..\real-engine\lib
cd ..\..
rd /s /q .\glfw-3.3.4

::wget https://github.com/assimp/assimp/archive/v4.1.0.zip
7z x v4.1.0.zip
::del v4.1.0.zip
mkdir .\assimp-4.1.0\build
xcopy /e .\assimp-4.1.0\include\assimp .\real-engine\include\assimp\
del .\real-engine\include\assimp\config.h.in
cd .\assimp-4.1.0\build
cmake -G "MinGW Makefiles" ..
mingw32-make -j12
move .\code\libassimp.dll ..\..\real-engine\lib
move .\include\assimp\config.h ..\..\real-engine\include\assimp
cd ..\..
rd /s /q .\assimp-4.1.0

pause
@echo off

mkdir .\project
mkdir .\project\src
mkdir .\project\build
mkdir .\project\resources
mkdir .\project\resources\model
xcopy /e .\template\shader .\project\resources\shader\
copy .\template\src\main.cpp .\project\src
copy .\template\config.json .\project
@echo off

mkdir .\project
mkdir .\project\src
mkdir .\project\build
mkdir .\project\resources
copy .\template\src\main.cpp .\project\src
copy .\template\config.json .\project
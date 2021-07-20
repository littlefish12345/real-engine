@echo off

xcopy /e /y .\real-engine\include\real-engine .\template\include\real-engine
copy /y .\project\src\main.cpp .\template\src
rd /s /q .\template\shader
xcopy /e .\project\resources\shader .\template\shader\
pause
@echo off

rem // Parameters:
rem // 1 = $(SolutionDir).
rem // 2 = $(ProjectDir).
rem // 3 = $(OutDir).
rem // 4 = $(Configuration)
rem // 5 = $(Platform)


echo Copying DLLs from libraries...
xcopy "%1\Libraries\glew-2.1.0\bin\%4\%5\glew32.dll" "%3" /Y
xcopy "%1\Libraries\glfw-3.3.2\lib-vc2019\glfw3.dll" "%3" /Y

xcopy "%1\Libraries\zlib-1.2.8.8\bin\%4\%5\zlibd.dll" "%3" /Y
xcopy "%1\Libraries\libpng-1.6.28.1\bin\%4\%5\libpng16.dll" "%3" /Y



echo Copying resource files...
rmdir /Q /S "%3\resource"
xcopy "%2\resource" "%3\resource" /Y /E /I



echo Deleting old logs...
if exist "logs" rmdir /Q /S "logs"
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
xcopy "%1\Libraries\libpng-1.2.37\bin\libpng12.dll" "%3" /Y
xcopy "%1\Libraries\libpng-1.2.37\bin\zlib1.dll" "%3" /Y


echo Copying resource files...
xcopy "%2\resource" "%3\resource" /Y /E /I
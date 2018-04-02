cls
::if exist build rmdir /S /Q build
::mkdir build
cd build

cmake -G "Visual Studio 8 2005" ../ -DCMAKE_CXX_FLAGS="/wd4996 /EHsc" -DMSVC_RUNTIME=static || exit /b

C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727\MSBuild.exe spline_test.sln /p:Configuration=Debug || exit /b
ctest --verbose --output-on-failure

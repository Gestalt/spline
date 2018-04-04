cls
if exist build rmdir /S /Q build
mkdir build
cd build

cmake -G "Visual Studio 8 2005" ../ -DUSE_BOOST:BOOL=ON || exit /b

cmake --build . --config Release || exit /b
ctest --verbose --output-on-failure
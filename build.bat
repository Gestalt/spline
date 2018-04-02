cls
::if exist build rmdir /S /Q build
::mkdir build
cd build

cmake -G "Borland Makefiles" ../ || exit /b
make || exit /b

spline -s src.txt -d dest.txt -h --spline Quadric -v
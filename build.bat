cls
if exist build rmdir /S /Q build
if exist bin rmdir /S /Q bin
mkdir build
mkdir bin

cd build

cmake -G "Visual Studio 8 2005" ../ -DUSE_BOOST:BOOL=ON || exit /b
cmake --build . --config Release || exit /b

cd ../bin

echo "Integration tests running ..."

release\spline
release\spline -h

for %%x in ( Neighbor Linear Quadric Unknown ) do (

release\spline -s resources\notfound.txt -d resources\dest.txt --spline %%x -v
release\spline -s resources\src.txt -d resources\dest.txt --spline %%x -v
release\spline -s resources\src.txt -d resources\notfound.txt --spline %%x -v
release\spline -s resources\src_bad.txt -d resources\dest_bad.txt --spline %%x -v
release\spline -s resources\src_empty.txt -d resources\dest_empty.txt --spline %%x -v
release\spline -s resources\src_toofew.txt -d resources\dest_toofew.txt --spline %%x -v
release\spline -s resources\src_corrupted.txt -d resources\dest_corrupted.txt --spline %%x -v
release\spline -s resources\src_notenough.txt -d resources\dest_notenough.txt --spline %%x -v
release\spline -s resources\src_outofrange.txt -d resources\dest_outofrange.txt --spline %%x -v
release\spline -s resources\src_negative.txt -d resources\dest_negative.txt --spline %%x -v

)

echo "Success"
exit 0

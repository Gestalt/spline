cls
if exist build rmdir /S /Q build
mkdir build
cd build

cmake -G "Borland Makefiles" -DUSE_BOOST:BOOL=ON ../ || exit /b
make || exit /b

echo "Integration tests running ..."

spline
spline -h

for %%x in ( Neighbor Linear Quadric Unknown ) do (

spline -s resources\notfound.txt -d resources\dest.txt --spline %%x -v
spline -s resources\src.txt -d resources\dest.txt --spline %%x -v
spline -s resources\src.txt -d resources\notfound.txt --spline %%x -v
spline -s resources\src_bad.txt -d resources\dest_bad.txt --spline %%x -v
spline -s resources\src_empty.txt -d resources\dest_empty.txt --spline %%x -v
spline -s resources\src_toofew.txt -d resources\dest_toofew.txt --spline %%x -v
spline -s resources\src_corrupted.txt -d resources\dest_corrupted.txt --spline %%x -v
spline -s resources\src_notenough.txt -d resources\dest_notenough.txt --spline %%x -v
spline -s resources\src_outofrange.txt -d resources\dest_outofrange.txt --spline %%x -v
spline -s resources\src_negative.txt -d resources\dest_negative.txt --spline %%x -v

)

echo "Success"
exit 0

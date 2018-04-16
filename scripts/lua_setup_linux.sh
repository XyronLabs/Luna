lua_version=lua-5.3.4

mkdir -p ../include/lua
mkdir -p ../source/lua
mkdir -p ../libraries

echo Downloading 
curl -R -O http://www.lua.org/ftp/$lua_version.tar.gz
tar zxf $lua_version.tar.gz

cd $lua_version
make linux
rm src/*.o

cd ..
mv $lua_version/src/*.a ../libraries
mv $lua_version/src/*.h ../include/lua
mv $lua_version/src/*.hpp ../include/lua
mv $lua_version/* ../source/lua
rm $lua_version.tar.gz
rm -r $lua_version/

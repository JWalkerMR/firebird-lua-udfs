@echo off

set LUA_DIR=lua-5.1.4
set FB_DIR=firebird-2.5\jrd
set MD5_DIR=md5-1.4
set LIB_DIR=../link.win32
set OUT_DIR=../build.win32
set OPT=-DUSE_IB_UTIL_MALLOC
set C_FILES=lua_udf.c %MD5_DIR%/md5.c
set OBJ_FILES=lua_udf md5
set LIB_FILES=lua51.lib ib_util_ms.lib

cd src

cl.exe /I %LUA_DIR% /I %FB_DIR% /I %MD5_DIR% %OPT% -DWINDOWS /c %C_FILES%

link.exe %OBJ_FILES% %LIB_FILES% /libpath:%LIB_DIR% /DLL /out:%OUT_DIR%\lua_udf.dll

cd ..


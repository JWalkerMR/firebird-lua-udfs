@echo off

set LUA_DIR=lua-5.1.4
set FB_DIR=firebird-2.5\jrd
set MD5_DIR=md5-1.4
set OPT=-DUSE_IB_UTIL_MALLOC -DLUA_UDF_FILE=%LUA_UDF_FILE%
set C_FILES=lua_udf.c %MD5_DIR%/md5.c
set OUT_DIR=..\build.win32
set OBJ_FILES=lua_udf.obj md5.obj %OUT_DIR%\lua51.lib %OUT_DIR%\ib_util_ms.lib

cd src

cl.exe /I %LUA_DIR% /I %FB_DIR% /I %MD5_DIR% %OPT% -DWINDOWS /c %C_FILES%

link.exe %OBJ_FILES% /DLL /out:%OUT_DIR%\lua_udf.dll


REM !!! The unit tests don't work if lua_udf is compiled with -DUSE_IB_UTIL_MALLOC !!!

cd unit-tests

set OUT_DIR=..\%OUT_DIR%

cl.exe -DWINDOWS /c test_lua_udf.c
link.exe test_lua_udf.obj %OUT_DIR%\lua_udf.lib /out:%OUT_DIR%\test_lua_udf.exe

cd ..

cd ..


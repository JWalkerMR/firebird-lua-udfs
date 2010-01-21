#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <ibase.h>
#include <ib_util.h>

typedef long long int int64;

#define INIT __attribute__ ((constructor))
#define FINI __attribute__ ((destructor))
#define EXPORT

#define LUA_UDF_FILE "gazolin_lua_udfs.lua"

lua_State* L;

int EXPORT reload() {
    return luaL_dofile(L, LUA_UDF_FILE);
}

void INIT init() {
    L = luaL_newstate();
    if (L)
	reload();
}

void FINI fini() {
    lua_close(L);
}

void push_paramdsc(lua_State* L, PARAMDSC* p) {
    lua_createtable(L, 6, 0); // { dtype, scale, length, subtype, flags, content }
    lua_pushnil(L); lua_pushnumber(L, p->dsc_dtype);	lua_settable(L, -3);
    lua_pushnil(L); lua_pushnumber(L, p->dsc_scale);	lua_settable(L, -3);
    lua_pushnil(L); lua_pushnumber(L, p->dsc_length);	lua_settable(L, -3);
    lua_pushnil(L); lua_pushnumber(L, p->dsc_sub_type);	lua_settable(L, -3);
    lua_pushnil(L); lua_pushnumber(L, p->dsc_flags);	lua_settable(L, -3);
    lua_pushnil(L); lua_pushlstring(L, (char*)p->dsc_address, p->dsc_length); lua_settable(L, -3);
    /*
    switch(p->dsc_dtype) {
	case dtype_text:
	    lua_pushlstring(L, (char*)p->dsc_address, p->dsc_length);
	    break;
	case dtype_cstring:
	    lua_pushstring(L, (char*)p->dsc_address);
	    break;
	case dtype_varying:
	    lua_pushlstring(L, (char*)p->dsc_address+2, *(short*)p->dsc_address);
	    break;
	case dtype_byte:
	    lua_pushnumber(L, *(char*)p->dsc_address);
	    break;
	case dtype_short:
	    lua_pushnumber(L, *(short*)p->dsc_address);
	    break;
	case dtype_long:
	    lua_pushnumber(L, *(int*)p->dsc_address);
	    break;
	case dtype_quad:
	    lua_pushnumber(L, *(int64*)p->dsc_address);
	    break;
	case dtype_real:
	    lua_pushnumber(L, *(float*)p->dsc_address);
	    break;
	case dtype_double:
	    lua_pushnumber(L, *(double*)p->dsc_address);
	    break;
	case dtype_sql_date:
	    lua_pushnumber(L, *(int*)p->dsc_address);
	    break;
	case dtype_sql_time:
	    lua_pushnumber(L, *(int*)p->dsc_address);
	    break;
	case dtype_timestamp:
	    lua_pushnumber(L, *(int64*)p->dsc_address);
	    break;
	case dtype_int64:
	    lua_pushnumber(L, *(int64*)p->dsc_address);
	    break;
	default:
	    lua_pushnil(L);
    }
    lua_settable(L, -3);
    */
}

void f1p(const char* fname, PARAMDSC* p1) {
    lua_getfield(L, LUA_GLOBALSINDEX, fname);
    push_paramdsc(L, p1);
    lua_call(L, 1, 1);
}

void f2p(const char* fname, PARAMDSC* p1, PARAMDSC* p2) {
    lua_getfield(L, LUA_GLOBALSINDEX, fname);
    push_paramdsc(L, p1);
    push_paramdsc(L, p2);
    lua_call(L, 2, 1);
}

void f3p(const char* fname, PARAMDSC* p1, PARAMDSC* p2, PARAMDSC* p3) {
    lua_getfield(L, LUA_GLOBALSINDEX, fname);
    push_paramdsc(L, p1);
    push_paramdsc(L, p2);
    push_paramdsc(L, p3);
    lua_call(L, 3, 1);
}

double ret_double() {
    double r = lua_tonumber(L, -1);
    lua_pop(L, -1);
    return r;
}

char* ret_varchar() {
    size_t len;
    const char* s;
    char* r;
    s = lua_tolstring(L, -1, &len);
    r = ib_util_malloc(len + 2);
    *(short*)r = len;
    memcpy(r+2, s, len);
    lua_pop(L, -1);
    return r;
}

// EXPORTS //
#define d1p(fname) double EXPORT fname(PARAMDSC* p1)					{ f1p((#fname), p1); 		return ret_double(); }
#define d2p(fname) double EXPORT fname(PARAMDSC* p1, PARAMDSC* p2)			{ f2p((#fname), p1, p2); 	return ret_double(); }
#define d3p(fname) double EXPORT fname(PARAMDSC* p1, PARAMDSC* p2, PARAMDSC* p3)	{ f3p((#fname), p1, p2, p3); 	return ret_double(); }
#define v1p(fname) char* EXPORT fname(PARAMDSC* p1)					{ f1p((#fname), p1); 		return ret_varchar(); }
#define v2p(fname) char* EXPORT fname(PARAMDSC* p1, PARAMDSC* p2)			{ f2p((#fname), p1, p2); 	return ret_varchar(); }
#define v3p(fname) char* EXPORT fname(PARAMDSC* p1, PARAMDSC* p2, PARAMDSC* p3)		{ f3p((#fname), p1, p2, p3);	return ret_varchar(); }

v1p(md5)


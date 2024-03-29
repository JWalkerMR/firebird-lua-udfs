#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef WINDOWS
    #include <windows.h>
#else
    #include <pthread.h>
#endif
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "md5.h"
#include "ibase.h"

#define ABI __cdecl

#ifdef WINDOWS
    #define EXPORT __declspec(dllexport)
#endif

typedef long long int int64;

#ifdef USE_IB_UTIL_MALLOC
    #define malloc ib_util_malloc
    #include "ib_util.h"
#endif

// INIT/FINI //

lua_State* L;

int ltry(char* f, int err) {
    if (err) {
        printf("%s failed [%d]: %s", f, err, lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    return !err;
}

EXPORT int ABI load_lua_lib(char* lua_udf_file);

#ifdef WINDOWS

HANDLE LM;

BOOL APIENTRY DllMain(HANDLE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            LM = CreateMutex(NULL, FALSE, NULL);
            //load_lua_lib(LUA_UDF_FILE);
        case DLL_PROCESS_DETACH:
            CloseHandle(LM);
    }
    return TRUE;
}

void mutex_lock() {
    WaitForSingleObject(LM, INFINITE);
}

void mutex_unlock() {
    ReleaseMutex(LM);
}

#else

pthread_mutex_t VLM;
pthread_mutex_t* LM = &VLM;

void __attribute__ ((constructor)) ABI init() {
    pthread_mutex_init(LM, NULL);
    //load_lua_lib(LUA_UDF_FILE);
}

void __attribute__ ((destructor)) ABI fini() {
    if (L) lua_close(L);
    pthread_mutex_destroy(LM);
}

void mutex_lock() {
    pthread_mutex_lock(LM);
}

void mutex_unlock() {
    pthread_mutex_unlock(LM);
}

#endif

// LUA EXPORTS //

EXPORT int ABI load_lua_lib(char* lua_udf_file) {
    int ok;

	if (!lua_udf_file)
        return 0;

    mutex_lock();

    ok = L != 0;

    if (ok) lua_close(L);

    ok = ltry("luaL_newstate", (L = luaL_newstate()) == 0);
    if (ok) {
		ok = ltry("luaL_loadfile", luaL_loadfile(L, lua_udf_file));
		if (ok) {
			luaL_openlibs(L);
			ok = ltry("lua_pcall", lua_pcall(L, 0, LUA_MULTRET, 0));
		}
    }

    mutex_unlock();

    return ok;
}

// LUA-FB BINDING HELPERS //

void push_varchar(lua_State* L, char* s) {
    if (!s)
	lua_pushnil(L);
    else
        lua_pushlstring(L, s + sizeof(short), *(short*)s);
}

void push_double(lua_State* L, double* d) {
	if (!d)
		lua_pushnil(L);
	else
		lua_pushnumber(L, *d);
}

char* ret_varchar(lua_State* L) {
    size_t len;
	const char* s;
	char* r;

	if (lua_isnil(L, -1))
	return 0;

    s = lua_tolstring(L, -1, &len);
    r = malloc(len + sizeof(short));
    *(short*)r = len;
    memcpy(r + sizeof(short), s, len);
    lua_pop(L, 1);
    mutex_unlock();
    return r;
}

double ret_double(lua_State* L) {
    double r;

	if (lua_isnil(L, -1))
	return 0;

    r = lua_tonumber(L, -1);
    lua_pop(L, 1);
    mutex_unlock();
    return r;
}

// C EXPORTS //

EXPORT int ABI file_is_readable(char* s) {
    FILE* f;

	if (!s) return 0;
    f = fopen(s+2, "r");
    if (f) {
	fclose(f);
		return 1;
	}
    return 0;
}

EXPORT char* ABI bin_to_hex(char* s) {
	char* hex;
	int len;
	char* r;
    int i;

	if (!s) return 0;

	hex = "0123456789ABCDEF";
    len = *(short*)s;
    r = malloc(len*2 + sizeof(short) + sizeof(char));

    *(short*)r = len*2;
    r[len*2 + sizeof(short)] = 0;
    for (i = 0; i < len; i++) {
		r[i*2+2] = hex[s[i+2] >> 4 & 0x0F];
		r[i*2+3] = hex[s[i+2] & 0x0F];
	}
    return r;
}

EXPORT char* ABI md5(char* s) {
    md5_state_t state;
    md5_byte_t digest[16];
	char* r;

	if (!s)
		return 0;

    md5_init(&state);
    md5_append(&state, (const md5_byte_t *)(s+2), *(short*)s);
    md5_finish(&state, digest);

    r = malloc(16 + sizeof(short) + sizeof(char));
    *(short*)r = 16;
    r[16 + sizeof(short)] = 0;
    memcpy(r+2, &digest, 16);
    return r;
}

// LUA EXPORTS //

char* v_v(char* f, char* s) {
    mutex_lock();
    lua_getglobal(L, f);
    push_varchar(L, s);
    lua_call(L, 1, 1);
    return ret_varchar(L);
}

double d_v(char* f, char* s) {
    mutex_lock();
    lua_getglobal(L, f);
    push_varchar(L, s);
    lua_call(L, 1, 1);
    return ret_double(L);
}

char* v_vv(char* f, char* p, char* s) {
    mutex_lock();
    lua_getglobal(L, f);
    push_varchar(L, p);
    push_varchar(L, s);
    lua_call(L, 2, 1);
    return ret_varchar(L);
}

double d_vv(char* f, char* p, char* s) {
    mutex_lock();
    lua_getglobal(L, f);
    push_varchar(L, p);
    push_varchar(L, s);
    lua_call(L, 2, 1);
    return ret_double(L);
}

char* v_vvv(char* f, char* p1, char* p2, char* s) {
    mutex_lock();
    lua_getglobal(L, f);
    push_varchar(L, p1);
    push_varchar(L, p2);
    push_varchar(L, s);
    lua_call(L, 3, 1);
    return ret_varchar(L);
}

EXPORT char* ABI sbc_replace_chars(char* find, char* replace, char* s) {
	return v_vvv("sbc_replace_chars", find, replace, s);
}

EXPORT char* ABI utf8_replace_chars(char* find, char* replace, char* s) {
	return v_vvv("utf8_replace_chars", find, replace, s);
}

EXPORT char* ABI utf8_replace_but_chars(char* leave, char* replace, char* s) {
	return v_vvv("utf8_replace_but_chars", leave, replace, s);
}

EXPORT double ABI utf8_made_of(char* list, char* s) {
	return d_vv("utf8_made_of", list, s);
}

EXPORT double ABI utf8_is_integer(char* s) {
	return d_v("utf8_is_integer", s);
}

// TESTING //

EXPORT char* ABI test_call_chain(char* s) {
    size_t len;
	const char* t;
	char* r;

	mutex_lock();
    lua_getglobal(L, "test");
    lua_pushlstring(L, s, strlen(s));
    lua_call(L, 1, 1);
    t = lua_tolstring(L, -1, &len);
    r = malloc(len + sizeof(char));
    memcpy(r, t, len + sizeof(char));
    lua_pop(L, 1);
    mutex_unlock();
    return r;
}

EXPORT char* ABI test_varchar_conv(char* s) {
    mutex_lock();
    push_varchar(L, s);
    return ret_varchar(L);
}


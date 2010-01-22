
#define ABI __cdecl

#ifdef WINDOWS
	#define IMPORT __declspec(dllimport)
#endif

// imports

// load_lua_lib(cstring(N) octets) returns integer
IMPORT int ABI load_lua_lib(char* lua_udf_file);

// md5(varchar(N) any_charset) returns varchar(16) octets
IMPORT char* ABI md5(char* s);

// bin_to_hex(varchar(N) octets) returns varchar(N*2) any_ascii_superset
IMPORT char* ABI bin_to_hex(char* s);

// sbc_replace_chars(varchar(N) any_sbc) returns varchar(N) any_sbc
IMPORT char* ABI sbc_replace_chars(char* find, char* replace, char* s);

// utf8_replace_chars(varchar(N) utf8) returns varchar(N) utf8
IMPORT char* ABI utf8_replace_chars(char* find, char* replace, char* s);

// utf8_replace_but_chars(varchar(N) utf8) returns varchar(N) utf8
IMPORT char* ABI utf8_replace_but_chars(char* leave, char* replace, char* s);

// utf8_made_of(varchar(MAX) utf8) returns double by reference free_it
IMPORT double ABI utf8_made_of(char* list, char* s);

// utf8_is_integer(varchar(MAX) utf8) returns double by reference free_it
IMPORT double ABI utf8_is_integer(char* s);

// file_is_readable(varchar(N) octets) returns integer by value
IMPORT int ABI file_is_readable(char* s);

// testing
IMPORT char* ABI test_call_chain(char* s);
IMPORT char* ABI test_varchar_conv(char* s);


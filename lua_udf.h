
// exports

int load_lua_lib(char* lua_udf_file);

// md5(varchar(N) any_charset) returns varchar(16) octets
char* md5(char* s);			

// bin_to_hex(varchar(N) octets) returns varchar(N*2) any_ascii_superset
char* bin_to_hex(char* s);

// sbc_replace_chars(varchar(N) any_sbc) returns varchar(N) any_sbc
char* sbc_replace_chars(char* find, char* replace, char* s);

// utf8_replace_chars(varchar(N) utf8) returns varchar(N) utf8
char* utf8_replace_chars(char* find, char* replace, char* s);

// utf8_replace_but_chars(varchar(N) utf8) returns varchar(N) utf8
char* utf8_replace_but_chars(char* leave, char* replace, char* s);

// utf8_made_of(varchar(MAX) utf8) returns double by reference free_it
double* utf8_made_of(char* list, char* s);

// utf8_is_integer(varchar(MAX) utf8) returns double by reference free_it
double* utf8_is_integer(char* s);

// testing
char* test_call_chain(char* s);
char* test_varchar_conv(char* s);


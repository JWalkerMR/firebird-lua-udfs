#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lua_udf.h"

// tools //
char* to_varchar(char* s) {
    int len = strlen(s);
    char* r = malloc(len + sizeof(short));
    *(short*)r = (short)len;
    memcpy(r + sizeof(short), s, len);
    return r;
}

char* from_varchar(char* s) {
    int len = *(short*)s;
    char* r = malloc(len + sizeof(char));
    memcpy(r, s + sizeof(short), len);
    r[len] = 0;
    return r;
}

// tests //
int main() {
    char* s;
    double d;
    int i;

    i = load_lua_lib("lua_udf.lua");
    printf("load_lua_lib: %d\n", i);

    s = from_varchar(to_varchar("seems ok!"));
    printf("from/to_varchar: %s\n", s);

    s = test_call_chain("some text");
    printf("test_call_chain: %s\n", s);

    s = from_varchar(test_varchar_conv(to_varchar("seems ok!")));
    printf("test_varchar_conv: %s\n", s);

    s = from_varchar(md5(to_varchar("some text")));
    printf("md5: %s\n", s);

    s = from_varchar(bin_to_hex(to_varchar("some text")));
    printf("bin_to_hex: %s\n", s);

    d = utf8_made_of(to_varchar("abcd"), to_varchar("abcdabcdacbabcdbacabcbadcbac"));
    printf("utf8_made_of: %d\n", (int)d);

    d = utf8_is_integer(to_varchar("0012301239"));
    printf("utf8_is_integer: %d\n", (int)d);

    s = from_varchar(sbc_replace_chars(to_varchar(" ;,:."), to_varchar("_"), to_varchar("words: w1,w2;w3.")));
    printf("sbc_replace_chars: %s\n", s);

    s = from_varchar(utf8_replace_chars(to_varchar(" ;,:."), to_varchar("_"), to_varchar("words: w1,w2;w3.")));
    printf("utf8_replace_chars: %s\n", s);

    s = from_varchar(utf8_replace_but_chars(to_varchar("abcdefghijklmnopqrstuvwxyz0123456789"), to_varchar(" "), to_varchar("words: w1,w2;www3www..ab")));
    printf("utf8_replace_but_chars: %s\n", s);

    i = file_is_readable(to_varchar("/bin/bash"));
    printf("file_is_readable: %d\n", i);

    printf("~END~\n");
    return 0;
}


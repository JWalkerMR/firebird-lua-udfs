#!/bin/lua

dofile("lua_udf.lua")

print("utf8_made_of: "..utf8_made_of('abcd', 'aaaabbbdddbcbdbbad'))
print("utf8_is_integer: "..utf8_is_integer('001092301230'))
print("sbc_replace_chars: "..sbc_replace_chars(' :,;.', '_', 'some words: w1; w2, w3'))
print("utf8_replace_chars: "..utf8_replace_chars(' :,;.', '_', 'some words: w1; w2, w3'))
print("utf8_replace_but_chars: "..utf8_replace_but_chars('abcdefghijklmnopqrstuvwxyz0123456789', ' ', 'some words: w1; w2, w3'))

-- testing the text functions
print("test: "..test('some text'))

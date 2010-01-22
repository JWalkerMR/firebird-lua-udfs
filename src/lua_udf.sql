declare external function LOAD_LUA_LIB
    cstring(200)
    returns integer by value
    entry_point 'load_lua_lib' module_name 'lua_udf';

declare external function MD5
    varchar(4096) character set UTF8 null
    returns varchar(16) character set OCTETS free_it
    entry_point 'md5' module_name 'lua_udf';

declare external function BIN_TO_HEX
    varchar(2048) character set OCTETS null
    returns varchar(4096) character set ASCII free_it
    entry_point 'bin_to_hex' module_name 'lua_udf';

declare external function ASCII_REPLACE_CHARS
    varchar(4096) character set ASCII null,
    varchar(4096) character set ASCII null,
    varchar(4096) character set ASCII null
    returns varchar(4096) character set ASCII free_it
    entry_point 'sbc_replace_chars' module_name 'lua_udf';

declare external function UTF8_REPLACE_CHARS
    varchar(4096) character set UTF8,
    varchar(4096) character set UTF8,
    varchar(4096) character set UTF8
    returns varchar(4096) character set UTF8 free_it
    entry_point 'utf8_replace_chars' module_name 'lua_udf';

declare external function UTF8_REPLACE_BUT_CHARS
    varchar(4096) character set UTF8,
    varchar(4096) character set UTF8,
    varchar(4096) character set UTF8
    returns varchar(4096) character set UTF8 free_it
    entry_point 'utf8_replace_but_chars' module_name 'lua_udf';

declare external function UTF8_MADE_OF
    varchar(4096) character set UTF8,
    varchar(4096) character set UTF8
    returns double precision by value
    entry_point 'utf8_made_of' module_name 'lua_udf';

declare external function UTF8_IS_INTEGER
    varchar(4096) character set UTF8
    returns double precision by value
    entry_point 'utf8_is_integer' module_name 'lua_udf';

declare external function FILE_IS_READABLE
    varchar(2048) character set OCTETS null
    returns integer by value
    entry_point 'file_is_readable' module_name 'lua_udf';



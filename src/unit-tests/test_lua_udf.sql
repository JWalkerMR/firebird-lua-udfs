select load_lua_lib('e:\cosmin_private\tools\firebird-2.5rc1\UDF\lua_udf.lua') from rdb$database;
select bin_to_hex(md5('lsadf;sdf;asdlfasdf')) from rdb$database;
select utf8_made_of('abcd', 'acabdcbacbdbcabdcabdc') from rdb$database;
select utf8_is_integer('001203491234098') from rdb$database;
select ascii_replace_chars(' ', '_', 'adkas ldkasldkas ldaks d') from rdb$database;
select utf8_replace_chars(' ', '_', 'adkas ldkasldkas ldaks d') from rdb$database;
select utf8_replace_but_chars('abcd', '!', 'adkas ldkasldkas ldaks d') from rdb$database;
select file_is_readable('c:\autoexec.bat') from rdb$database;


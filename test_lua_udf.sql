select lua_udf_reload_library() from rdb$database;
select bin_to_hex(md5('lsadf;sdf;asdlfasdf')) from rdb$database;
select utf8_made_of('abcd', 'acabdcbacbdbcabdcabdc') from rdb$database;
select utf8_is_integer('001203491234098') from rdb$database;
select ascii_replace_chars(' ', '_', 'adkas ldkasldkas ldaks d') from rdb$database;
select utf8_replace_chars(' ', '_', 'adkas ldkasldkas ldaks d') from rdb$database;
select utf8_replace_but_chars('abcd', '!', 'adkas ldkasldkas ldaks d') from rdb$database;
select file_is_readable('/bin/bash') from rdb$database;

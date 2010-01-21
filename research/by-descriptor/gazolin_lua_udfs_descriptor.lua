#!/bin/lua

local require_rocks = require "luarocks.require"
local md5 = require_rocks.require "md5"

local dtype_unknown	= 0
local dtype_text	= 1
local dtype_cstring	= 2
local dtype_varying	= 3
local dtype_packed	= 6
local dtype_byte	= 7
local dtype_short	= 8
local dtype_long	= 9
local dtype_quad	= 10
local dtype_real	= 11
local dtype_double	= 12
local dtype_d_float	= 13
local dtype_sql_date	= 14
local dtype_sql_time	= 15
local dtype_timestamp	= 16
local dtype_blob	= 17
local dtype_array	= 18
local dtype_int64	= 19

local DSC_TEXT_TYPE_NONE	= 0
local DSC_TEXT_TYPE_FIXED	= 1
local DSC_TEXT_TYPE_METADATA	= 2

local DSC_NUM_TYPE_NONE		= 0
local DSC_NUM_TYPE_NUMERIC	= 1
local DSC_NUM_TYPE_DECIMAL	= 2

local DSC_NULL			= 1
local DSC_NO_SUBTYPE		= 2
local DSC_NULLABLE		= 3

local function dsc2string(dsc)
    local dtype 	= dsc[0]
    local scale		= dsc[1]
    local length	= dsc[2]
    local subtype	= dsc[3]
    local flags		= dsc[4]
    
    if dtype = dtype_text then
	
end

local function my_md5(s)
    return md5.sum(s)
end

return { 
    md5 = my_md5
}



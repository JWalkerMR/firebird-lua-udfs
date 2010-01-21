#!/bin/lua

local function strfind(needle, haystack, start)
    return string.find(haystack, needle, start or 1, true)
end

function sbc_made_of(list, s)
    if list == nil or s == nil then
	return nil
    end
    
    for i = 1,#s do
	if not strfind(s:sub(i,i), list) then
	    return 0
	end
    end
    return 1
end

function sbc_replace_chars(find, replace, s, negate)
    if find == nil or replace == nil or s == nil then
	return nil
    end

    local t,k = {},1
    for i = 1,#s do
	if strfind(s:sub(i,i), find) then
	    if k < i then
		t[#t+1] = s:sub(k,i-1)..replace
	    end
	    k = i+1
	end
    end
    t[#t+1] = s:sub(k,#s)

    return table.concat(t, '')
end

function sbc_replace_but_chars(leave, replace, s)
    if leave == nil or replace == nil or s == nil then
	return nil
    end

    local t,k = {},1
    for i = 1,#s do
	if not strfind(s:sub(i,i), leave) then
	    if k < i then
		t[#t+1] = s:sub(k,i-1)..replace
	    end
	    k = i+1
	end
    end
    t[#t+1] = s:sub(k,#s)

    return table.concat(t, '')
end

function utf8_made_of(list, s)
    return sbc_made_of(list, s)
end

function utf8_is_integer(s)
    return utf8_made_of('0123456789', s)
end

function utf8_replace_chars(find, replace, s)
    return sbc_replace_chars(find, replace, s)
end

function utf8_replace_but_chars(leave, replace, s)
    return sbc_replace_but_chars(leave, replace, s)
end

-- testing
function test(s)
    return s..':'..s;
end


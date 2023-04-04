const std = @import("std");
const c = @cImport({
    @cDefine("_GNU_SOURCE", ""); // strcasestr
    @cInclude("string.h");
});

// complete

// XXX: most of these need separate implementations that don't use span

export fn trim(str: ?[*:0]u8) ?[*:0]u8 {
    if(str) |s| {
        const slice = std.mem.span(s);
        var trimmed = std.mem.trim(u8, slice, &std.ascii.whitespace);
        @constCast(trimmed.ptr)[trimmed.len] = 0;
        return @ptrCast([*:0]u8, @constCast(trimmed.ptr));
    } else return str;
}

export fn streq(a: ?[*:0]const u8, b: ?[*:0]const u8) c_int {
    if(a == b) return 1;
    if(a == null or b == null) return 0;

    return c.strcmp(a, b);
}

export fn streq_nocase(a: ?[*:0]const u8, b: ?[*:0]const u8) c_int {
    if(a == b) return 1;
    if(a == null or b == null) return 0;

    return if(comptime @hasDecl(c, "strcasecmp")) c.strcasecmp(a, b) else @compileError("stub");
}

export fn startsWith(haystack: ?[*:0]const u8, needle: ?[*:0]const u8) c_int {
    if(haystack == needle) return 1;
    if(haystack == null or needle == null) return 0;

    const h = std.mem.span(haystack.?);
    const n = std.mem.span(needle.?);

    return if(std.mem.startsWith(u8, h, n)) 1 else 0;
}

export fn startsWith_nocase(haystack: ?[*:0]const u8, needle: ?[*:0]const u8) c_int {
    if(haystack == needle) return 1;
    if(haystack == null or needle == null) return 0;

    const h = std.mem.span(haystack.?);
    const n = std.mem.span(needle.?);

    if(h.len <= n.len) return 0;

    return if(std.ascii.eqlIgnoreCase(n, h[0..n.len])) 1 else 0;
}

export fn endsWith(haystack: ?[*:0]const u8, needle: ?[*:0]const u8) c_int {
    if(haystack == needle) return 1;
    if(haystack == null or needle == null) return 0;

    const h = std.mem.span(haystack.?);
    const n = std.mem.span(needle.?);

    return if(std.mem.endsWith(u8, h, n)) 1 else 0;
}

export fn endsWith_nocase(haystack: ?[*:0]const u8, needle: ?[*:0]const u8) c_int {
    if(haystack == needle) return 1;
    if(haystack == null or needle == null) return 0;

    const h = std.mem.span(haystack.?);
    const n = std.mem.span(needle.?);

    if(h.len <= n.len) return 0;

    return if(std.ascii.eqlIgnoreCase(n, h[h.len - n.len..])) 1 else 0;
}

export fn contains(haystack: ?[*:0]const u8, needle: ?[*:0]const u8) c_int {
    if(haystack == needle) return 1;
    if(haystack == null or needle == null) return 0;

    return c.strstr(haystack, needle);
}

export fn contains_nocase(haystack: ?[*:0]const u8, needle: ?[*:0]const u8) c_int {
    if(haystack == needle) return 1;
    if(haystack == null or needle == null) return 0;

    return if(comptime @hasDecl(c, "strcasestr")) c.strcasestr(haystack, needle) else @compileError("stub");
}

export fn toLowerCase(str: ?[*:0]u8) ?[*:0]u8 {
    if(str) |s| {
        const sl = std.mem.span(s.?);
        std.ascii.lowerString(sl, sl);
    }
    return str;
}

export fn toUpperCase(str: ?[*:0]u8) ?[*:0]u8 {
    if(str) |s| {
        const sl = std.mem.span(s.?);
        std.ascii.upperString(sl, sl);
    }
    return str;
}

export fn strisunum(str: ?[*:0]u8) c_int {
    if(str) |s| {
        for(s) |ch| {
            switch(ch) {
                '0'...'9' => {},
                else => return 0,
            }
        }
        return 1;
    } else return 0;
}

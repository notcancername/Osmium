const std = @import("std");
const c = @cImport(@cInclude("network.h"));

export fn swapEndian(dou: *anyopaque, sz: usize) void {
	const bytes = @ptrCast([*]u8, dou);
    const half_sz = std.math.divExact(usize, sz, 2) catch {
        std.log.warn("size {d} passed to swapEndian not divisible by 2!", .{sz});
        unreachable;
    };
	for(0..half_sz) |i| {
        std.mem.swap(u8, &bytes[i], &bytes[sz - 1 - i]);
	}
}

fn getVarSize(in: anytype) usize {
    const nb_bytes = switch(@TypeOf(in)) {
        i32 => 5,
        i64 => 10,
        else => |T| @compileError("in (" ++ @typeName(T) ++ ") unsupported"),
    };
    const L2I = std.math.Log2Int(@TypeOf(in));

	for (1..nb_bytes) |x| {
		if(in >> @intCast(L2I, x * 7) == 0)
            return x;
    }

	return nb_bytes;
}

export fn getVarIntSize(in: i32) usize {return getVarSize(in);}
export fn getVarLongSize(in: i64) usize {return getVarSize(in);}

fn writeVar(_in: anytype, buf: [*]u8) c_int {
    var in = _in;

    if(comptime !std.meta.trait.isUnsignedInt(@TypeOf(in)))
        @compileError("in (" ++ @typeName(@TypeOf(in)) ++ ") not unsigned int");

    var i: usize = 0;
    while(in >> 7 != 0) : (i += 1) {
        if(in & 0x80 != 0) {
            buf[i] = @bitCast(u8, @truncate(u8, in)) | 0x80;
            in >>= 7;
        }
    }

    buf[i] = @intCast(u8, in);
    return @intCast(c_int, i + 1);
}

export fn writeVarInt(in: i32, buf: [*]u8) c_int {return writeVar(@bitCast(u32, in), buf);}
export fn writeVarLong(in: i64, buf: [*]u8) c_int {return writeVar(@bitCast(u64, in), buf);}

fn readVar(comptime T: type, buf: []u8) struct {out: T, nb_read: usize} {
    if(comptime !std.meta.trait.isIntegral(T))
        @compileError("T (" ++ @typeName(T) ++ ") not an integer type");

    var out: T = 0;
    var i: usize = 0;

    for(buf) |ch| {
        out <<= 7;
        out |= @truncate(u7, ch);

        const next = if(ch & 0x80 != 0) true else false;
        if (!next)
            break;

        i += 1;
    }

    return .{.out = out, .nb_read = i};
}

export fn readVarInt(out: *i32, buf: [*]u8, len: usize) c_int {
    const x = readVar(i32, buf[0..len]);
    out.* = x.out;
    return @intCast(c_int, x.nb_read);
}

export fn readVarLong(out: *i64, buf: [*]u8, len: usize) c_int {
    const x = readVar(i64, buf[0..len]);
    out.* = x.out;
    return @intCast(c_int, x.nb_read);
}

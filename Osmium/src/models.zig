const std = @import("std");
const c = @cImport({
    @cDefine("GL_GLEXT_PROTOTYPES", "");
    @cDefine("GL_VERSION_4_5", "");
    @cInclude("models.h");
    @cInclude("png.h");
    @cInclude("GL/gl.h");
    @cInclude("xstring.h");
    @cInclude("errno.h");
    @cInclude("dirent.h");
    @cInclude("math.h");
    @cInclude("globals.h");
    @cInclude("GL/glext.h");
});

const ally = @import("util.zig").allocator;

export fn loadTexturesPNG2(path: [*:0]u8, wrap: c_int, id: c_int, s: c_int, map: [*][*:0]u8, nb_maps: usize, smap: [*]c_int) c_int {
    // uuuuh, maybe it'll work?
    {
        var wid: c_int = undefined;
        var hig: c_int = undefined;
        return c.loadTexturesPNG(path, wrap, &wid, &hig, id, s, @ptrCast([*c][*c]u8, map), @intCast(c_int, nb_maps), smap);
    }
    var a_tally = std.heap.ArenaAllocator.init(ally);
    defer a_tally.deinit();
    const tally = a_tally.allocator();

    const sl_path = std.mem.span(path);

	var rw: c_int = 0;
	var rh: c_int = 0;
	var mo: c_int = 0;

	c.glBindTexture(c.GL_TEXTURE_2D_ARRAY, @intCast(c_uint, id));
	c.glPixelStorei(c.GL_UNPACK_ALIGNMENT, 1);
	c.glTexParameteri(c.GL_TEXTURE_2D_ARRAY, c.GL_TEXTURE_WRAP_S, c.GL_REPEAT);
	c.glTexParameteri(c.GL_TEXTURE_2D_ARRAY, c.GL_TEXTURE_WRAP_T, c.GL_REPEAT);
	c.glTexParameteri(c.GL_TEXTURE_2D_ARRAY, c.GL_TEXTURE_MAG_FILTER, if(s != 0) c.GL_NEAREST else c.GL_LINEAR);
	c.glTexParameteri(c.GL_TEXTURE_2D_ARRAY, c.GL_TEXTURE_MIN_FILTER, c.GL_LINEAR);
    // #ifdef c.GL_TEXTURE_MAX_ANISOTROPY_EXT
	//     c.glTexParameterf(c.GL_TEXTURE_2D_ARRAY, c.GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0);
    // #endif
	c.glTexEnvf(c.GL_TEXTURE_ENV, c.GL_TEXTURE_ENV_MODE, c.GL_MODULATE);
	c.glTexStorage3D(c.GL_TEXTURE_2D_ARRAY, 3, c.GL_RGBA8, c.width, c.height, @intCast(c_int, nb_maps));
	//c.glTexImage2D(c.GL_TEXTURE_2D, 0, c.GL_RGBA, width, height, 0, c.GL_RGBA, c.GL_UNSIGNED_BYTE, data);

	for(map, 0..nb_maps) |me, mi| {
        const sl_me = std.mem.span(me);
	    const cx = tally.allocSentinel(u8, sl_path.len + sl_me.len, 0) catch return -1;
        defer tally.free(cx);

        std.mem.copy(u8, cx, sl_path);
        std.mem.copy(u8, cx[sl_path.len..], sl_me);

		const fd = @ptrCast(?*c.FILE, c.fopen(cx, "rb")) orelse return -1;
        defer _ = c.fclose(fd);

		var png = @as(?*c.png_struct, c.png_create_read_struct(c.PNG_LIBPNG_VER_STRING, null, null, null));
        var info = @as(?*c.png_info, c.png_create_info_struct(png));
		defer c.png_destroy_read_struct(&png, &info, null);
        if(png == null or info == null) return -1;

		c.png_init_io(png, fd);
		c.png_read_info(png, info);
		const width = c.png_get_image_width(png, info);

		if(rw == 0)
            rw = @intCast(c_int, width) + (2 * c.TEXTURE_BUFFER);

        const height = c.png_get_image_height(png, info);
		if(rh == 0) rh = @intCast(c_int, height) + (2 * c.TEXTURE_BUFFER);
		const color_type = c.png_get_color_type(png, info);
		const bit_depth = c.png_get_bit_depth(png, info);

		if(bit_depth == 16)
            c.png_set_strip_16(png);

        if(color_type == c.PNG_COLOR_TYPE_PALETTE)
            c.png_set_palette_to_rgb(png);
		if(color_type == c.PNG_COLOR_TYPE_GRAY and bit_depth < 8)
            c.png_set_expand_gray_1_2_4_to_8(png);
		if(c.png_get_valid(png, info, c.PNG_INFO_tRNS) != 0)
            c.png_set_tRNS_to_alpha(png);
		if(color_type == c.PNG_COLOR_TYPE_RGB or color_type == c.PNG_COLOR_TYPE_GRAY or color_type == c.PNG_COLOR_TYPE_PALETTE)
            c.png_set_filler(png, 0xFF, c.PNG_FILLER_AFTER);
		if(color_type == c.PNG_COLOR_TYPE_GRAY or color_type == c.PNG_COLOR_TYPE_GRAY_ALPHA)
            c.png_set_gray_to_rgb(png);

		c.png_read_update_info(png, info);
		smap[mi] = mo;

		const row_pointers = tally.alloc(*anyopaque, height) catch unreachable;
        defer tally.free(row_pointers);

		const bry: c_int = 0;
		const imgs = tally.alloc(*anyopaque, height / @intCast(c_uint, rh) + 1) catch unreachable;
        defer tally.free(imgs);


        std.debug.print("{s} {} {} {}\n", .{me, mi, height, rh});

		for(imgs) |*img| {
			img.* = (ally.alloc(u8, @intCast(usize, rw * rh * 4)) catch unreachable).ptr;
		}

        // XXX: THIS IS BROKEN
        // (but I didn't break it, they did, and now I at least have good errors)
		for(row_pointers, 0..) |*rp, y| {
			rp.* = @ptrCast([*]u8, imgs[y / 16]) + ((y % 16) * @intCast(usize, rw));
		}

		c.png_read_image(png, @ptrCast([*c][*c]u8, row_pointers.ptr));

		if(
            std.mem.eql(u8, sl_me, "grass_top.png")
                or std.mem.eql(u8, sl_me, "fern.png")
                or std.mem.eql(u8, sl_me, "tallgrass.png")
                or std.mem.startsWith(u8, sl_me, "double_plant_grass")
                or std.mem.startsWith(u8, sl_me, "double_plant_fern")
                or std.mem.startsWith(u8, sl_me, "leaves_")
        ) { // TODO: implement dynamic textures better than this
			for (0..bry) |y| {
				const pix = @ptrCast([*]u32, row_pointers[y]);
				for (0..rw) |x| {
					const cc = (pix[x] & 0xFF);
                    const cc_f = @intToFloat(f32, cc);
					var r = @floatToInt(i32, 71  * (cc_f / 255));
				    var g = @floatToInt(i32, 205 * (cc_f / 255));
					var b = @floatToInt(i32, 51  * (cc_f / 255));

					if (r > 255 or g > 255 or b > 255) {
						const total = r + g + b;
						const h = @max(r, @max(g, b));

						if (total < 765) {
							const m = (765 - total) / (3 * h - total);
							_ = 255 - m * h;
							r = g + m * r;
							g = g + m * g;
							b = g + m * b;
						} else {
							r = 255;
							g = 255;
							b = 255;
						}
					}
					if (r < 0) r = 0;
					if (g < 0) g = 0;
					if (b < 0) b = 0;
					pix[x] = @intCast(u8, r) | (@intCast(u16, g) << 8) | (@intCast(u32, b) << 16) | (pix[x] & 0xFF000000);
				}
			}
		}
        // What are we trying to do with the data here? I don't know, and the author certainly didn't!
    }
	return 0;
}

export fn loadTextureData(id: c_int, width: usize, height: usize, data: *anyopaque, s: c_int) void {
	c.glBindTexture(c.GL_TEXTURE_2D, @intCast(c_uint, id));
	c.glPixelStorei(c.GL_UNPACK_ALIGNMENT, 1);
	c.glTexParameteri(c.GL_TEXTURE_2D, c.GL_TEXTURE_WRAP_S, c.GL_REPEAT);
	c.glTexParameteri(c.GL_TEXTURE_2D, c.GL_TEXTURE_WRAP_T, c.GL_REPEAT);
	c.glTexParameteri(c.GL_TEXTURE_2D, c.GL_TEXTURE_MAG_FILTER, if(s != 0) c.GL_NEAREST else c.GL_LINEAR);
	c.glTexParameteri(c.GL_TEXTURE_2D, c.GL_TEXTURE_MIN_FILTER, c.GL_LINEAR);
	if(comptime @hasDecl(c, "GL_TEXTURE_MAX_ANISOTROPY_EXT"))
        c.glTexParameterf(c.GL_TEXTURE_2D, c.GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0);
	c.glTexEnvf(c.GL_TEXTURE_ENV, c.GL_TEXTURE_ENV_MODE, c.GL_MODULATE);
	c.glTexImage2D(c.GL_TEXTURE_2D, 0, c.GL_RGBA, @intCast(c_int, width), @intCast(c_int, height), 0, c.GL_RGBA, c.GL_UNSIGNED_BYTE, data);
}

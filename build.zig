const std = @import("std");

fn makeCObjects(b: *std.Build, comptime c_sources: anytype, target: anytype, optimize: anytype, exe: anytype) void {
    inline for(c_sources) |source| {
        const obj = b.addObject(.{
            .name = source,
            .target = target,
            .optimize = optimize,
        });
        obj.linkLibC();
        obj.addCSourceFile("Osmium/src/" ++ source, &.{"-Wall", "-Wvla"});
        exe.addObject(obj);
    }
}

fn makeZigObjects(b: *std.Build, comptime sources: anytype, target: anytype, optimize: anytype, exe: anytype) void {
    inline for(sources) |source| {
        const obj = b.addObject(.{
            .name = source,
            .target = target,
            .optimize = optimize,
            .root_source_file = .{.path = "Osmium/src/" ++ source},
        });
        obj.linkLibC();
        obj.addIncludePath("Osmium/src");
        exe.addObject(obj);
    }
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "osmium",
        .target = target,
        .optimize = optimize,
    });

    exe.disable_sanitize_c = false;

    const libs = .{
        "gl",
        "glu",
        "glut",
        "glfw",
        "png",
        "z",
    };

    inline for(libs) |lib| exe.linkSystemLibrary(lib);

    exe.linkLibC();

    // XXX: add libraries to link

    const c_sources = .{
        "block.c",
        "bmodel.c",
        "entity.c",
        "gui.c",
        "ingame.c",
        "inventory.c",
        "main.c",
        "models.c",
        "nbt.c",
        "network.c",
        "render.c",
        "world.c",
        "json.c",
        "globals.c",
    };

    const zig_sources = .{
        "xstring.zig",
        "network.zig",
        "models.zig",
    };

    makeCObjects(b, c_sources, target, optimize, exe);
    makeZigObjects(b, zig_sources, target, optimize, exe);

    exe.install();
}

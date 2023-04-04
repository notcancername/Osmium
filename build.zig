const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "osmium",
        .target = target,
        .optimize = optimize,
    });

    exe.addIncludePath("./Osmium");
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
    };

    const zig_sources = .{
        "xstring.zig",
    };

    inline for(c_sources) |source| exe.addCSourceFile("Osmium/src/" ++ source, &.{});
    inline for(zig_sources) |source| exe.addObjectFileSource(.{.path = "Osmium/src/" ++ source});

    exe.install();
}

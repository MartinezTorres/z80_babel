const std = @import("std");
/// Zig version. When writing code that supports multiple versions of Zig, prefer
/// feature detection (i.e. with `@hasDecl` or `@hasField`) over version checks.
pub const zig_version = std.SemanticVersion.parse("0.9.0") catch unreachable;
/// Temporary until self-hosted is feature complete.
pub const zig_is_stage2 = true;
/// Temporary until self-hosted supports the `cpu.arch` value.
pub const stage2_arch: std.Target.Cpu.Arch = .avr;
/// Temporary until self-hosted can call `std.Target.x86.featureSetHas` at comptime.
pub const stage2_x86_cx16 = false;

pub const output_mode = std.builtin.OutputMode.Obj;
pub const link_mode = std.builtin.LinkMode.Static;
pub const is_test = false;
pub const single_threaded = false;
pub const abi = std.Target.Abi.eabi;
pub const cpu: std.Target.Cpu = .{
    .arch = .avr,
    .model = &std.Target.avr.cpu.avr2,
    .features = std.Target.avr.featureSet(&[_]std.Target.avr.Feature{
        .addsubiw,
        .avr0,
        .avr1,
        .avr2,
        .ijmpcall,
        .lpm,
        .memmappedregs,
        .sram,
    }),
};
pub const os = std.Target.Os{
    .tag = .freestanding,
    .version_range = .{ .none = {} }
};
pub const target = std.Target{
    .cpu = cpu,
    .os = os,
    .abi = abi,
};
pub const object_format = std.Target.ObjectFormat.elf;
pub const mode = std.builtin.Mode.ReleaseSmall;
pub const link_libc = false;
pub const link_libcpp = false;
pub const have_error_return_tracing = false;
pub const valgrind_support = false;
pub const position_independent_code = false;
pub const position_independent_executable = false;
pub const strip_debug_info = false;
pub const code_model = std.builtin.CodeModel.default;

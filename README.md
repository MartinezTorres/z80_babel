# z80 Babel: 
# C, C++, D, Fortran, Rust and Zig for your z80

This is a proof of concept for a multi-language pipeline for the Z80 CPU, 
and its corresponding test and benchmark tool coded for MSX.

Most surprisingly, it IS possible to use C++, D, Fortran, Rust or Zig to generate Z80 code, 
and even more surprisingly, these have competitive performance (except for Fortran, but maybe we can live with that). 
Support for their respective standard libraries is somewhat limited (a.k.a inexistent).

### Compiling to Z80

We leverage the [LLVM Project](https://github.com/llvm/llvm-project). 
The LLVM Project is a collection of tools to create highly optimized compilers. 
LLVM *front-ends* turn source code from different languages into a common intermediate representation (llvm-ir), 
while LLVM *back-ends* turn this intermediate code into machine code for the desired target. 
This architecture allows LLVM to support a large number of programming languages, as well as a large number of target architectures.
Sadly, Z80 is not yet a natively supported architecture, albeit there are efforts to add Z80 support
[[1](https://github.com/jacobly0/llvm-project),[2](https://github.com/AHelper/llvm-z80-target)].

C++, Rust, D, Zig and Fortran, among others, have compilers based on the llvm project that can generate *llvm-ir*.

One of the original back-ends for LLVM was the C back-end, that generated C code from any of the sources.
This back-end became obsolete long ago and its support was abandoned, 
there have been several attempts to resurrect the C back-end over the years, 
but the most successful one is the [llvm-cbe](https://github.com/JuliaComputingOSS/llvm-cbe) project by Julia Computing, 
which is robust and supports modern llvm versions.

By using the C back-end, we can compile most of the LLVM supported languages to C. 
The last step of the chain is to compile C to native Z80 assembly. 
We use [SDCC]([llvm-cbe](https://github.com/JuliaComputingOSS/llvm-cbe)) to perform this step.

So, our pipeline goes from the source language to *llvm-ir*, then to C, and finally to assembly. 

We had to solve a few issues though. The *llvm-ir* is not completely target independent.
In particular, pointer size, alignment, and bit endianness will affect the *llvm-ir*.
Luckily, LLVM supports natively the AVR architecture, which is 8 bit, has 16 bit pointers, 
and is generally treated as little endian, just as our beloved Z80.
This means that the *llvm-ir* generated when the AVR architecture is selected, 
will be largely compatible with Z80.

Other than that, the C files that *llvm-cbe* use custom attributes for MSC and GNUC that are not compatible with SDCC.
Also, some front-ends generate *llvm-ir* code that is not well recognized by the *llvm-cbe*, so we had to mangle these too.

Here we document the steps needed to compile any of the source languages to Z80 asm, as well as the dependencies required.

### Test and Benchmark Tool

The code in this repository contains a *test and benchmark* program for the only Z80-based platform is it worth to use, the MSX.
This program is meant to test if the aforementioned pipelines **work**, check its competitiveness in terms of **size** and **speed**.

#### Organization

The code is split between the `src` directory, which contains the benchmark tool itself, 
and the `tests` directory which contains the code and description of the tests to execute.
The benchmark tool is written mostly in C, and the test functions are linked together. 
We use [megalinker](https://github.com/MartinezTorres/megalinker) generates a ROM using an ASCII8 based mapper that can be flashed
and executed in any specification compliant MSX. 

#### Test execution

To generate the ROM, one can use `make rom`. To generate the ROM and test it on OpenMSX, use `make {msx1, msx1jp, msx2, msx2jp, msx2+, msxtr}`.
You need to ensure that you have both [OpenMSX](https://openmsx.org/) and the BIOS of any of these machinesm e.g., [C Bios](http://cbios.sourceforge.net/).
The Makefile runs the MSX at 50x of its original speed to speed-up the tests.

For every *test case*, it's name is colored in *green* if its execution is verified to be successful, or *red* if the output is not the expected one.
Then the test is performed 10 times and the average delay is reported, as well as the size of the tested function.

Use the left and right arrow keys to navigate between tests. Use the [s] and [d] keys to switch between sorting by *delay* or sorting by *size*.

#### Quirks

The makefile compiles each test file using different optimization options for the SDCC.
For the `--max-allocs-per-node` it tests values between 1000 (1k) to 50000 (50k), being 1k the least optimized to 50k the most.
It also tests the use of [MDL](https://github.com/santiontanon/mdlz80optimizer), which is a Z80 code optimizer by Santiago Ontañon.

To link together different versions of the same file, we mangle the symbol names in the object files between linking them together.

Also, to find the size of a function, we add a phony *end* function immediately after the origial one.

## All Requisites:
### SDCC (version >= 4.1.12)
### llvm-cbe
### clang, ldmd2, flang-7
### rust
### zig
### MDL
### Megalinker
### Openmsx

## Compilation instructions:

### C++ to LLVM IR
```
clang -S -emit-llvm -Os -target avr -Wno-avr-rtlib-linking-quirks -Wall -Wextra  {FILE}.cc -o {FILE}.ll
```

### D to LLVM IR
```
ldmd2  -mtriple=avr-unknown-unknown -O -betterC -output-ll {FILE}.d -of {FILE}.ll
```

### Rust to LLVM IR
```
rustc --emit=llvm-ir -C opt-level=3 -C embed-bitcode=no --target avr-unknown-gnu-atmega328 -Cpanic=abort -L dependency=ext/rust_deps --extern 'noprelude:compiler_builtins=ext/rust_deps/libcompiler_builtins-4b0354a1ee99278a.rlib'  --extern 'noprelude:core=ext/rust_deps/libcore-c1e4c798d948b121.rlib'  -Z unstable-options {FILE}.rs -o {FILE}.ll
```

### Zig to LLVM IR
```
ext/zig-linux-x86_64-0.9.0/zig build-obj -fno-stage1 -fLLVM -O ReleaseSmall --cache-dir /tmp/zig-cache -target avr-freestanding-eabi -femit-llvm-ir=tmp/tests/sieve_zig.ll tests/sieve_zig.zig
sed '/attributes \#/d' -i tmp/tests/sieve_zig.ll
```

### Fortran to LLVM IR
```
flang-7 -Mextend -S -O3 -emit-llvm tests/sieve_f.f -o tmp/tests/sieve_f.ll
```

### LLVM IR to Z80 ASM
```
ext/llvm-cbe/build/tools/llvm-cbe/llvm-cbe --cbe-declare-locals-late {FILE}.ll -o {FILE}.c

sed 's/static __forceinline/inline/g' -i {FILE}.c

sed 's/uint8_t\* memset(uint8_t\*, uint32_t, uint16_t);/inline uint8_t\* memset(uint8_t\* dst, uint8_t c, uint16_t sz) {uint8_t \*p = dst; while (sz--) *p++ = c; return dst; }/g' -i {FILE}.c

sed '/__noreturn void rust_begin_unwind(struct l_struct_core_KD__KD_panic_KD__KD_PanicInfo\* llvm_cbe_info)/{:a;N;/__builtin_unreachable/{N;N;d};/  }/b;ba}' -i {FILE}.c

ext/sdcc-4.1.14/bin/sdcc -S -Iinc -Isrc -Itests \
    --std-sdcc11 -mz80 --out-fmt-ihx \
    --disable-warning 110 --disable-warning 126 \
    --max-allocs-per-node 2000 --allow-unsafe-read --opt-code-speed \
    --no-std-crt0 --nostdlib --no-xinit-opt \
    -Iext/sdcc-4.1.14/device/include \
    -D__HIDDEN__= -D__attribute__\(a\)=  -D__builtin_unreachable\(\)=while\(1\)\; \
    {FILE}.c -o {FILE}.asm
```

## Current Benchmarks
The only implemented benchmark currently is the sieve of Eratosthenes. The implemented algorithm is naïve, and it has the same complexity in all languages.
C, C++, and D implement three closely related versions of the algorithm (v1, v2, v3). The "1k"..."50k" indicate the number of allocations allowed for SDCC, the number of allocations controls the optimization level for SDCC, with more allocations generally corresponding to more optimized code. The code coming from LLVM tends to leverage better high optimization levels. 

![](img/1_50k_1.png)
![](img/2_1k_1.png)
![](img/3_50k_2.png)
![](img/4_1k_2.png)
![](img/5_C_v1.png)
![](img/6_C_v3.png)
![](img/7_C++_v1.png)
![](img/8_C++_v3.png)
![](img/9_D_v1.png)
![](img/10_D_v3.png)
![](img/11_RUST.png)
![](img/12_ZIG.png)

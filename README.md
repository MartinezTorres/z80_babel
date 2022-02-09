# z80 Babel: 
# C, C++, D, Fortran, Rust and Zig for your z80

This is a proof of concept for a multi-language pipeline for the Z80 CPU, and its corresponding test and benchmark tool coded for MSX.

Most surprisingly, it IS possible to use C++, D, Fortran, Rust or Zig to generate Z80 code, and even more surprisingly, these have competitive performance (except for Fortran, but maybe we can live with that). Support for their respective standard libraries is somewhat limited (a.k.a inexistent).

We leverage the [LLVM Project](https://github.com/llvm/llvm-project). 
The LLVM Project is a collection of tools to create highly optimized compilers. 
LLVM front-ends turn source code from different languages into an intermediate representation (llvm-ir), 
while LLVM back-ends turn this intermediate code into machine code for the desired target. 
This architecture allows LLVM to support a large number of languages, and also a large number of target architectures.
Sadly, Z80 is not yet a natively supported architecture, albeit there are efforts to add Z80 support [[1](https://github.com/jacobly0/llvm-project),[2](https://github.com/AHelper/llvm-z80-target)].


C++, Rust, D, Zig and Fortran have compilers based on the llvm project.  

To compile C we use SDCC. To compile C++, Rust, D, Zig or Fortran, we use the llvm-cbe backend to generate a C file rom the llvm intermediate representation, and we compile this C file to Z80 assembly using SDCC. The key that makes this possible is using the AVR target for the llmv frontends. I could not get Fortran to accept the AVR target, and thus it incurrs on a large performance penalty.

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

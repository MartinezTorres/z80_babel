NAME := z80_babel

.PHONY: all clean
.SECONDARY:  

all: rom 

##########################################################
### BINARY DEPENDENCIES AND FLAGS

# SED
SED = sed

# SDCC (for some includes to work, it needs an absolute path)
SDCC = ext/sdcc-4.1.14

CCZ80 = $(SDCC)/bin/sdcc
MAX_ALLOCS = 2000

CCZ80FLAGS = --std-sdcc11 -mz80 --out-fmt-ihx
CCZ80FLAGS += --disable-warning 110 --disable-warning 126 
CCZ80FLAGS += --max-allocs-per-node $(MAX_ALLOCS) --allow-unsafe-read --opt-code-speed 
CCZ80FLAGS += --no-std-crt0 --nostdlib --no-xinit-opt
CCZ80FLAGS += -I$(SDCC)/device/include
CCZ80FLAGS += -D__HIDDEN__= -D__attribute__\(a\)= 
CCZ80FLAGS += -D__builtin_unreachable\(\)=while\(1\)\; 

# ASM
ASM = $(SDCC)/bin/sdasz80
ASM_FLAGS = -ogslp

# MDL
MDL = ext/mdl.jar
MDL_FLAGS = -dialect sdcc -ro -po speed -ro -po speed -ro -asm-dialect

#LLVM_C BACKEND
LLVM_CBE = ext/llvm-cbe/build/tools/llvm-cbe/llvm-cbe 
LLVM_CBE_FLAGS = --cbe-declare-locals-late

#CLANG
CLANG = clang
CLANG_FLAGS = -S -emit-llvm -Os -target avr -Wno-avr-rtlib-linking-quirks -Wall -Wextra 

#DLANG
DLANG = ldmd2 
DLANG_FLAGS = -mtriple=avr-unknown-unknown -O -betterC -output-ll 

#FORTRAN
FORTRAN = flang-7
FORTRAN_FLAGS =  -Mextend -S -O3 -emit-llvm

#RUST
RUST = rustc
RUST_FLAGS = --emit=llvm-ir -C opt-level=3 -C embed-bitcode=no --target avr-unknown-gnu-atmega328 -Cpanic=abort
RUST_FLAGS += -L dependency=ext/rust_deps 
RUST_FLAGS += --extern 'noprelude:compiler_builtins=ext/rust_deps/libcompiler_builtins-4b0354a1ee99278a.rlib' 
RUST_FLAGS += --extern 'noprelude:core=ext/rust_deps/libcore-c1e4c798d948b121.rlib' 
RUST_FLAGS += -Z unstable-options 

#ZIG
ZIG = ext/zig-linux-x86_64-0.9.0/zig
ZIG_FLAGS = build-obj -fno-stage1 -fLLVM -O ReleaseSmall --cache-dir /tmp/zig-cache -target avr-freestanding-eabi  

# LINKER
MEGALINKER = ext/megalinker/megalinker

# OPENMSX
OPENMSX_PARAM = -command "set speed 5000"
OPENMSX_BIN = openmsx
OPENMSX_DEF = $(OPENMSX_BIN)                            $(OPENMSX_PARAM) -carta 
OPENMSX1    = $(OPENMSX_BIN) -machine Philips_VG_8020   $(OPENMSX_PARAM) -carta 
OPENMSX1_JP = $(OPENMSX_BIN) -machine C-BIOS_MSX1_JP    $(OPENMSX_PARAM) -carta 
OPENMSX2    = $(OPENMSX_BIN) -machine C-BIOS_MSX2       $(OPENMSX_PARAM) -carta 
OPENMSX2P   = $(OPENMSX_BIN) -machine C-BIOS_MSX2+_JP   $(OPENMSX_PARAM) -carta 
OPENMSXTR   = $(OPENMSX_BIN) -machine Panasonic_FS-A1GT $(OPENMSX_PARAM) -carta 

MSG = "\033[1;32m[$(@)]\033[1;31m\033[0m"


##########################################################
### COLLECT SOURCES TEST PROGRAM

#recursive wildcard
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

INCLUDES        += -Iinc -Isrc
HEADERS         += $(call rwildcard, src/ inc/, *.h) 

SOURCES_C       += $(call rwildcard, src/, *.c)
SOURCES_S       += $(call rwildcard, src/, *.s) 
SOURCES_ASM     += $(call rwildcard, src/, *.asm) 

SOURCES_CPP     += $(call rwildcard, src/, *.cpp)
SOURCES_CC      += $(call rwildcard, src/, *.cc)
SOURCES_FORTRAN += $(call rwildcard, src/, *.f)
SOURCES_DLANG   += $(call rwildcard, src/, *.d)
SOURCES_RUST    += $(call rwildcard, src/, *.rs)
SOURCES_ZIG     += $(call rwildcard, src/, *.zig)

##########################################################
### CREATE OBJECT FILES
OBJ    += $(addprefix tmp/,$(SOURCES_C:.c=.rel))
OBJ    += $(addprefix tmp/,$(SOURCES_S:.s=.rel))
OBJ    += $(addprefix tmp/,$(SOURCES_ASM:.asm=.rel))

OBJ    += $(addprefix tmp/,$(SOURCES_CPP:.cpp=.rel))
OBJ    += $(addprefix tmp/,$(SOURCES_CC:.cc=.rel))
OBJ    += $(addprefix tmp/,$(SOURCES_FORTRAN:.f=.rel))
OBJ    += $(addprefix tmp/,$(SOURCES_DLANG:.d=.rel))
OBJ    += $(addprefix tmp/,$(SOURCES_RUST:.rs=.rel))
OBJ    += $(addprefix tmp/,$(SOURCES_ZIG:.zig=.rel))

##########################################################
### COLLECT TESTSMARKS

INCLUDES              += -Itests
#HEADERS               += $(call rwildcard, tests/, *.h) 

TESTS_SOURCES_C       += $(call rwildcard, tests/, *.c)
TESTS_SOURCES_S       += $(call rwildcard, tests/, *.s) 
TESTS_SOURCES_ASM     += $(call rwildcard, tests/, *.asm) 

TESTS_SOURCES_CPP     += $(call rwildcard, tests/, *.cpp)
TESTS_SOURCES_CC      += $(call rwildcard, tests/, *.cc)
TESTS_SOURCES_FORTRAN += $(call rwildcard, tests/, *.f)
TESTS_SOURCES_DLANG   += $(call rwildcard, tests/, *.d)
TESTS_SOURCES_RUST    += $(call rwildcard, tests/, *.rs)
TESTS_SOURCES_ZIG     += $(call rwildcard, tests/, *.zig)

ALLOCS := 1k 2k 5k 10k 20k 50k 1k.mdl.ro 2k.mdl.ro 5k.mdl.ro 10k.mdl.ro 20k.mdl.ro 50k.mdl.ro

OBJ    += $(foreach ALLOC, $(ALLOCS), $(addprefix tmp/,$(TESTS_SOURCES_C:.c=.$(ALLOC).rel)))
OBJ    += $(foreach ALLOC, $(ALLOCS), $(addprefix tmp/,$(TESTS_SOURCES_S:.s=.$(ALLOC).rel)))
OBJ    += $(foreach ALLOC, $(ALLOCS), $(addprefix tmp/,$(TESTS_SOURCES_ASM:.asm=.$(ALLOC).rel)))

OBJ    += $(foreach ALLOC, $(ALLOCS), $(addprefix tmp/,$(TESTS_SOURCES_CPP:.cpp=.$(ALLOC).rel)))
OBJ    += $(foreach ALLOC, $(ALLOCS), $(addprefix tmp/,$(TESTS_SOURCES_CC:.cc=.$(ALLOC).rel)))
OBJ    += $(foreach ALLOC, $(ALLOCS), $(addprefix tmp/,$(TESTS_SOURCES_FORTRAN:.f=.$(ALLOC).rel)))
OBJ    += $(foreach ALLOC, $(ALLOCS), $(addprefix tmp/,$(TESTS_SOURCES_DLANG:.d=.$(ALLOC).rel)))
OBJ    += $(foreach ALLOC, $(ALLOCS), $(addprefix tmp/,$(TESTS_SOURCES_RUST:.rs=.$(ALLOC).rel)))
OBJ    += $(foreach ALLOC, $(ALLOCS), $(addprefix tmp/,$(TESTS_SOURCES_ZIG:.zig=.$(ALLOC).rel)))

#$(info $$OBJ is [${OBJ}])


###### SDCC NATIVE: ASM
tmp/%.rel: %.s $(HEADERS) 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(ASM) $(ASM_FLAGS) $@ $<
	@echo " "`grep "size" tmp/$*.sym | awk 'strtonum("0x"$$4) {print $$2": "strtonum("0x"$$4)" bytes"}'` 

tmp/%.rel: %.asm $(HEADERS) 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(ASM) $(ASM_FLAGS) $@ $<
	@echo " "`grep "size" tmp/$*.sym | awk 'strtonum("0x"$$4) {print $$2": "strtonum("0x"$$4)" bytes"}'` 

###### SDCC NATIVE: C
tmp/%.c: %.c $(HEADERS)
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(CLANG) $(CLANG_FLAGS) $(INCLUDES) $< -o $@.clang
	@cp $< $@
	@#$(CCZ80) -c $(INCLUDES) $(CCZ80FLAGS) $< -o $@
	@echo 


###### LLVM COMMON PIPELINE:
tmp/%.cbe.c: tmp/%.ll
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(LLVM_CBE) --cbe-declare-locals-late $< -o $@
	@echo 
	
tmp/%.c: tmp/%.cbe.c
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(SED) 's/static __forceinline/inline/g' $< > $@
	@$(SED) 's/uint8_t\* memset(uint8_t\*, uint32_t, uint16_t);/inline uint8_t\* memset(uint8_t\* dst, uint8_t c, uint16_t sz) {uint8_t \*p = dst; while (sz--) *p++ = c; return dst; }/g' -i $@
	@$(SED) '/__noreturn void rust_begin_unwind(struct l_struct_core_KD__KD_panic_KD__KD_PanicInfo\* llvm_cbe_info)/{:a;N;/__builtin_unreachable/{N;N;d};/  }/b;ba}' -i $@
	@echo 

tmp/%.1k.asm: tmp/%.c 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(eval ALLOCS_TMP := $(shell echo $@ | egrep -o "\.[0-9]*k\." | tr -d ".k")000 )
	@$(CCZ80) -S $(INCLUDES) $(CCZ80FLAGS) --max-allocs-per-node $(ALLOCS_TMP) $< -o $@
	@echo 

tmp/%.2k.asm: tmp/%.c 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(eval ALLOCS_TMP := $(shell echo $@ | egrep -o "\.[0-9]*k\." | tr -d ".k")000 )
	@$(CCZ80) -S $(INCLUDES) $(CCZ80FLAGS) --max-allocs-per-node $(ALLOCS_TMP) $< -o $@
	@echo 

tmp/%.5k.asm: tmp/%.c 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(eval ALLOCS_TMP := $(shell echo $@ | egrep -o "\.[0-9]*k\." | tr -d ".k")000 )
	@$(CCZ80) -S $(INCLUDES) $(CCZ80FLAGS) --max-allocs-per-node $(ALLOCS_TMP) $< -o $@
	@echo 

tmp/%.10k.asm: tmp/%.c 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(eval ALLOCS_TMP := $(shell echo $@ | egrep -o "\.[0-9]*k\." | tr -d ".k")000 )
	@$(CCZ80) -S $(INCLUDES) $(CCZ80FLAGS) --max-allocs-per-node $(ALLOCS_TMP) $< -o $@
	@echo 

tmp/%.20k.asm: tmp/%.c 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(eval ALLOCS_TMP := $(shell echo $@ | egrep -o "\.[0-9]*k\." | tr -d ".k")000 )
	@$(CCZ80) -S $(INCLUDES) $(CCZ80FLAGS) --max-allocs-per-node $(ALLOCS_TMP) $< -o $@
	@echo 

tmp/%.50k.asm: tmp/%.c 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(eval ALLOCS_TMP := $(shell echo $@ | egrep -o "\.[0-9]*k\." | tr -d ".k")000 )
	@$(CCZ80) -S $(INCLUDES) $(CCZ80FLAGS) --max-allocs-per-node $(ALLOCS_TMP) $< -o $@
	@echo 

tmp/%.asm: tmp/%.c 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(CCZ80) -S $(INCLUDES) $(CCZ80FLAGS) $< -o $@
	@echo 

tmp/%.rel: tmp/%.asm
	@echo -n $(MSG)
	@mkdir -p $(@D)q
	@$(ASM) $(ASM_FLAGS) $@ $<
	
	@$(eval AK := $(shell echo $@ | egrep -o "\.[0-9]*k\." | tr -d ".k"))
	@$(eval A_SUFFIX := $(if $(AK), _$(AK)k, ))
	@$(SED) '/^M/ s/$$/$(A_SUFFIX)/' -i $@
	@$(SED) '/^S/ s/ Def/$(A_SUFFIX) Def/' -i $@

	@$(eval MDL_RO := $(shell echo $@ | egrep -o "\.mdl.ro\."))
	@$(eval MDL_RO_SUFFIX := $(if $(MDL_RO), _mdl_ro, ))
	@$(SED) '/^M/ s/$$/$(MDL_RO_SUFFIX)/' -i $@
	@$(SED) '/^S/ s/ Def/$(MDL_RO_SUFFIX) Def/' -i $@

	@echo " "`grep "size" tmp/$*.sym | awk 'strtonum("0x"$$4) {print $$2": "strtonum("0x"$$4)" bytes"}'` 

tmp/%.mdl.ro.asm: tmp/%.asm 
	@echo -n $(MSG) " "
	@echo `java -jar $(MDL) $< $(MDL_FLAGS) $@ | grep summary | cut -f 1 -d. | cut -f 3 -d:`

###### LLVM FRONTENDS:

# CPP
tmp/%.ll: %.cpp $(HEADERS) 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(CLANG) $(CLANG_FLAGS) $< -o $@
	@echo 

tmp/%.ll: %.cc $(HEADERS) 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(CLANG) $(CLANG_FLAGS) $< -o $@
	@echo 

# FORTRAN
tmp/%.ll: %.f $(HEADERS) 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(FORTRAN) $(FORTRAN_FLAGS) $< -o $@
	@echo 

# D
tmp/%.ll: %.d $(HEADERS) 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(DLANG) $(DLANG_FLAGS) $< -of $@
	@echo 

# RUST
tmp/%.ll: %.rs $(HEADERS) 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(RUST) $(RUST_FLAGS) $< -o $@
	@echo 

# ZIG
tmp/%.ll: %.zig $(HEADERS) 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(ZIG) $(ZIG_FLAGS) -femit-llvm-ir=$@ $<
	
	@$(SED) '/attributes \#0/d' -i $@
	@$(SED) '/attributes \#1/d' -i $@
	
	@echo 


##########################################################
### LINKING AND CREATING A ROM

out/%_[ASCII8].rom: $(OBJ) tmp/mapper/ascii8.rel
	@echo $(MSG)
	@mkdir -p $(@D)
	@$(MEGALINKER) $(OBJ) tmp/mapper/ascii8.rel $@

out/%_[Generic8].rom: $(OBJ) tmp/mapper/generic8.rel
	@echo $(MSG)
	@mkdir -p $(@D)
	@$(MEGALINKER) $(OBJ) tmp/mapper/generic8.rel $@

rom: out/$(NAME)_[ASCII8].rom out/$(NAME)_[Generic8].rom

##########################################################
### EXECUTING SUCH ROM

msx: out/$(NAME)_[ASCII8].rom
	@echo $(MSG)
	@$(OPENMSX_DEF) $< || true

msx1: out/$(NAME)_[ASCII8].rom
	@echo $(MSG)
	@$(OPENMSX1) $< || true

msx1jp: out/$(NAME)_[ASCII8].rom
	@echo $(MSG)
	@$(OPENMSX1_JP) $< || true

msx2: out/$(NAME)_[ASCII8].rom
	@echo $(MSG)
	@$(OPENMSX2) $< || true

msx2p: out/$(NAME)_[ASCII8].rom
	@echo $(MSG)
	@$(OPENMSX2P) $< || true

msxtr: out/$(NAME)_[ASCII8].rom
	@echo $(MSG)
	@$(OPENMSXTR) $< || true
	
##########################################################
### UTILITIES SECTION

INCLUDE := util
tmp/%: %.cc
	@echo $(MSG)
	@mkdir -p $(@D)
	@$(CXX) -o $@ $< $(shell echo `grep -m1 "^// FLAGS:" $< | cut -d: -f2-`)

%: util/%.cc bin/% 
	@echo $(MSG)
	@true

clean:
	@echo -n "Cleaning... "
	@rm -rf tmp out
	@echo "Done!"

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

CCZ80FLAGS = --std-sdcc11 -mz80 --out-fmt-ihx
CCZ80FLAGS += --disable-warning 110 --disable-warning 126 --disable-warning 84 
CCZ80FLAGS += --max-allocs-per-node 2000 --allow-unsafe-read --opt-code-speed 
CCZ80FLAGS += --no-std-crt0 --nostdlib --no-xinit-opt
CCZ80FLAGS += -I$(SDCC)/device/include
CCZ80FLAGS += -D__HIDDEN__= -D__attribute__\(a\)= 
CCZ80FLAGS += -D__builtin_unreachable\(\)=while\(1\)\; 

# ASM
ASM = $(SDCC)/bin/sdasz80
ASM_FLAGS = -ogslp

# MDL
MDL = ext/mdl.jar
MDL_FLAGS = -dialect sdcc -ro -po speed -asm-dialect

MDL_ALT = ext/mdl_v2.4dev.jar
MDL_ALT_FLAGS = -dialect sdcc -ro -po speed -asm-dialect

#LLVM_C BACKEND
LLVM_CBE = ext/llvm-cbe/build/tools/llvm-cbe/llvm-cbe 
LLVM_CBE_FLAGS = --cbe-declare-locals-late

#CLANG
CLANG_AVR = clang -target avr -Wno-avr-rtlib-linking-quirks -I ext/CEdev/include
CLANG_Z80 = ext/CEdev/bin/ez80-clang -I ext/CEdev/include -target z80
CLANG_FLAGS = -S -emit-llvm -Wall -Wextra -Oz


#DLANG
DLANG = ldc2 
DLANG_FLAGS = -mtriple=avr -Oz -betterC  -release -output-ll 

#FORTRAN
FORTRAN = flang-7
FORTRAN_FLAGS =  -Mextend -S -Oz -emit-llvm

#RUST
RUST = rustc
RUST_FLAGS = --emit=llvm-ir -C opt-level=z -C embed-bitcode=no --target avr-unknown-gnu-atmega328 -Cpanic=abort
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

INCLUDES        += -Iinc -Isrc -I.
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
OBJ    += $(shell for f in `gcc -DDEPENDENCIES -I. -E -P src/tests.c`; do echo tmp/tests/$$f.rel; done)
$(info $$OBJ is [${OBJ}])


###### SDCC NATIVE: ASM
tmp/%.rel: %.s $(HEADERS) 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(ASM) $(ASM_FLAGS) $@ $<
	@echo " "`grep "size" tmp/$*.sym | awk 'strtonum("0x"$$4) {print $$2": "strtonum("0x"$$4)" bytes"}'` 
	@echo

tmp/%.asm: %.asm $(HEADERS) 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@cp $< $@
	@echo

###### SDCC NATIVE: C
tmp/%.c: %.c $(HEADERS)
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(CLANG_AVR) $(CLANG_FLAGS) $(INCLUDES) $< -o $@.clang
	@cp $< $@
	@echo

###### LLVM COMMON PIPELINE:
tmp/%.cbe.c: tmp/%.ll
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(SED) '/attributes \#/d' -i $<
	@$(LLVM_CBE) --cbe-declare-locals-late $< -o $@
	@$(SED) '/__ATTRIBUTE_WEAK__/d' -i $@
	@echo 
	
tmp/%.c: tmp/%.cbe.c
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(SED) 's/static __forceinline/inline/g' $< > $@
	@$(SED) 's/uint8_t\* memset/inline uint8_t\* memset(uint8_t\* dst, uint8_t c, uint16_t sz) {uint8_t \*p = dst; while (sz--) *p++ = c; return dst; } \/\//g' -i $@
	@$(SED) '/__noreturn void rust_begin_unwind(struct l_struct_core_KD__KD_panic_KD__KD_PanicInfo\* llvm_cbe_info)/{:a;N;/__builtin_unreachable/{N;N;d};/  }/b;ba}' -i $@
	@echo 

define SPAWN_ALLOC_TARGETS

tmp/%_$(1).asm: tmp/%.c 
	@echo -n $$(MSG)
	@mkdir -p $$(@D)
	@$$(eval ALLOCS_TMP := $$(shell echo $$@ | egrep -o "_[0-9]*k\." | tr -d "_.k")000 )
	@$$(CCZ80) -S $$(INCLUDES) $$(CCZ80FLAGS) --max-allocs-per-node $$(ALLOCS_TMP) $$< -o $$@
	@echo 

endef

MAX_ALLOCS := 1k 2k 5k 10k 20k 50k 100k 200k 500k 1000k 2000k 5000k
$(eval $(foreach i,$(MAX_ALLOCS), $(call SPAWN_ALLOC_TARGETS,$(i))))


tmp/%.asm: tmp/%.c 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(CCZ80) -S $(INCLUDES) $(CCZ80FLAGS) $< -o $@
	@echo 

tmp/%.rel: tmp/%.asm
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(ASM) $(ASM_FLAGS) $@ $<

	@$(eval AVR := $(shell echo $@ | egrep -o "_avr"))
	@$(eval AVR_SUFFIX := $(if $(AVR), _avr, ))
	@#$(SED) '/^M/ s/$$/$(AVR_SUFFIX)/' -i $@
	@$(SED) '/^S/ s/ Def/$(AVR_SUFFIX) Def/' -i $@

	@$(eval Z80 := $(shell echo $@ | egrep -o "_z80"))
	@$(eval Z80_SUFFIX := $(if $(Z80), _z80, ))
	@#$(SED) '/^M/ s/$$/$(Z80_SUFFIX)/' -i $@
	@$(SED) '/^S/ s/ Def/$(Z80_SUFFIX) Def/' -i $@

	@$(eval O := $(shell echo $@ | egrep -o "_O[^_\.]*[\._]" | tr -d "_."))
	@$(eval O_SUFFIX := $(if $(O), _$(O), ))
	@#$(SED) '/^M/ s/$$/$(O_SUFFIX)/' -i $@
	@$(SED) '/^S/ s/ Def/$(O_SUFFIX) Def/' -i $@
	
	@$(eval AK := $(shell echo $@ | egrep -o "_[0-9]*k" | tr -d "_.k"))
	@$(eval A_SUFFIX := $(if $(AK), _$(AK)k, ))
	@$(SED) '/^M/ s/$$/$(A_SUFFIX)/' -i $@
	@$(SED) '/^S/ s/ Def/$(A_SUFFIX) Def/' -i $@

	@$(eval MDLF := $(shell echo $@ | egrep -o "_mdl"))
	@$(eval MDLF_SUFFIX := $(if $(MDLF), _mdl, ))
	@$(SED) '/^M/ s/$$/$(MDLF_SUFFIX)/' -i $@
	@$(SED) '/^S/ s/ Def/$(MDLF_SUFFIX) Def/' -i $@

	@$(eval MDL_ALT_F := $(shell echo $@ | egrep -o "_mdl_alt"))
	@$(eval MDL_ALT_SUFFIX := $(if $(MDL_ALT_F), _alt, ))
	@$(SED) '/^M/ s/$$/$(MDL_ALT_SUFFIX)/' -i $@
	@$(SED) '/^S/ s/ Def/$(MDL_ALT_SUFFIX) Def/' -i $@

	@echo " "`grep "size" tmp/$*.sym | awk 'strtonum("0x"$$4) {print $$2": "strtonum("0x"$$4)" bytes"}'` 

tmp/%.rel: tmp/%.s
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(ASM) $(ASM_FLAGS) $@ $<
	@echo " "`grep "size" tmp/$*.sym | awk 'strtonum("0x"$$4) {print $$2": "strtonum("0x"$$4)" bytes"}'` 

tmp/%_mdl.asm: tmp/%.asm 
	@echo -n $(MSG) " "
	@echo `java -jar $(MDL) $< $(MDL_FLAGS) $@ | grep summary | cut -f 1 -d_ | cut -f 3 -d:`

tmp/%_mdl_alt.asm: tmp/%.asm 
	@echo -n $(MSG) " "
	@echo `java -jar $(MDL_ALT) $< $(MDL_ALT_FLAGS) $@ | grep summary | cut -f 1 -d_ | cut -f 3 -d:`


###### LLVM FRONTENDS:

# C
tmp/%_Os.ll tmp/%_Oz.ll tmp/%_O3.ll tmp/%_Ofast.ll: %.c
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(eval O := $(shell echo $@ | egrep -o "_O[^\.]*\." | tr -d "_."))
	@$(eval O := $(if $(O), -$(O), ))
	@$(CLANG_AVR) $(CLANG_FLAGS) $(INCLUDES) $(O) $< -o $@
	@echo 

tmp/%_z80_Os.ll tmp/%_z80_Oz.ll tmp/%_z80_O3.ll tmp/%_z80_Ofast.ll: %.c
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(eval O := $(shell echo $@ | egrep -o "_O[^\.]*\." | tr -d "_."))
	@$(eval O := $(if $(O), -$(O), ))
	@$(CLANG_Z80) $(CLANG_FLAGS) $(INCLUDES) $(O) $< -o $@
	@echo 

# CPP
tmp/%_Os.ll tmp/%_Oz.ll tmp/%_O3.ll tmp/%_Ofast.ll tmp/%.ll: %.cc
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(eval O := $(shell echo $@ | egrep -o "_O[^\.]*\." | tr -d "_."))
	@$(eval O := $(if $(O), -$(O), ))
	@$(CLANG_AVR) $(CLANG_FLAGS) $(INCLUDES) $(O) $< -o $@
	@echo 

tmp/%_Os.ll tmp/%_Oz.ll tmp/%_O3.ll tmp/%_Ofast.ll tmp/%.ll: %.cpp
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(eval O := $(shell echo $@ | egrep -o "_O[^\.]*\." | tr -d "_."))
	@$(eval O := $(if $(O), -$(O), ))
	@$(CLANG_AVR) $(CLANG_FLAGS) $(INCLUDES) $(O) $< -o $@
	@echo 


# FORTRAN
tmp/%_Os.ll tmp/%_Oz.ll tmp/%_O3.ll tmp/%_Ofast.ll tmp/%.ll: %.f
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(eval O := $(shell echo $@ | egrep -o "_O[^\.]*\." | tr -d "_."))
	@$(eval O := $(if $(O), -$(O), ))
	@$(FORTRAN) $(FORTRAN_FLAGS) $(O) $< -o $@
	@echo 

# D
tmp/%_Os.ll tmp/%_Oz.ll tmp/%_O3.ll tmp/%_Ofast.ll tmp/%.ll: %.d
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(eval O := $(shell echo $@ | egrep -o "_O[^\.]*\." | tr -d "_."))
	@$(eval O := $(if $(O), -$(O), ))
	@$(DLANG) $(DLANG_FLAGS) $(O) $< -of $@
	@echo 

# RUST
tmp/%_Os.ll tmp/%_Oz.ll tmp/%_O3.ll tmp/%_Ofast.ll tmp/%.ll: %.rs
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(eval O := $(shell echo $@ | egrep -o "_O[^\.]*\." | tr -d "O_."))
	@$(eval O := $(if $(O), -C opt-level=$(O), ))
	@$(RUST) $(RUST_FLAGS) $(O) $< -o $@
	@echo 

# ZIG
tmp/%_Os.ll tmp/%_Ofast.ll tmp/%.ll: %.zig
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(eval Os := $(shell echo $@ | egrep -o "_Os\." ))
	@$(eval Of := $(shell echo $@ | egrep -o "_Ofast\." ))
	@$(eval O := $(if $(Os), -O ReleaseSmall, ) $(if $(Os), -O ReleaseFast, ))
	@$(ZIG) $(ZIG_FLAGS) $(O) -femit-llvm-ir=$@ $<
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

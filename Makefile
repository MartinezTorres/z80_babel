NAME := z80_babel

.PHONY: all clean
.SECONDARY:  

all: rom 


##########################################################
### INFO MESSAGE
MSG = "\033[1;32m[$(@)]\033[1;31m\033[0m"
MISSING_MSG = "\033[1;31m[$(@) is missing]\033[1;31m\033[0m"


##########################################################
### BINARY DEPENDENCIES AND FLAGS

# SED
SED = sed

# SDCC (for some includes to work, it needs an absolute path)
SDCC = ext/sdcc-4.1.14

CCZ80 = $(SDCC)/bin/sdcc

CCZ80FLAGS = --std-sdcc11 -mz80 --out-fmt-ihx
CCZ80FLAGS += --disable-warning 110 --disable-warning 126 --disable-warning 84 --disable-warning 85
CCZ80FLAGS += --max-allocs-per-node 2000 --allow-unsafe-read --opt-code-speed 
CCZ80FLAGS += --no-std-crt0 --nostdlib --no-xinit-opt
CCZ80FLAGS += -I$(SDCC)/device/include
CCZ80FLAGS += -D__HIDDEN__= -D__attribute__\(a\)= 
CCZ80FLAGS += -D__builtin_unreachable\(\)=while\(1\)\; 

$(CCZ80):
	@echo $(MISSING_MSG) Please download/build a recent version of SDCC from: http://sdcc.sourceforge.net/snap.php && false

# ASM
ASM = $(SDCC)/bin/sdasz80
ASM_FLAGS = -ogslp

$(ASM):
	@echo $(MISSING_MSG) Please download/build a recent version of SDCC from: http://sdcc.sourceforge.net/snap.php && false

# MDL
MDL = ext/mdl_v2.3.jar
MDL_FLAGS = -dialect sdcc -ro -po speed -asm-dialect

$(MDL):
	@echo $(MISSING_MSG) Please download a release version of MDL from: https://github.com/santiontanon/mdlz80optimizer && false

MDL_DEV = ext/mdl_v2.4dev.jar
MDL_DEV_FLAGS = -dialect sdcc -ro -po speed -asm-dialect

$(MDL_DEV):
	@echo $(MISSING_MSG) Please download a development version of MDL from: https://github.com/santiontanon/mdlz80optimizer && false

#LLVM_C BACKEND
LLVM_CBE = ext/llvm-cbe/build/tools/llvm-cbe/llvm-cbe 
LLVM_CBE_FLAGS = --cbe-declare-locals-late

$(LLVM_CBE):
	@echo $(MISSING_MSG) Please download and build llvm-cbe from: https://github.com/JuliaComputingOSS/llvm-cbe && false

#CLANG
CLANG              = /usr/bin/clang
CLANG_AVR_FLAGS    = -target avr -Wno-avr-rtlib-linking-quirks 
CLANG_Z80          = ext/CEdev/bin/ez80-clang
CLANG_Z80_FLAGS    = -target z80
CLANG_Z80_HEADERS  = ext/CEdev/include
CLANG_COMMON_FLAGS = -I $(CLANG_Z80_HEADERS) -S -emit-llvm -Wall -Wextra -Oz

$(CLANG):
	@echo $(MISSING_MSG) Please install clang && false

$(CLANG_Z80):
	@echo $(MISSING_MSG) Please download and unpack the CE Toolchain from: https://github.com/CE-Programming/toolchain/releases/tag/v9.2.2  && false

$(CLANG_Z80_HEADERS):
	@echo $(MISSING_MSG) Please download and unpack the CE Toolchain from: https://github.com/CE-Programming/toolchain/releases/tag/v9.2.2  && false
	
#DLANG
DLANG = /usr/bin/ldc2 
DLANG_FLAGS = -mtriple=avr -Oz -betterC  -release -output-ll 

$(DLANG):
	@echo $(MISSING_MSG) Please install the D language compiler && false
	 

#RUST (tries to find the default rustc)
RUSTC = $(if $(shell which rustc), $(shell which rustc), rustc)
RUST_FLAGS = --emit=llvm-ir -C opt-level=z -C embed-bitcode=no --target avr-unknown-gnu-atmega328 -Cpanic=abort
RUST_FLAGS += -L dependency=ext/rust_deps 
RUST_FLAGS += --extern 'noprelude:compiler_builtins=ext/rust_deps/libcompiler_builtins-4b0354a1ee99278a.rlib' 
RUST_FLAGS += --extern 'noprelude:core=ext/rust_deps/libcore-c1e4c798d948b121.rlib' 
RUST_FLAGS += -Z unstable-options 

$(RUSTC):
	@echo $(MISSING_MSG) Please install the Rust language compiler && false

#ZIG
ZIG = ext/zig-linux-x86_64-0.9.0/zig
ZIG_FLAGS = build-obj -femit-bin=/tmp/zig-tmp -fno-stage1 -fLLVM -O ReleaseSmall --cache-dir /tmp/zig-cache -target avr-freestanding-eabi  

$(ZIG):
	@echo $(MISSING_MSG) Please download the zig compiler from https://ziglang.org/download/ && false

# LINKER
MEGALINKER = ext/megalinker/megalinker

$(MEGALINKER):
	@echo -n $(MISSING_MSG) Please download Megalinker from https://github.com/MartinezTorres/megalinker && false

# OPENMSX
OPENMSX_PARAM = -command "set speed 5000"
OPENMSX_BIN = /usr/local/bin/openmsx
OPENMSX1    =  Philips_VG_8020    
OPENMSX1_JP =  C-BIOS_MSX1_JP     
OPENMSX2    =  C-BIOS_MSX2        
OPENMSX2P   =  C-BIOS_MSX2+_JP    
OPENMSXTR   =  Panasonic_FS-A1GT  

$(OPENMSX_BIN):
	@echo $(MISSING_MSG) Please install openmsx or adjust the path in the Makefile && false



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
OBJ    += $(addprefix tmp/,$(SOURCES_DLANG:.d=.rel))
OBJ    += $(addprefix tmp/,$(SOURCES_RUST:.rs=.rel))
OBJ    += $(addprefix tmp/,$(SOURCES_ZIG:.zig=.rel))

##########################################################
### COLLECT TESTSMARKS

INCLUDES              += -Itests
OBJ    += $(shell for f in `gcc -DDEPENDENCIES -I. -E -P src/tests.c`; do echo tmp/tests/$$f.rel; done)
#$(info $$OBJ is [${OBJ}])

all: $(OBJ)


###### SDCC NATIVE: ASM
tmp/%.rel: %.s $(HEADERS) $(ASM) 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(ASM) $(ASM_FLAGS) $@ $<
	@echo " "`grep "size" tmp/$*.sym | awk 'strtonum("0x"$$4) {print $$2": "strtonum("0x"$$4)" bytes"}'` 

tmp/%.asm: %.asm $(HEADERS) 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@cp $< $@
	@echo

###### SDCC NATIVE: C
tmp/%.c: %.c $(HEADERS) $(CLANG) $(CLANG_Z80_HEADERS) 
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(CLANG) $(CLANG_AVR_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) $< -o $@.clang
	@cp $< $@
	@echo

###### LLVM COMMON PIPELINE:
tmp/%.cbe.c: tmp/%.ll $(LLVM_CBE)
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

tmp/%_$(1).asm: tmp/%.c $$(CCZ80)
	@echo -n $$(MSG)
	@mkdir -p $$(@D)
	@$$(eval ALLOCS_TMP := $$(shell echo $$@ | egrep -o "_[0-9]*k\." | tr -d "_.k")000 )
	@$$(CCZ80) -S $$(INCLUDES) $$(CCZ80FLAGS) --max-allocs-per-node $$(ALLOCS_TMP) $$< -o $$@
	@echo 

endef

MAX_ALLOCS := 1k 2k 5k 10k 20k 50k 100k 200k 500k 1000k 2000k 5000k 10000k
$(eval $(foreach i,$(MAX_ALLOCS), $(call SPAWN_ALLOC_TARGETS,$(i))))


tmp/%.asm: tmp/%.c $(CCZ80)
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

	@$(eval MDL_DEV_F := $(shell echo $@ | egrep -o "_mdl_dev"))
	@$(eval MDL_DEV_SUFFIX := $(if $(MDL_DEV_F), _dev, ))
	@$(SED) '/^M/ s/$$/$(MDL_DEV_SUFFIX)/' -i $@
	@$(SED) '/^S/ s/ Def/$(MDL_DEV_SUFFIX) Def/' -i $@

	@echo " "`grep "size" tmp/$*.sym | awk 'strtonum("0x"$$4) {print $$2": "strtonum("0x"$$4)" bytes"}'` 

tmp/%.rel: tmp/%.s $(ASM)
	@echo -n $(MSG)
	@mkdir -p $(@D)
	@$(ASM) $(ASM_FLAGS) $@ $<
	@echo " "`grep "size" tmp/$*.sym | awk 'strtonum("0x"$$4) {print $$2": "strtonum("0x"$$4)" bytes"}'` 

tmp/%_mdl.asm: tmp/%.asm $(MDL)
	@echo -n $(MSG) " "
	@echo `java -jar $(MDL) $< $(MDL_FLAGS) $@ | grep summary | cut -f 1 -d_ | cut -f 3 -d:`

tmp/%_mdl_dev.asm: tmp/%.asm $(MDL_DEV)
	@echo -n $(MSG) " "
	@echo `java -jar $(MDL_DEV) $< $(MDL_DEV_FLAGS) $@ | grep summary | cut -f 1 -d_ | cut -f 3 -d:`


###### LLVM FRONTENDS:

# C
tmp/%_Ofast.ll: %.c $(CLANG) 
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG) $(CLANG_AVR_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) -Ofast $< -o $@

tmp/%_O3.ll: %.c $(CLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG) $(CLANG_AVR_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) -O3    $< -o $@

tmp/%_Os.ll: %.c $(CLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG) $(CLANG_AVR_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) -Os    $< -o $@

tmp/%_Oz.ll: %.c $(CLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG) $(CLANG_AVR_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) -Oz    $< -o $@



tmp/%_z80_Ofast.ll: %.c $(CLANG_Z80)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG_Z80) $(CLANG_Z80_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) -Ofast $< -o $@

tmp/%_z80_O3.ll: %.c $(CLANG_Z80)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG_Z80) $(CLANG_Z80_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) -O3    $< -o $@

tmp/%_z80_Os.ll: %.c $(CLANG_Z80)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG_Z80) $(CLANG_Z80_FLAGS) $(CLANG_COMMON_FLAGS)) $(INCLUDES) -Os    $< -o $@

tmp/%_z80_Oz.ll: %.c $(CLANG_Z80)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG_Z80) $(CLANG_Z80_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) -Oz    $< -o $@


# CPP
tmp/%_Ofast.ll: %.cc $(CLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG) $(CLANG_AVR_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) -Ofast $< -o $@

tmp/%_O3.ll: %.cc $(CLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG) $(CLANG_AVR_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) -O3    $< -o $@

tmp/%_Os.ll: %.cc $(CLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG) $(CLANG_AVR_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) -Os    $< -o $@

tmp/%_Oz.ll: %.cc $(CLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG) $(CLANG_AVR_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) -Oz    $< -o $@

tmp/%.ll: %.cc $(CLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG) $(CLANG_AVR_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES)        $< -o $@

tmp/%_Ofast.ll: %.cpp $(CLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG) $(CLANG_AVR_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) -Ofast $< -o $@

tmp/%_O3.ll: %.cpp $(CLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG) $(CLANG_AVR_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) -O3    $< -o $@

tmp/%_Os.ll: %.cpp $(CLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG) $(CLANG_AVR_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) -Os    $< -o $@

tmp/%_Oz.ll: %.cpp $(CLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG) $(CLANG_AVR_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES) -Oz    $< -o $@

tmp/%.ll: %.cpp $(CLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(CLANG) $(CLANG_AVR_FLAGS) $(CLANG_COMMON_FLAGS) $(INCLUDES)        $< -o $@

# D
tmp/%_O3.ll: %.d $(DLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(DLANG) $(DLANG_FLAGS) -O3    $< -of $@

tmp/%_Os.ll: %.d $(DLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(DLANG) $(DLANG_FLAGS) -Os    $< -of $@

tmp/%_Oz.ll: %.d $(DLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(DLANG) $(DLANG_FLAGS) -Oz    $< -of $@

tmp/%.ll: %.d $(DLANG)
	@echo $(MSG) && mkdir -p $(@D) && $(DLANG) $(DLANG_FLAGS)        $< -of $@


# RUST
tmp/%_O3.ll: %.rs $(RUSTC)
	@echo $(MSG) && mkdir -p $(@D) && $(RUSTC) $(RUST_FLAGS) -C opt-level=3    $< -o $@

tmp/%_Os.ll: %.rs $(RUSTC)
	@echo $(MSG) && mkdir -p $(@D) && $(RUSTC) $(RUST_FLAGS) -C opt-level=s    $< -o $@

tmp/%_Oz.ll: %.rs $(RUSTC)
	@echo $(MSG) && mkdir -p $(@D) && $(RUSTC) $(RUST_FLAGS) -C opt-level=z    $< -o $@

tmp/%.ll: %.rs $(RUSTC)
	@echo $(MSG) && mkdir -p $(@D) && $(RUSTC) $(RUST_FLAGS)                   $< -o $@


# ZIG
tmp/%_O3.ll: %.zig $(ZIG)
	@echo $(MSG) && mkdir -p $(@D) && $(ZIG) $(ZIG_FLAGS) -O ReleaseFast  -femit-llvm-ir=$@  $< 

tmp/%_Os.ll: %.zig $(ZIG)
	@echo $(MSG) && mkdir -p $(@D) && $(ZIG) $(ZIG_FLAGS) -O ReleaseSmall -femit-llvm-ir=$@  $< 

tmp/%.ll: %.zig $(ZIG)
	@echo $(MSG) && mkdir -p $(@D) && $(ZIG) $(ZIG_FLAGS)                 -femit-llvm-ir=$@  $< 

##########################################################
### LINKING AND CREATING A ROM

out/%_[ASCII8].rom: $(OBJ) tmp/mapper/ascii8.rel $(MEGALINKER)
	@echo $(MSG)
	@mkdir -p $(@D)
	@$(MEGALINKER) $(OBJ) tmp/mapper/ascii8.rel $@ 

out/%_[Generic8].rom: $(OBJ) tmp/mapper/generic8.rel $(MEGALINKER)
	@echo $(MSG)
	@mkdir -p $(@D)
	@$(MEGALINKER) $(OBJ) tmp/mapper/generic8.rel $@

rom: out/$(NAME)_[ASCII8].rom out/$(NAME)_[Generic8].rom

##########################################################
### EXECUTING SUCH ROM

msx: out/$(NAME)_[ASCII8].rom $(OPENMSX_BIN)
	@echo $(MSG)
	@$(OPENMSX_BIN) $(OPENMSX_PARAM) -carta $< || true

msx1: out/$(NAME)_[ASCII8].rom $(OPENMSX_BIN)
	@echo $(MSG)
	@$(OPENMSX_BIN) -machine $(OPENMSX1)    $(OPENMSX_PARAM) -carta $< || true

msx1jp: out/$(NAME)_[ASCII8].rom $(OPENMSX_BIN)
	@echo $(MSG)
	@$(OPENMSX_BIN) -machine $(OPENMSX1_JP) $(OPENMSX_PARAM) -carta $< || true

msx2: out/$(NAME)_[ASCII8].rom $(OPENMSX_BIN)
	@echo $(MSG)
	@$(OPENMSX_BIN) -machine $(OPENMSX2)    $(OPENMSX_PARAM) -carta $< || true

msx2p: out/$(NAME)_[ASCII8].rom $(OPENMSX_BIN)
	@echo $(MSG)
	@$(OPENMSX_BIN) -machine $(OPENMSX2P)   $(OPENMSX_PARAM) -carta $< || true

msxtr: out/$(NAME)_[ASCII8].rom $(OPENMSX_BIN) 
	@echo $(MSG)
	@$(OPENMSX_BIN) -machine $(OPENMSXTR)   $(OPENMSX_PARAM) -carta $< || true
	
##########################################################
### UTILITIES SECTION

clean:
	@echo -n "Cleaning... "
	@rm -rf tmp out
	@echo "Done!"

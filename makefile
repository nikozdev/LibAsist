# basic

NAME:=libasist
VERS:=a0a0a0
TYPE:=RUN

# files

HDREXT:=hxx
SRCEXT:=cxx
OBJEXT:=obj
BINEXT:=bin
MANEXT:=man

## source

SROOT:=.

### fdirs

SDHDR:=$(SROOT)/src
SDSRC:=$(SROOT)/src
SDOBJ:=$(SROOT)/obj
SDBIN:=$(SROOT)/bin
SDRSC:=$(SROOT)/rsc
SDMAN:=$(SROOT)/man

### lists

SLHDR:=$(wildcard $(SDHDR)/*.$(HDREXT))
SLSRC:=$(patsubst $(SDHDR)/%.$(HDREXT),$(SDSRC)/%.$(SRCEXT),$(SLHDR))
SLOBJ:=$(patsubst $(SDSRC)/%.$(SRCEXT),$(SDOBJ)/%.$(OBJEXT),$(SLSRC))
SLBIN:=$(SDBIN)/$(NAME).$(BINEXT)
SLMAN:=$(wildcard $(SDMAN)/*.$(MANEXT))

## target

TROOT?=$(HOME)/.local/bin

### fdirs

TDBIN:=$(TROOT)/bin
TDMAN:=$(TROOT)/share/man/man1

### lists

TLBIN:=$(patsubst $(SDBIN)/%.$(BINEXT),$(TDBIN)/%,$(SLBIN))
TLMAN:=$(patsubst $(SDMAN)/%,$(TDMAN)/%,$(SLMAN))

# build

## compiler

CMAKER?= $(shell which clang++) -c -o
CFLAGS+= -std=c++20 -stdlib=libc++
CFLAGS+= -O0 -g
CFLAGS+= -D_NAME=$(NAME) -D_NAME_STR=\"$(NAME)\"
CLFAGS+= -D_VERS=$(VERS) -D_VERS_STR=\"$(VERS)\"
CFLAGS+= -D_TYPE_$(TYPE) -D_TYPE_STR=\"$(TYPE)\"
CFLAGS+= $(addprefix -include ,$(SLHDR))

## linker

LMAKER?= $(shell which clang++) -o

# shell

SHSU:= $(shell which sudo)
SHCO:= $(shell which chown) -R $(USER):$(USER)
SHCM:= $(shell which chmod) -R
SHCP:= $(shell which cp) -riv
SHRM:= $(shell which rm) -rfv
SHMV:= $(shell which mv) -iv
SHMD:= $(shell which mkdir) -p
SHDB:= $(shell which lldb)

# rules

## internal

build: build-head $(SLOBJ) $(SLBIN)
	$(SHRM) $(SLSRC)
build-head:
	$(info "--[[build]]--")

clean: clean-head
	$(SHRM) $(SLOBJ) $(SLBIN)
clean-head:
	$(info "--[[clean]]--")

## external

setup: setup-head $(TLBIN) $(TLMAN)
setup-head:
	$(info "--[=[setup]=]--")

reset: reset-head
	$(SHRM) $(TLBIN) $(TLMAN)
reset-head:
	$(info "--[=[reset]=]--")

## addition

again: again-head clean build
again-head:
	$(info "--[=[again]=]--")

start: start-head build
	for b in ${SLBIN}; do $$b; done
start-head:
	$(info "--[=[start]=]--")

rerun: rerun-head again start
rerun-head:
	$(info "--[==[rerun]==]--")

debug: debug-head again
	for bin in ${SLBIN}; do $(SHDB) $$b; done
debug-head:
	$(info "--[==[debug]==]--")

print: print-head
	$(info --[[basic]]--)
	$(info [NAME]=$(NAME))
	$(info [VERS]=$(VERS))
	$(info --[[files]]--)
	$(info --[=[source]=]--)
	$(info [SROOT]=$(SROOT))
	$(info --[==[fdirs]==]--)
	$(info [SDSRC]=$(SDSRC))
	$(info [SDOBJ]=$(SDOBJ))
	$(info [SDBIN]=$(SDBIN))
	$(info [SDRSC]=$(SDRSC))
	$(info [SDMAN]=$(SDMAN))
	$(info --[==[lists]==]--)
	$(info [SLSRC]=$(SLSRC))
	$(info [SLOBJ]=$(SLOBJ))
	$(info [SLBIN]=$(SLBIN))
	$(info [SLRSC]=$(SLRSC))
	$(info [SLMAN]=$(SLMAN))
	$(info --[=[target]=]--)
	$(info [TROOT]=$(TROOT))
	$(info --[==[fdirs]==]--)
	$(info [TDBIN]=$(TDBIN))
	$(info [TDMAN]=$(TDMAN))
	$(info --[==[lists]==]--)
	$(info [TLBIN]=$(TLBIN))
	$(info [TLMAN]=$(TLMAN))
	$(info --[[build]]--)
	$(info --[=[compiler]=]--)
	$(info [CMAKER]=$(CMAKER))
	$(info [CFLAGS]=$(CFLAGS))
	$(info --[=[linker]=]--)
	$(info [LMAKER]=$(LMAKER))
	$(info [LFLAGS]=$(LFLAGS))
	$(info --[[shell]]--)
	$(info [SHSU]=$(SHSU))
	$(info [SHCO]=$(SHCO))
	$(info [SHCM]=$(SHCM))
	$(info [SHCP]=$(SHCP))
	$(info [SHRM]=$(SHRM))
	$(info [SHMV]=$(SHMV))
	$(info [SHMD]=$(SHMD))
	$(info [SHDB]=$(SHDB))
	$(info --[[rules]]--)
	$(info --[=[build]=]--)
	$(info link binary file from object code compiled from source code)
	$(info --[=[clean]=]--)
	$(info remove compiled object code and linked binary file)
	$(info --[=[setup]=]--)
	$(info copy binary and manual files into the system)
	$(info --[=[reset]=]--) $(info remove binary and manual files from the system)
	$(info --[=[again]=]--)
	$(info clean and rebuild the project again)
	$(info --[=[start]=]--)
	$(info build and run the binary file)
	$(info --[=[rerun]=]--)
	$(info clean, rebuild and run the binary file with the shell)
	$(info --[=[debug]=]--)
	$(info clean, rebuild and run the binary file with the debugger)
print-head:
	$(info --[print]--)

## source

$(SDHDR)/%.$(HDREXT):
	$(info "[header]=$@")

$(SDSRC)/%.$(SRCEXT): $(SDHDR)/%.$(HDREXT)
	$(info "[source]=$@")
	touch $@

$(SDOBJ)/%.$(OBJEXT): $(SDSRC)/%.$(SRCEXT)
	$(info "[object]=$@")
	$(CMAKER) $@ $^ $(CFLAGS)

$(SDBIN)/%.$(BINEXT): $(SLOBJ)
	$(info "[source-binary]=$@")
	$(LMAKER) $@ $^ $(LFLAGS)

$(SDMAN)/%.$(MANEXT):
	$(info "[source-manual]=$@")

## target

$(TDBIN)/%: %.$(BINEXT)
	$(info "[target-binary]=$@")
	$(SHCP) $< $@
	$(SHCO) $@
	$(SHCM) 744 $@

$(TDMAN)/%.$(MANEXT): %.$(MANEXT)
	$(info "[target-manual]=$@")
	$(SHCP) $< $@
	$(SHCM) 644 $@

# endof

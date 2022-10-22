# basic

NAME:=libasist
VERS:=0a0a0
TYPE:=RUN

# files

HDREXT:=hxx
SRCEXT:=cxx
OBJEXT:=obj
BINEXT:=bin
MANEXT:=man

## source

SROOT:=.

SLHDR:=$(wildcard $(SROOT)/*.$(HDREXT))
SLSRC:=$(patsubst %.$(HDREXT),%.$(SRCEXT),$(SLHDR))
SLOBJ:=$(patsubst %.$(SRCEXT),%.$(OBJEXT),$(SLSRC))
SLBIN:=$(SROOT)/$(NAME).$(BINEXT)
SLMAN:=$(SROOT)/$(NAME).$(MANEXT)

## target

TROOT?=$(HOME)/.local/bin

TDBIN:=$(TROOT)/bin
TDMAN:=$(TROOT)/share/man/man1

TLBIN:=$(patsubst $(SROOT)/%.$(BINEXT),$(TDBIN)/%,$(SLBIN))
TLMAN:=$(patsubst $(SROOT)/%,$(TDMAN)/%,$(SLMAN))

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
	$(SLBIN)
start-head:
	$(info "--[=[start]=]--")

rerun: rerun-head again
	$(SLBIN)
rerun-head:
	$(info "--[==[rerun]==]--")

debug: debug-head again
	$(SHDB) $(SLBIN)
debug-head:
	$(info "--[==[debug]==]--")

print: print-head
	$(info --[=[basic]=]--)
	$(info [NAME]=$(NAME))
	$(info [VERS]=$(VERS))
	$(info --[=[files]=]--)
	$(info --[[source]]--)
	$(info [SLSRC]=$(SLSRC))
	$(info [SLOBJ]=$(SLOBJ))
	$(info [SLBIN]=$(SLBIN))
	$(info --[[target]]--)
	$(info [TROOT]=$(TROOT))
	$(info [TDBIN]=$(TDBIN))
	$(info [TDMAN]=$(TDMAN))
	$(info [TLBIN]=$(TLBIN))
	$(info [TLMAN]=$(TLMAN))
	$(info --[=[build]=]--)
	$(info --[[compiler]]--)
	$(info [CMAKER]=$(CMAKER))
	$(info [CFLAGS]=$(CFLAGS))
	$(info --[[linker]]--)
	$(info [LMAKER]=$(LMAKER))
	$(info [LFLAGS]=$(LFLAGS))
	$(info --[=[shell]=]--)
	$(info [SHSU]=$(SHSU))
	$(info [SHCO]=$(SHCO))
	$(info [SHCM]=$(SHCM))
	$(info [SHCP]=$(SHCP))
	$(info [SHRM]=$(SHRM))
	$(info [SHMV]=$(SHMV))
	$(info [SHMD]=$(SHMD))
	$(info [SHDB]=$(SHDB))
	$(info --[=[rules]=]--)
	$(info --[build]--)
	$(info link binary file from object code compiled from source code)
	$(info --[clean]--)
	$(info remove compiled object code and linked binary file)
	$(info --[setup]--)
	$(info copy binary and manual files into the system)
	$(info --[reset]--) $(info remove binary and manual files from the system)
	$(info --[again]--)
	$(info clean and rebuild the project again)
	$(info --[start]--)
	$(info build and run the binary file)
	$(info --[rerun]--)
	$(info clean, rebuild and run the binary file with the shell)
	$(info --[debug]--)
	$(info clean, rebuild and run the binary file with the debugger)
print-head:
	$(info --[==[print]==]--)

## source

%.$(HDREXT):
	$(info "[header]=$@")

%.$(SRCEXT): %.$(HDREXT)
	$(info "[source]=$@")
	touch $@

%.$(OBJEXT): %.$(SRCEXT)
	$(info "[object]=$@")
	$(CMAKER) $@ $^ $(CFLAGS)

%.$(BINEXT): $(SLOBJ)
	$(info "[source-binary]=$@")
	$(LMAKER) $@ $^ $(LFLAGS)

%.$(MANEXT):
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

# basic

NAME:=libasist
VNUM:=a0a0a0
TYPE:=RUN

# files

SRCSUF:=cxx
HDRSUF:=hxx
OBJSUF:=obj
BINSUF:=bin
MANSUF:=man

## source

SROOT:=.

### fdirs

SDSRC:=$(SROOT)/src
SDHDR:=$(SROOT)/src
SDOBJ:=$(SROOT)/obj
SDBIN:=$(SROOT)/bin
SDRSC:=$(SROOT)/rsc
SDMAN:=$(SROOT)/man

### lists

SLSRC:=$(wildcard $(SDSRC)/*.$(SRCSUF))
SLHDR:=$(wildcard $(SDSRC)/%.$(SRCSUF),$(SDHDR)/%.$(HDRSUF),$(SLSRC))
SLOBJ:=$(patsubst $(SDSRC)/%.$(SRCSUF),$(SDOBJ)/%.$(OBJSUF),$(SLSRC))
SLBIN:=$(SDBIN)/$(NAME).$(BINSUF)
SLMAN:=$(wildcard $(SDMAN)/*.$(MANSUF))

## target

TROOT?=$(HOME)/.local/bin

### fdirs

TDBIN:=$(TROOT)/bin
TDMAN:=$(TROOT)/share/man/man1

### lists

TLBIN:=$(patsubst $(SDBIN)/%.$(BINSUF),$(TDBIN)/%,$(SLBIN))
TLMAN:=$(patsubst $(SDMAN)/%,$(TDMAN)/%,$(SLMAN))

# build

## compiler

CMAKER?= $(shell which clang++) -c -o
CFLAGS+= -std=c++20 -stdlib=libc++
CFLAGS+= -O0 -g
CFLAGS+= -Wno-initializer-overrides
CFLAGS+= -D_NAME=$(NAME) -D_NAME_STR=\"$(NAME)\"
CLFAGS+= -D_VNUM=$(VNUM) -D_VNUM_STR=\"$(VNUM)\"
CFLAGS+= -D_TYPE_$(TYPE) -D_TYPE_STR=\"$(TYPE)\"

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
	$(info "[[build]]")

clean: clean-head
	$(SHRM) $(SLOBJ) $(SLBIN)
clean-head:
	$(info "[[clean]]")

## external

setup: setup-head $(TLBIN) $(TLMAN)
setup-head:
	$(info "[[setup]]")

reset: reset-head
	$(SHRM) $(TLBIN) $(TLMAN)
reset-head:
	$(info "[[reset]]")

## addition

again: again-head clean build
again-head:
	$(info "[[again]]")

start: start-head build
	for bin in ${SLBIN}; do $$bin; done
start-head:
	$(info "[[start]]")

rerun: rerun-head again start
rerun-head:
	$(info "[[rerun]]")

debug: debug-head again
	for bin in ${SLBIN}; do $(SHDB) $$bin; done
debug-head:
	$(info "[[debug]]")

print: print-head
	$(info [=[basic]=])
	$(info [NAME]=$(NAME))
	$(info [VNUM]=$(VNUM))
	$(info [=[files]=])
	$(info [==[source]==])
	$(info [SROOT]=$(SROOT))
	$(info [===[fdirs]===])
	$(info [SDSRC]=$(SDSRC))
	$(info [SDHDR]=$(SDHDR))
	$(info [SDOBJ]=$(SDOBJ))
	$(info [SDBIN]=$(SDBIN))
	$(info [SDRSC]=$(SDRSC))
	$(info [SDMAN]=$(SDMAN))
	$(info [===[lists]===])
	$(info [SLSRC]=$(SLSRC))
	$(info [SLHDR]=$(SLHDR))
	$(info [SLOBJ]=$(SLOBJ))
	$(info [SLBIN]=$(SLBIN))
	$(info [SLRSC]=$(SLRSC))
	$(info [SLMAN]=$(SLMAN))
	$(info [==[target]==])
	$(info [TROOT]=$(TROOT))
	$(info [===[fdirs]===])
	$(info [TDBIN]=$(TDBIN))
	$(info [TDMAN]=$(TDMAN))
	$(info [===[lists]===])
	$(info [TLBIN]=$(TLBIN))
	$(info [TLMAN]=$(TLMAN))
	$(info [=[build]=])
	$(info [==[compiler]==])
	$(info [CMAKER]=$(CMAKER))
	$(info [CFLAGS]=$(CFLAGS))
	$(info [==[linker]==])
	$(info [LMAKER]=$(LMAKER))
	$(info [LFLAGS]=$(LFLAGS))
	$(info [=[shell]=])
	$(info [SHSU]=$(SHSU))
	$(info [SHCO]=$(SHCO))
	$(info [SHCM]=$(SHCM))
	$(info [SHCP]=$(SHCP))
	$(info [SHRM]=$(SHRM))
	$(info [SHMV]=$(SHMV))
	$(info [SHMD]=$(SHMD))
	$(info [SHDB]=$(SHDB))
	$(info [=[rules]=])
	$(info [build]=link binary file from object code compiled from source code)
	$(info [clean]=remove compiled object code and linked binary file)
	$(info [setup]=copy binary and manual files into the system)
	$(info [reset]=remove binary and manual files from the system)
	$(info [again]=clean and rebuild the project again)
	$(info [start]=build and run the binary file)
	$(info [rerun]=clean, rebuild and run the binary file with the shell)
	$(info [debug]=clean, rebuild and run the binary file with the debugger)
print-head:
	$(info [[print]])

## source

$(SDSRC)/%.$(SRCSUF):
	$(info "[source]=$@")

$(SDHDR)/%.$(HDRSUF):
	$(info "[header]=$@")

$(SDOBJ)/%.$(OBJSUF): $(SDSRC)/%.$(SRCSUF)
	$(info "[object]=$@")
	$(CMAKER) $@ $^ $(CFLAGS)

$(SDBIN)/%.$(BINSUF): $(SLOBJ)
	$(info "[source-binary]=$@")
	$(LMAKER) $@ $^ $(LFLAGS)

$(SDMAN)/%.$(MANSUF):
	$(info "[source-manual]=$@")

## target

$(TDBIN)/%: %.$(BINSUF)
	$(info "[target-binary]=$@")
	$(SHCP) $< $@
	$(SHCO) $@
	$(SHCM) 744 $@

$(TDMAN)/%.$(MANSUF): %.$(MANSUF)
	$(info "[target-manual]=$@")
	$(SHCP) $< $@
	$(SHCM) 644 $@

# endof

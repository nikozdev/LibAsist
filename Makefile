# basic

NAME:=libasist
VNUM:=0xa0a2a3
TYPE:=EXE
CONF:=WORK

# operating system

ifeq ($(OSYS),)
ifeq ($(findstring Windows,$(OS)),Windows)
OSYS:=winos
else ifeq ($(shell uname -s),Linux)
OSYS:=linux
else ifeq ($(shell uname -s),Darwin)
OSYS:=macos
else
$(info failed to figure out the operating system)
endif
endif

# architecture

ARCH:=x64
ifeq ($(ARCH),)
ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
ARCH:=x64
else ifeq ($(PROCESSOR_ARCHITECTURE),x86)
ARCH:=x32
else ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
ARCH:=x64
else ifeq ($(shell uname -p),x86)
ARCH:=x32
else ifeq ($(shell uname -p),x32)
ARCH:=x32
else ifeq ($(shell uname -p),x64)
ARCH:=x64
else ifeq ($(shell uname -p),arm)
ARCH:=arm
else
$(info failed to figure out the system architecture)
endif
endif

# files

## suf-fix

HDRSUF:=hxx
PCHSUF:=gch
SRCSUF:=cxx
OBJSUF:=obj
BINSUF_EXE:=exe
BINSUF_SLL:=sll
BINSUF_DLL:=dll
ifeq ($(TYPE),)
else ifeq ($(TYPE),EXE)
BINSUF:=$(BINSUF_EXE)
else ifeq ($(TYPE),SLL)
BINSUF:=$(BINSUF_SLL)
else ifeq ($(TYPE),DLL)
BINSUF:=$(BINSUF_DLL)
endif
MANSUF:=man

## source

### directories

FSDLOC:=.

HDRFSD:=$(FSDLOC)/src
PCHFSD:=$(FSDLOC)/src
SRCFSD:=$(FSDLOC)/src
OBJFSD:=$(FSDLOC)/obj

BINFSD:=$(FSDLOC)/bin
MANFSD:=$(FSDLOC)/man

RSCFSD:=$(FSDLOC)/rsc

### lists

HDRFSL:=$(wildcard $(HDRFSD)/*.$(HDRSUF))
PCHFSL:=$(PCHFSD)/head.$(HDRSUF).$(PCHSUF)
SRCFSL:=$(wildcard $(SRCFSD)/*.$(SRCSUF) $(SRCFSD)/**/*.$(SRCSUF))
OBJFSL:=$(patsubst $(SRCFSD)/%.$(SRCSUF),$(OBJFSD)/%.$(OBJSUF),$(SRCFSL))

BINFSL:=$(BINFSD)/$(NAME).$(BINSUF)
MANFSL:=$(wildcard $(MANFSD)/*.$(MANSUF))

RSCFSL:= $(wildcard $(RSCFSD)/*.*) $(wildcard $(RSCFSD)/*/*.*)

## target

### locations

FTDLOC:=$(HOME)/.local

### directories

BINFTD:=$(FTDLOC)/bin
MANFTD:=$(FTDLOC)/share/man/man1

### lists

BINFTL:=$(patsubst $(BINFSD)/%.*,$(BINFTD)/%,$(BINFSL))
MANFTL:=$(patsubst $(MANFSD)/%,$(MANFTD)/%,$(MANFSL))

# build

## libraries

LIBDIR:=$(FSDLOC)/lib
LIBSET:=$(patsubst $(LIBDIR)/%,%,$(wildcard $(LIBDIR)/*))
LIBUSE:=$(subst ,,$(LIBSET))
LIBMOD:=SLL
LIBSUF:=$(BINSUF_$(LIBMOD))
LIBLIN:=$(patsubst %,$(LIBDIR)/%/bin/*.$(LIBSUF),$(LIBUSE))

## compiler

ifeq ($(OSYS),)
$(info undefined operating system)
else ifeq ($(OSYS),linux)
CMAKER:= $(shell which g++) -c -o
ifeq ($(TYPE),)
$(info undefined build type)
else ifeq ($(TYPE),EXE)
else ifeq ($(TYPE),SLL)
else ifeq ($(TYPE),DLL)
#CFLAGS+= -Wl,--out-implib=lib${module}.dll.a
CFLAGS+= -Wl,--export-all-symbols
CFLAGS+= -Wl,--enable-auto-import
#CFLAGS+= -Wl,--whole-archive ${old_libs}
#CFLAGS+= -Wl,--no-whole-archive ${dependency_libs}
CFLAGS+= -fPIC
else
$(info unknown build type: $(TYPE))
endif
else ifeq ($(OSYS),macos)
CMAKER:= $(shell which clang++) -c -o
ifeq ($(TYPE),)
$(info unkown build type)
else ifeq ($(TYPE),EXE)
else ifeq ($(TYPE),SLL)
else ifeq ($(TYPE),DLL)
#CFLAGS+= -Wl,--out-implib=lib${module}.dll.a
CFLAGS+= -Wl,--export-all-symbols
CFLAGS+= -Wl,--enable-auto-import
#CFLAGS+= -Wl,--whole-archive ${old_libs}
#CFLAGS+= -Wl,--no-whole-archive ${dependency_libs}
CFLAGS+= -fPIC
else
$(info unknown build type: $(TYPE))
endif
else ifeq ($(OSYS),winos)
# temporary value, figure this out
CMAKER:= cl
ifeq ($(TYPE),)
$(info unkown build type)
else ifeq ($(TYPE),EXE)
else ifeq ($(TYPE),SLL)
else ifeq ($(TYPE),DLL)
else
$(info unknown build type: $(TYPE))
endif
else
$(info undefined operating system: $(OSYS))
endif
CFLAGS+= -std=c++23
ifeq ($(CONF),)
else ifeq ($(CONF),WORK)
CFLAGS+= -O0 -g
else ifeq ($(CONF),PLAY)
CFLAGS+= -O3
endif
CFLAGS+= -Wno-error=narrowing -Wno-narrowing
CFLAGS+= -Wno-class-conversion
CFLAGS+= -fpermissive
CFLAGS+= -D_NAME=$(NAME) -D_NAME_STR=\"$(NAME)\"
CFLAGS+= -D_VNUM=$(VNUM) -D_VNUM_STR=\"$(VNUM)\"
CFLAGS+= -D_TYPE_$(TYPE) -D_TYPE_STR=\"$(TYPE)\"
CFLAGS+= -D_CONF_$(CONF) -D_CONF_STR=\"$(CONF)\"
#CFLAGS+= $(shell pkg-config --cflags) # external deps here
CFLAGS+= -I$(PCHFSD)
CFLAGS+= $(patsubst %,-I$(LIBDIR)/%/src,$(LIBUSE))

## linker

ifeq ($(OSYS),)
$(info undefined operating system)
else ifeq ($(OSYS),linux)
ifeq ($(TYPE),)
$(info undefined build type)
else ifeq ($(TYPE),EXE)
LMAKER:= $(shell which g++) -o
else ifeq ($(TYPE),SLL)
LMAKER:= $(shell which ar) -rc
else ifeq ($(TYPE),DLL)
LMAKER:= $(shell which g++) -shared -o
else
$(info unknown build type: $(TYPE))
endif
else ifeq ($(OSYS),macos)
LMAKER:= $(shell which llvm-ar)
ifeq ($(TYPE),)
$(info undefined build type)
else ifeq ($(TYPE),EXE)
LMAKER:= $(shell which clang++) -o
else ifeq ($(TYPE),SLL)
LMAKER:= $(shell which llvm-ar)
else ifeq ($(TYPE),DLL)
LMAKER:= $(shell which clang++) -shared -o
else
$(info unknown build type: $(TYPE))
endif
else ifeq ($(OSYS),winos)
# temporary value, figure this out
ifeq ($(TYPE),)
$(info undefined build type)
else ifeq ($(TYPE),EXE)
LMAKER:= link
else ifeq ($(TYPE),SLL)
LMAKER:= link
else ifeq ($(TYPE),DLL)
LMAKER:= link
else
$(info unknown build type: $(TYPE))
endif
else
$(info unknown operating system: $(OSYS))
endif
LFLAGS+= -lstdc++
#LFLAGS+= $(shell pkg-config --libs) # external deps here
LFLAGS+= $(patsubst %,-L$(LIBDIR)/%/bin,$(LIBUSE))
LFLAGS+= $(patsubst %,-l:%.$(LIBSUF),$(LIBUSE))

# terminal

TERMSU:= $(shell which sudo)
TERMCO:= $(shell which chown) -R $(USER):$(USER)
TERMCM:= $(shell which chmod) -R
TERMCP:= $(shell which cp) -riv
TERMRM:= $(shell which rm) -rfv
TERMMV:= $(shell which mv) -iv
TERMMD:= $(shell which mkdir) -p
TERMDB:= $(shell which gdb)

# rules

## internal

build: build-head $(PCHFSL) $(OBJFSL) $(BINFSL) $(LIBLIN)
build-head:
	$(info "[[build]]")

clean: clean-head
	$(TERMRM) $(OBJFSL) $(BINFSL) $(PCHFSL)
clean-head:
	$(info "[[clean]]")

## external

setup: setup-head $(BINFTL) $(MANFTL)
setup-head:
	$(info "[[setup]]")

reset: reset-head
	$(TERMRM) $(BINFTL) $(MANFTL)
reset-head:
	$(info "[[reset]]")

## addition

again: again-head clean build
again-head:
	$(info "[[again]]")

start: start-head build
	@for bin in ${BINFSL}; do $$bin $(ARGV); done
start-head:
	$(info "[[start]]")

rerun: rerun-head again start
rerun-head:
	$(info "[[rerun]]")

debug: debug-head again
	@for bin in ${BINFSL}; do $(TERMDB) $$bin $(ARGV); done
debug-head:
	$(info "[[debug]]")

print: print-head
	$(info [=[basic]=])
	$(info [NAME]=$(NAME))
	$(info [VNUM]=$(VNUM))
	$(info [TYPE]=$(TYPE))
	$(info [CONF]=$(CONF))
	$(info [OSYS]=$(OSYS))
	$(info [ARCH]=$(ARCH))
	$(info [ARGV]=$(ARGV))
	$(info [=[files]=])
	$(info [==[suffix]==])
	$(info [HDRSUF]=$(HDRSUF))
	$(info [PCHSUF]=$(PCHSUF))
	$(info [SRCSUF]=$(SRCSUF))
	$(info [OBJSUF]=$(OBJSUF))
	$(info [BINSUF]=$(BINSUF))
	$(info [MANSUF]=$(MANSUF))
	$(info [==[source]==])
	$(info [===[directories]===])
	$(info [FSDLOC]=$(FSDLOC))
	$(info [HDRFSD]=$(HDRFSD))
	$(info [PCHFSD]=$(PCHFSD))
	$(info [SRCFSD]=$(SRCFSD))
	$(info [OBJFSD]=$(OBJFSD))
	$(info [BINFSD]=$(BINFSD))
	$(info [MANFSD]=$(MANFSD))
	$(info [RSCFSD]=$(RSCFSD))
	$(info [===[lists]===])
	$(info [HDRFSL]=$(HDRFSL))
	$(info [PCHFSL]=$(PCHFSL))
	$(info [SRCFSL]=$(SRCFSL))
	$(info [OBJFSL]=$(OBJFSL))
	$(info [BINFSL]=$(BINFSL))
	$(info [MANFSL]=$(MANFSL))
	$(info [RSCFSL]=$(RSCFSL))
	$(info [==[target]==])
	$(info [===[locations]===])
	$(info [FTDLOC]=$(FTDLOC))
	$(info [===[directories]===])
	$(info [BINFTD]=$(BINFTD))
	$(info [MANFTD]=$(MANFTD))
	$(info [===[lists]===])
	$(info [BINFTL]=$(BINFTL))
	$(info [MANFTL]=$(MANFTL))
	$(info [=[build]=])
	$(info [==[compiler]==])
	$(info [CMAKER]=$(CMAKER))
	$(info [CFLAGS]=$(CFLAGS))
	$(info [==[linker]==])
	$(info [LMAKER]=$(LMAKER))
	$(info [LFLAGS]=$(LFLAGS))
	$(info [=[terminal]=])
	$(info [TERMSU]=$(TERMSU))
	$(info [TERMCO]=$(TERMCO))
	$(info [TERMCM]=$(TERMCM))
	$(info [TERMCP]=$(TERMCP))
	$(info [TERMRM]=$(TERMRM))
	$(info [TERMMV]=$(TERMMV))
	$(info [TERMMD]=$(TERMMD))
	$(info [TERMDB]=$(TERMDB))
	$(info [=[libraries]=])
	$(info [LIBDIR]=$(LIBDIR))
	$(info [LIBSET]=$(LIBSET))
	$(info [LIBUSE]=$(LIBUSE))
	$(info [LIBMOD]=$(LIBMOD))
	$(info [LIBSUF]=$(LIBSUF))
	$(info [LIBLIN]=$(LIBLIN))
	$(info [=[rules]=])
	$(info [build]=link binary file from object code compiled from source code)
	$(info [clean]=remove compiled object code and linked binary file)
	$(info [setup]=copy binary and manual files into the system)
	$(info [reset]=remove binary and manual files from the system)
	$(info [again]=clean and rebuild the project again)
	$(info [start]=build and run the binary file)
	$(info [rerun]=clean, rebuild and run the binary file with the shell)
	$(info [debug]=clean, rebuild and run the binary file with the debugger)
	$(info [print]=write this whole text)
print-head:
	@for lib in ${LIBUSE}; do ${MAKE} -C $(LIBDIR)/$$lib TYPE=SLL print; done
	$(info [[print]])

## source

$(HDRFSD)/%.$(HDRSUF):
	$(info "[header]=$@")

$(PCHFSD)/%.$(PCHSUF): $(HDRFSD)/%
	$(info "[pchead]=$@")
	$(CMAKER) $@ $^ $(CFLAGS)

$(SRCFSD)/%.$(SRCSUF): $(HDRFSD)/%.$(HDRSUF)
	$(info "[source]=$@")

$(OBJFSD)/%.$(OBJSUF): $(SRCFSD)/%.$(SRCSUF)
	$(info "[object]=$@")
	$(CMAKER) $@ $^ $(CFLAGS)

$(BINFSD)/%.$(BINSUF): $(OBJFSL)
	$(info "[source-binary]=$@")
	$(LMAKER) $@ $^ $(LFLAGS)

$(MANFSD)/%.$(MANSUF):
	$(info "[source-manual]=$@")

## target

$(BINFTD)/%: %.$(BINSUF)
	$(info "[target-binary]=$@")
	$(TERMCP) $< $@
	$(TERMCO) $@
	$(TERMCM) 744 $@

$(MANFTD)/%.$(MANSUF): %.$(MANSUF)
	$(info "[target-manual]=$@")
	$(TERMCP) $< $@
	$(TERMCM) 644 $@

# endof

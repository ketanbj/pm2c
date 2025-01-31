# Makefile

.DEFAULT_GOAL := all

JULIA ?= julia
DLEXT := $(shell $(JULIA) --startup-file=no -e 'using Libdl; print(Libdl.dlext)')

TARGET="PowerModelsCompiled"

PMBELIB_INCLUDES = $(TARGET)/include/julia_init.h $(TARGET)/include/libpowermodelscompiled.h
PMBE_PATH := $(TARGET)/lib/libpowermodelscompiled.$(DLEXT)

build-library: build/build.jl src/PowerModelsCompiled.jl
	$(JULIA) --startup-file=no --project=. -e 'using Pkg; Pkg.instantiate();'
	$(JULIA) --startup-file=no --project=build -e 'using Pkg; Pkg.instantiate(); include("build/build.jl")'

INCLUDE_DIR = $(TARGET)/include

build-c-test: 
	gcc ctest/direct-test.c -o ctest/pmbe-direct-test -I$(INCLUDE_DIR) -L$(TARGET)/lib -ljulia -lpowermodelscompiled
	gcc ctest/dlopen-test.c -o  ctest/dlopen-test -I$(INCLUDE_DIR)

all: build-library build-c-test

clean:
	$(RM) *~ *.o *.$(DLEXT)
	$(RM) -Rf $(TARGET)

.PHONY: build-library build-c-test clean all

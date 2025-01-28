# Makefile

.DEFAULT_GOAL := all

JULIA ?= julia
DLEXT := $(shell $(JULIA) --startup-file=no -e 'using Libdl; print(Libdl.dlext)')

TARGET="PowerModelsCompiled"

PMBELIB_INCLUDES = $(TARGET)/include/julia_init.h $(TARGET)/include/powermodelscompiled.h
PMBE_PATH := $(TARGET)/lib/libpowermodelscompiled.$(DLEXT)

build-library: build/build.jl src/PowerModelsCompiled.jl
	$(JULIA) --startup-file=no --project=. -e 'using Pkg; Pkg.instantiate(); Pkg.add("PackageCompiler"); Pkg.add("PowerModels"); Pkg.add("Ipopt"); Pkg.add("JSON"); Pkg.resolve()'
	$(JULIA) --startup-file=no --project=build -e 'using Pkg; Pkg.instantiate(); Pkg.add("PackageCompiler"); Pkg.add("PowerModels"); Pkg.add("Ipopt"); Pkg.add("JSON"); Pkg.resolve(); include("build/build.jl")'

INCLUDE_DIR = $(TARGET)/include

build-c-test: ctest/direct-test.c ctest/dlopen-test.c
	gcc ctest/direct-test.c -o ctest/pmbe-direct-test -I$(INCLUDE_DIR) -L$(TARGET)/lib -ljulia -lpowermodelscompiled
	gcc ctest/dlopen-test.c -o  ctest/dlopen-test -I$(INCLUDE_DIR)

all: build-library build-c-test

clean:
	$(RM) *~ *.o *.$(DLEXT)
	$(RM) -Rf $(TARGET)

.PHONY: build-library build-c-test clean all

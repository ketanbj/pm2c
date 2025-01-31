# pmbe2grid
Repository for PowerModels.jl based backend for Grid2Op

# current status
- dynamic library is generated
- dynamic library contains the symbols
- Testing dlopen / dlsym - ongoing 

# organization
- Makefile includes all the steps to compile the PoweModelsCompiled.jl wrappers 
- src: 
    - implementation  that export two C functions (also declared in build/powermodelscompiled.h) 
    - generate_precompile.j; tests the exported functions from Julia
    - additional_precompile.jl (if something needs to be done)
- build: includes package compiler scripts and headers
- ctest: two simple tests implemented in C to check sanity of generated dynamic library

# pre-requisites

- Install Julia 1.11.1
- Set PATH: 
```export PATH=<path to>/julia/bin:$PATH```

If you installed Julia from a downloaded dmg on mac, it looks something like this:

```export PATH=/Applications/Julia-1.11.app/Contents/Resources/julia/bin:$PATH```

# build

```git clone https://github.com/ketanbj/pmbe2grid.git```

```make```

Running make creates a folder PowerModelCompiled which contains library libpowemodelscompiled.dylib or libpowemodelscompiled.so and all julia libraries needed to run it

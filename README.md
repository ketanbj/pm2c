# pm2c
Repository for PowerModels.jl based backend dynamic library to be used to create a python-based backend for Grid2Op

# organization
- Makefile includes all the steps to compile the PoweModelsCompiled.jl wrappers 
- src: 
    - implementation  that export two C functions (also declared in build/powermodelscompiled.h) 
    - generate_precompile.j; tests the exported functions from Julia
    - additional_precompile.jl (if something needs to be done)
- build: includes package compiler scripts and headers
- ctest: two simple tests implemented in C to check the sanitythe of generated dynamic library

# pre-requisites

- Install Julia 1.11.1 or 1.11.2
- Set PATH: 
```export PATH=<path to>/julia/bin:$PATH```

If you installed Julia from a downloaded dmg on Mac, it looks something like this:

```export PATH=/Applications/Julia-1.11.app/Contents/Resources/julia/bin:$PATH```

If you are running on rogues gallery machines, loading the julia module will set up the PATH variable :

```module load julia/1.11.2```

# build

1. clone this repo: ```git clone https://github.com/ketanbj/pm2c.git```

2. Build using make: ```make```

This will create a folder PowerModulesCompiled containing the include, lib, libexec, share folder.

The library libpowemodelscompiled.dylib or libpowemodelscompiled.so and all julia libraries needed should be populated there.

# test

This will also build two test executables in the ctest directory: 

- direct-test: test to directly link with the generated library and execute basic functions like load_grid and solve_power_flow
- dlopen-test: test to open the library using dlopen and calling the same functions.

You can run the test with the following steps:

1. Set LIBRARY_PATH:
    - On Mac:
    ```export DYLD_FALLBACK_LIBRARY_PATH=<path-to>/julia/lib:<path-to>/julia/lib/julia:<path-to>/pm2c/PowerModelsCompiled/lib:$DYLD_FALLBACK_LIBRARY_PATH```
    - On Linux:
    ```export LD_LIBRARY_PATH=<path-to>/julia/lib/:<path-to>/julia/lib/julia:<path-to>/pm2c/PowerModelsCompiled/lib:$LD_LIBRARY_PATH```

2. Go to ctest directory:
   ```cd ctest```

3. run executable
   ```./direct-test```

   Sample output:
    ```
    Loading grid from case5.m[warn | PowerModels]: The last 5 generator cost records will be ignored due to too few generator records.
    [warn | PowerModels]: reversing the orientation of branch 6 (4, 3) to be consistent with other parallel branches
    [warn | PowerModels]: bus 3 has an unrecongized bus_type 0, updating to bus_type 2
    [warn | PowerModels]: the voltage setpoint on generator 4 does not match the value at bus 4
    [warn | PowerModels]: the voltage setpoint on generator 1 does not match the value at bus 1
    [warn | PowerModels]: the voltage setpoint on generator 5 does not match the value at bus 10
    [warn | PowerModels]: the voltage setpoint on generator 2 does not match the value at bus 1
    [warn | PowerModels]: the voltage setpoint on generator 3 does not match the value at bus 3
    [info | PowerModels]: removing 1 cost terms from generator 4: [4000.0, 0.0]
    [info | PowerModels]: removing 1 cost terms from generator 1: [1400.0, 0.0]
    [info | PowerModels]: removing 1 cost terms from generator 5: [1000.0, 0.0]
    [info | PowerModels]: removing 1 cost terms from generator 2: [1500.0, 0.0]
    [info | PowerModels]: removing 1 cost terms from generator 3: [3000.0, 0.0]
    Loaded grid from case5.m
    Loaded case5.m 1
    ```
    
   ```./dlopen-test```

   Sample output:
   ```
    Shared library loaded successfully
    c_load_grid function loaded successfully
    c_solve_power_flow function loaded successfully
    Loading grid from case5.m[warn | PowerModels]: The last 5 generator cost records will be ignored due to too few generator records.
    [warn | PowerModels]: reversing the orientation of branch 6 (4, 3) to be consistent with other parallel branches
    [warn | PowerModels]: bus 3 has an unrecongized bus_type 0, updating to bus_type 2
    [warn | PowerModels]: the voltage setpoint on generator 4 does not match the value at bus 4
    [warn | PowerModels]: the voltage setpoint on generator 1 does not match the value at bus 1
    [warn | PowerModels]: the voltage setpoint on generator 5 does not match the value at bus 10
    [warn | PowerModels]: the voltage setpoint on generator 2 does not match the value at bus 1
    [warn | PowerModels]: the voltage setpoint on generator 3 does not match the value at bus 3
    [info | PowerModels]: removing 1 cost terms from generator 4: [4000.0, 0.0]
    [info | PowerModels]: removing 1 cost terms from generator 1: [1400.0, 0.0]
    [info | PowerModels]: removing 1 cost terms from generator 5: [1000.0, 0.0]
    [info | PowerModels]: removing 1 cost terms from generator 2: [1500.0, 0.0]
    [info | PowerModels]: removing 1 cost terms from generator 3: [3000.0, 0.0]
    Loaded grid from case5.m
    c_load_grid result: 1
   ```

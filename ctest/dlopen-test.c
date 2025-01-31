#include <stdio.h>
#include <dlfcn.h>

typedef int (*c_load_grid_t)(char*);
typedef char* (*c_solve_power_flow_t)(char*);

int main() {
    void *handle;
    char *error;

    // Open the shared library
    handle = dlopen("libpowermodelscompiled.dylib", RTLD_NOW);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    // Clear any existing error
    dlerror();
    printf("Shared library loaded successfully\n");

    // Load the c_load_grid function
    c_load_grid_t ptr_c_load_grid = NULL;
    ptr_c_load_grid = (c_load_grid_t) dlsym(handle, "c_load_grid");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        dlclose(handle);
        return 1;
    }
    if(ptr_c_load_grid) printf("c_load_grid function loaded successfully\n" );
    // Load the c_solve_power_flow function
    c_solve_power_flow_t ptr_c_solve_power_flow = NULL;
    ptr_c_solve_power_flow = (c_solve_power_flow_t) dlsym(handle, "c_solve_power_flow");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        dlclose(handle);
        return 1;
    }
    if(ptr_c_solve_power_flow) printf("c_solve_power_flow function loaded successfully\n" );
    // Call the c_load_grid function
    int load_result = ptr_c_load_grid("case5.m");
    printf("c_load_grid result: %d\n", load_result);

    // Call the c_solve_power_flow function
    char* solve_result = ptr_c_solve_power_flow("case5.m");
    printf("c_solve_power_flow result: %s\n", solve_result);

    // Free the result from c_solve_power_flow if necessary
    // free(solve_result); // Uncomment if the result needs to be freed

    // Close the shared library
    dlclose(handle);

    return 0;
}
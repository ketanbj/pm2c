#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *handle;
    char *error;

    // Open the shared library
    handle = dlopen("libpowermodelscompiled.dylib", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    // Clear any existing error
    dlerror();

    // Load the c_load_grid function
    int (*c_load_grid)(const char*);
    *(void **) (&c_load_grid) = dlsym(handle, "c_load_grid");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        dlclose(handle);
        return 1;
    }

    // Load the c_solve_power_flow function
    char* (*c_solve_power_flow)(const char*);
    *(void **) (&c_solve_power_flow) = dlsym(handle, "c_solve_power_flow");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        dlclose(handle);
        return 1;
    }

    // Call the c_load_grid function
    const char* input_data = "case5.m";
    int load_result = c_load_grid(input_data);
    printf("c_load_grid result: %d\n", load_result);

    // Call the c_solve_power_flow function
    char* solve_result = c_solve_power_flow(input_data);
    printf("c_solve_power_flow result: %s\n", solve_result);

    // Free the result from c_solve_power_flow if necessary
    // free(solve_result); // Uncomment if the result needs to be freed

    // Close the shared library
    dlclose(handle);

    return 0;
}
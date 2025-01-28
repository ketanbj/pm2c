#include <stdio.h>

#include "julia_init.h"
#include "powermodelscompiled.h"

int main(int argc, char *argv[])
{
    init_julia(argc, argv);

    int status  = c_load_grid("case5.m");
    printf("Loaded case5.m %d\n",status);

    char* json_out = c_solve_power_flow("case5.m");
    
    printf("Output:\n%s\n", json_out);
    printf("Solved power flow\n");


    shutdown_julia(0);
    return 0;
}
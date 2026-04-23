#include <stdio.h>
#include <stdlib.h>
#include "os.h"

int OS_TYPE = 0;

int fetch_OS_type () { 
    //Checks for windows systems.
    #ifdef _WIN32 
    OS_TYPE = 1;
    return OS_TYPE;

    //Checks for linux systems
    #elif __linux__
    OS_TYPE = 2;
    return OS_TYPE;

    //Checks for BSD systems
    #elif BSD
    OS_TYPE = 3;
    return OS_TYPE;

    //Checks for MACOS systems
    #elif TARGET_OS_MAC
    OS_TYPE 4;
    return OS_TYPE;

    #else
    //Returns 0 if the OS doesnt fit into mainstream catagories.
    OS_TYPE = 0;
    return OS_TYPE;

    #endif
    return OS_TYPE;

}




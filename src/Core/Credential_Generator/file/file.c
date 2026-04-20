//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "file.h"

bool check_file_validity (char full_path[512]) {

//Checks for file presence
FILE *fileptr;
fileptr = fopen(full_path, "r");

if (fileptr == NULL) {
    return false;
}

//checks if file has data.
fseek(fileptr, 0, SEEK_END);
long int file_end = ftell(fileptr);

if (file_end <= 0) {
    fclose(fileptr);
    return false;
} else {
    fclose(fileptr);
    return true;
}

}

long int check_file_size (char full_path[512]) {

//Checks for file presence
FILE *fileptr;
fileptr = fopen(full_path, "r");

if (fileptr == NULL) {
    long int err = 0;
    return err;
}

//Finds and return file size.
fseek(fileptr, 0, SEEK_END);
long int file_end = ftell(fileptr);

return file_end;

}


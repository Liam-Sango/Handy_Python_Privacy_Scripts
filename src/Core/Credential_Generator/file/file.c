//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "file.h"

#include "../random/random.h"


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

char* get_random_file_line (char full_path[512]) {
    //Allocates memory to store our random file line.
    char* file_line;
    file_line = calloc(512, 1);

    if (file_line == NULL) {
        return NULL;
    }

    //Checks that the target file is valid with present data.
    bool file_valid = check_file_validity(full_path);

    if (file_valid == false) {
        return NULL;
    }

    //Opens the target file
    FILE *fileptr;
    fileptr = fopen(full_path, "r");

    //Fetches the size of the target file
    long int file_size = check_file_size(full_path);

    //Navigates to the start of the file
    fseek(fileptr, 0, SEEK_SET);


    //Generates a random line position
    unsigned long long int temp_line_position = Generate_random_number(0, file_size);

    if (temp_line_position > 2147483647) {
        return NULL;
    }

    long int random_line_position = temp_line_position;

    //Navigates to the random line.
    fseek(fileptr, random_line_position, SEEK_CUR);

    //Reads the randomly placed file line.
    fgets(file_line, 512, fileptr);
    fclose(fileptr);

    return file_line;
}


#ifndef FILE_H
#define FILE_H

//Checks to see if a file is present and has data.
bool check_file_validity (char full_path[512]);

//Returns a files size as a long int.
long int check_file_size (char full_path[512]);

#endif // FILE_H

#ifndef CREDENTIAL_GENERATOR_RANDOM_H
#define CREDENTIAL_GENERATOR_RANDOM_H

#include <wchar.h>
#include <unicode/uchar.h>

//Generates random bytes 
int Generate_raw_random_bytes(int Gen_amt, unsigned char* rand_buffer);

//Generates random numbers between a user defined range
unsigned long long int Generate_random_number(int lower_range, int upper_range);

//Generates random UTF8 Unicode strings between a user defined range
char* Generate_Random_UTF8_string(int string_length, UChar32 Lower_Char_Limit, UChar32 Upper_Char_Limit);

#endif // CREDENTIAL_GENERATOR_RANDOM_H

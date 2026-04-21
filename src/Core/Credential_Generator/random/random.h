#ifndef CREDENTIAL_GENERATOR_RANDOM_H
#define CREDENTIAL_GENERATOR_RANDOM_H

//Generates securely random raw bytes. (Without any conversion or processing)
int Generate_raw_random_bytes(int Gen_amt, unsigned char* rand_buffer);

//Generates a cryptographically random number between a predefined range
unsigned long long int Generate_random_number(int lower_range, int upper_range);

//Generates a cryptographically random string based on a user defined character set
char* Generate_Random_string (int length, char* char_list);

#endif // CREDENTIAL_GENERATOR_RANDOM_H

#ifndef RANDOM_H
#define RANDOM_H

//Generates securely random raw bytes. (Without any conversion or processing)
int Generate_raw_random_bytes(int Gen_amt, unsigned char rand_buffer[Gen_amt]);

//generates a large random number
unsigned long long int Generate_random_number(int lower_range, int upper_range);

//Generates a random number between a predefined range

#endif // RANDOM_H
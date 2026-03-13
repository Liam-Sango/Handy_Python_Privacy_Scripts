#ifndef RANDOM_H
#define RANDOM_H

//Generates securely random raw bytes. (Without any conversion or processing)
int Generate_raw_random_bytes(int Gen_amt, unsigned char rand_buffer[Gen_amt]);

//generates an array of random numbers for use in credential generation (Unfinished)
int Generate_random_numbers(int Gen_amt, unsigned char rand_buffer[Gen_amt]);

#endif // RANDOM_H
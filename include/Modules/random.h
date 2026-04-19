#ifndef RANDOM_H
#define RANDOM_H

//Generates securely random raw bytes. (Without any conversion or processing)
int Generate_raw_random_bytes(int Gen_amt, unsigned char rand_buffer[Gen_amt]);

//Generates a random number between a predefined range
unsigned long long int Generate_random_number(int lower_range, int upper_range);

//Generates a random phrase from a file with a filelist
char* Generate_Rand_Phrase (int Phrase_length);

//Generates a random string from a predefined charset
char* Generate_Rand_String (int String_length);

#endif // RANDOM_H
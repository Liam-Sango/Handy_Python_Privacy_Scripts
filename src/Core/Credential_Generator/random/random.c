//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <openssl/rand.h>
#include <openssl/err.h>

#include "random.h" 


//Global variables


//Functions
int Generate_raw_random_bytes(int Gen_amt, unsigned char* rand_buffer) {
    //Ensures cryptographic algorithms and error strings are available.
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    // Check if RNG is properly seeded
    if (RAND_poll() != 1) {
        return 1;
    }

    //Generates random bytes
    int result = RAND_bytes(rand_buffer, Gen_amt);
    return 0;
}


unsigned long long int Generate_random_number(int lower_range, int upper_range) {
    //Assigns mathmatical variables.
    unsigned long long int Generator_limit = 4294967296;
    unsigned long long int Target_Range = upper_range - lower_range + 1;
    unsigned long long int Modulo_Limit = Generator_limit - (Generator_limit % Target_Range);

    
    unsigned long long int Final_number = 0;
    unsigned long long int Generated_Number = 0;   

    //Error checking
    if (lower_range >= upper_range) {
        return 1;
    }

    bool Generated_num_valid = false;
    while (Generated_num_valid == false) { 
        int status;

        // Generates random bytes.
        unsigned char raw_buffer[4];
        status = Generate_raw_random_bytes(4, raw_buffer);

        // Check for generation failure.
        if (status == 1) {
           return 1; 
        }
    
        //uses byte shifting to calculate the decimal result of our random bytes.
        Generated_Number = (raw_buffer[0] << 24) | (raw_buffer[1] << 16) | (raw_buffer[2] << 8) | raw_buffer[3];


        //Checks if the final number contains modulo bias, Regenrates 
        if (Generated_Number > Modulo_Limit) {
            Generated_num_valid = false;
            continue;
        } else {
            Generated_num_valid = true;
        }  
    }

    Final_number = (Generated_Number % Target_Range) + lower_range;

  return Final_number;
}

char* Generate_Random_string (int length, char* char_list) {
    return NULL;
}
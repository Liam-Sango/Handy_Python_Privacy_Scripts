#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/rand.h>
#include <openssl/err.h>

#include "../../include/Modules/random.h" 

int Generate_raw_random_bytes(int Gen_amt, unsigned char rand_buffer[Gen_amt]) {
    //Ensures cryptographic algorithms and error strings are available.
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    // Check if RNG is properly seeded
    if (RAND_poll() != 1) {
        unsigned char seed[16] = {0};  // Using zeroed seed as fallback
        RAND_seed(seed, sizeof(seed));
    }

    //Generates random bytes
    int result = RAND_bytes(rand_buffer, Gen_amt);
    return 0;
};

//Unfinished
int Generate_random_numbers(int Gen_amt, unsigned char rand_buffer[Gen_amt]) {
    //Ensures cryptographic algorithms and error strings are available.
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    // Check if RNG is properly seeded
    if (RAND_poll() != 1) {
        unsigned char seed[16] = {0};  // Using zeroed seed as fallback
        RAND_seed(seed, sizeof(seed));
    }

    //Generates random bytes
    int result = RAND_bytes(rand_buffer, Gen_amt);
    return 0;
};
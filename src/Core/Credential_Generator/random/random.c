//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <wchar.h>
#include <locale.h>  

#include <openssl/rand.h>
#include <openssl/err.h>

#include "random.h" 


//Global variables


//Functions
int Generate_raw_random_bytes(int Gen_amt, unsigned char* rand_buffer) {
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    if (RAND_poll() != 1) {
        return 1;
    }

    int result = RAND_bytes(rand_buffer, Gen_amt);
    return 0;
}


unsigned long long int Generate_random_number(int lower_range, int upper_range) {
    unsigned long long int Generator_limit = 4294967296;
    unsigned long long int Target_Range = upper_range - lower_range + 1;
    unsigned long long int Modulo_Limit = Generator_limit - (Generator_limit % Target_Range);

    unsigned long long int Final_number = 0;
    unsigned long long int Generated_Number = 0;

    if (lower_range >= upper_range) {
        return 1;
    }

    bool Generated_num_valid = false;
    while (Generated_num_valid == false) {
        int status;
        unsigned char raw_buffer[4];

        status = Generate_raw_random_bytes(4, raw_buffer);
        if (status == 1) {
            return 1;
        }

        Generated_Number = (raw_buffer[0] << 24) | (raw_buffer[1] << 16) | (raw_buffer[2] << 8) | raw_buffer[3];

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

wchar_t* Generate_Random_UTF8_string (int string_length, int lower_char_limit, int upper_char_limit, int char_list_length) {
    setlocale(LC_ALL, "");

    return NULL;
}
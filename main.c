#include <stdio.h>
#include <stdlib.h>

#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/evp.h>

#include "include/Modules/random.h"



int main() {  
    int lower = 1;
    int upper = 1000;
    printf("NUMBERS:\n");
    for (int x = 0; x < 10; x++) {
        unsigned long long int number = Generate_random_number(lower, upper);
        printf(" %u\n", number);
    }

}
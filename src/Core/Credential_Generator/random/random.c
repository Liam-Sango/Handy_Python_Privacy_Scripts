//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <wchar.h>
#include <locale.h> 

#include <openssl/rand.h>
#include <openssl/err.h>

#include <unicode/utypes.h>
#include <unicode/ustring.h>
#include <unicode/uchar.h>
#include <unicode/utf8.h>

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

//TODO



char* Generate_Random_UTF8_string (int string_length, UChar32 Lower_Char_Limit, UChar32 Upper_Char_Limit) {

//Validate user defined code point range (Ensuring blacklisted characters are disabled)
bool User_range_invalid = false;

// 1. Basic sanity limits (Max Unicode is 0x10FFFF) and logic checks
if (Lower_Char_Limit > Upper_Char_Limit || Upper_Char_Limit > 0x10FFFF) {
    User_range_invalid = true;
}
// 2. Overlap with C0 Control Characters (0x0000 to 0x001F)
else if (Lower_Char_Limit <= 0x001F && Upper_Char_Limit >= 0x0000) {
    User_range_invalid = true;
}
// 3. Overlap with C1 Control Characters (0x007F to 0x009F)
else if (Lower_Char_Limit <= 0x009F && Upper_Char_Limit >= 0x007F) {
    User_range_invalid = true;
}
// 4. Overlap with Surrogates (0xD800 to 0xDFFF)
else if (Lower_Char_Limit <= 0xDFFF && Upper_Char_Limit >= 0xD800) {
    User_range_invalid = true;
}
// 5. Overlap with Bi-Directional Text Control Characters (LRE, RLE, etc.)
else if (Lower_Char_Limit <= 0x202E && Upper_Char_Limit >= 0x202A) {
    User_range_invalid = true;
}
else if (Lower_Char_Limit <= 0x2069 && Upper_Char_Limit >= 0x2066) {
    User_range_invalid = true;
}
// 6. Overlap with Zero-Width Characters and BOMs
else if (Lower_Char_Limit <= 0x200D && Upper_Char_Limit >= 0x200B) {
    User_range_invalid = true;
}
else if (Lower_Char_Limit <= 0x2060 && Upper_Char_Limit >= 0x2060) {
    User_range_invalid = true;
}
else if (Lower_Char_Limit <= 0xFEFF && Upper_Char_Limit >= 0xFEFF) {
    User_range_invalid = true;
}
// 7. Overlap with guaranteed Unicode Non-characters (0xFDD0 to 0xFDEF)
else if (Lower_Char_Limit <= 0xFDEF && Upper_Char_Limit >= 0xFDD0) {
    User_range_invalid = true;
}
// 8. Overlap with Tags Block
else if (Lower_Char_Limit <= 0xE007F && Upper_Char_Limit >= 0xE0000) {
    User_range_invalid = true;
}

// Check if lower or upper bound itself is a non-character (FFFE/FFFF in any plane)
bool lower_is_nonchar = ((Lower_Char_Limit & 0xFFFE) == 0xFFFE);
bool upper_is_nonchar = ((Upper_Char_Limit & 0xFFFE) == 0xFFFE);

// Check if range spans any non-character (FFFE or FFFF in planes 0-16)
bool spans_nonchar = false;
for (int plane = 0; plane <= 16; plane++) {
    UChar32 base = (UChar32)plane * 0x10000;
    if (Lower_Char_Limit <= base + 0xFFFE && base + 0xFFFE <= Upper_Char_Limit) {
        spans_nonchar = true;
        break;
    }
    if (Lower_Char_Limit <= base + 0xFFFF && base + 0xFFFF <= Upper_Char_Limit) {
        spans_nonchar = true;
        break;
    }
}

if (lower_is_nonchar || upper_is_nonchar || spans_nonchar) {
    User_range_invalid = true;
}

// Proceed with generation only if (User_range_invalid == false)
if (User_range_invalid == true) {
    return NULL;
}

//Allocates our string buffer & Additional variables
int32_t capacity = (string_length * 4) + 1;
char *buffer = malloc(capacity);
if (!buffer) return NULL;
int32_t index = 0;
bool is_error = false;


// FOR LOOP (String length in chars.)
for (int x = 0; x < string_length; x++) {

//Generate a valid code point
UChar32 current_char = Generate_random_number(Lower_Char_Limit, Upper_Char_Limit);

//Validate the generated code point
if (current_char == 1){
    free (buffer);
    return NULL;
}
if (current_char >= Lower_Char_Limit && current_char <= Upper_Char_Limit) {
} else {
    free(buffer);
    return NULL;
}

if (current_char >= 0xD800 && current_char <= 0xDFFF) {
    free(buffer);
    return NULL;
}

//Add the UTF8 char to the finished string
U8_APPEND (buffer, index, capacity, current_char, is_error);

if (is_error == true) {
    free(buffer);
    return NULL;
}
}

//Return the finished string.
buffer[index] = '\0';  // Null-terminate
return buffer;  // Return the same buffer you've been building

}

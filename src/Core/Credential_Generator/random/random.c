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
bool User_Range_Validity = false;

// 1. Basic sanity limits (Max Unicode is 0x10FFFF) and logic checks
if (Lower_Char_Limit > Upper_Char_Limit || Upper_Char_Limit > 0x10FFFF) {
    User_Range_Validity = true;
}
// 2. Overlap with C0 Control Characters (0x0000 to 0x001F)
else if (Lower_Char_Limit <= 0x001F && Upper_Char_Limit >= 0x0000) {
    User_Range_Validity = true;
}
// 3. Overlap with C1 Control Characters (0x007F to 0x009F)
else if (Lower_Char_Limit <= 0x009F && Upper_Char_Limit >= 0x007F) {
    User_Range_Validity = true;
}
// 4. Overlap with Surrogates (0xD800 to 0xDFFF)
else if (Lower_Char_Limit <= 0xDFFF && Upper_Char_Limit >= 0xD800) {
    User_Range_Validity = true;
}
// 5. Overlap with Bi-Directional Text Control Characters (LRE, RLE, etc.)
else if (Lower_Char_Limit <= 0x202E && Upper_Char_Limit >= 0x202A) {
    User_Range_Validity = true;
}
else if (Lower_Char_Limit <= 0x2069 && Upper_Char_Limit >= 0x2066) {
    User_Range_Validity = true;
}
// 6. Overlap with Zero-Width Characters and BOMs
else if (Lower_Char_Limit <= 0x200D && Upper_Char_Limit >= 0x200B) {
    User_Range_Validity = true;
}
else if (Lower_Char_Limit <= 0x2060 && Upper_Char_Limit >= 0x2060) {
    User_Range_Validity = true;
}
else if (Lower_Char_Limit <= 0xFEFF && Upper_Char_Limit >= 0xFEFF) {
    User_Range_Validity = true;
}
// 7. Overlap with guaranteed Unicode Non-characters (0xFDD0 to 0xFDEF)
else if (Lower_Char_Limit <= 0xFDEF && Upper_Char_Limit >= 0xFDD0) {
    User_Range_Validity = true;
}
// 8. Overlap with Tags Block
else if (Lower_Char_Limit <= 0xE007F && Upper_Char_Limit >= 0xE0000) {
    User_Range_Validity = true;
}
// 9. Overlap with Non-characters ending in FFFE or FFFF on ANY plane
else if (
    (Lower_Char_Limit >> 16) != (Upper_Char_Limit >> 16) || 
    (Lower_Char_Limit & 0xFFFF) >= 0xFFFE || 
    (Upper_Char_Limit & 0xFFFF) >= 0xFFFE
) {
    User_Range_Validity = true;
}

// Proceed with generation only if (User_Range_Validity == false)
if (User_Range_Validity = true) {
    return NULL;
}




// FOR LOOP (String length in chars.)
//Generate a valid code point
//Validate the generated code point
//Encode the generated code point to UTF8 
//Add the UTF8 char to the fnished string

//Return the finished string.
}

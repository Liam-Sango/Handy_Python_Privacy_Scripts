#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "src/Core/Credential_Generator/random/random.h"
#include "src/Core/Credential_Generator/file/file.h"

static char* trim_whitespace(char* str) {
	if (!str) return NULL;

	char* end;
	while (isspace((unsigned char)*str)) str++;
	if (*str == '\0') return str;

	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) end--;
	*(end + 1) = '\0';

	return str;
}

int main() {
//Main CLI will go here.
}

//Phrase generator, UTF8 string generator, Random number generator
//FORMAT: Random_phrase_1, Random_Phrase_2, Random_number
char* Username_generator() {
	char* word1 = NULL;
	char* word2 = NULL;
	char* username = NULL;

	word1 = get_random_UTF8_file_line("Files/username_word_list.txt");
	if (!word1) return NULL;
	trim_whitespace(word1);

	word2 = get_random_UTF8_file_line("Files/username_word_list.txt");
	if (!word2) { free(word1); return NULL; }
	trim_whitespace(word2);

	unsigned long long int number = Generate_random_number(0, 9999);

	size_t total_len = strlen(word1) + strlen(word2) + 20;
	username = malloc(total_len);
	if (!username) { free(word1); free(word2); return NULL; }

	snprintf(username, total_len, "%s_%s_%llu", word1, word2, number);

	free(word1);
	free(word2);

	return username;
}

// UTF8 string Generator
//FORMAT: Random_String (Defined char set)
char* password_generator() {
	int password_length = 20;
	UChar32 lower_limit = 0x21;
	UChar32 upper_limit = 0x7E;

	char* password = Generate_Random_UTF8_string(password_length, lower_limit, upper_limit);
	return password;
}

// Phrase generator
//FORMAT: Random_phrase
void Passphrase_generator () {
    return 0;
}

// Phrase generator
// FORMAT: Random_phrase_1, Random_phrase_2, Random_phrase_3
void Full_Name_generator () {
    return 0;
}

//Random Number generator
//FORMAT: Random number
void date_time_Generator () {
    return 0;
}
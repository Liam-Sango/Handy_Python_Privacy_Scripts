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

char* Username_generator();
char* password_generator();
char* Passphrase_generator();
char* Full_Name_generator();
char* date_time_Generator();

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
char* Passphrase_generator() {
	int phrase_word_count = 6;

	char* phrase = Generate_Random_Phrase("Files/passphrase_list.txt", phrase_word_count);
	if (!phrase) return NULL;

	char* trimmed = trim_whitespace(phrase);
	if (trimmed != phrase) {
		size_t len = strlen(trimmed) + 1;
		char* result = malloc(len);
		if (result) {
			memcpy(result, trimmed, len);
		}
	return phrase;
}
	return phrase;
}

// Phrase generator
// FORMAT: Random_phrase_1, Random_phrase_2, Random_phrase_3
char* Full_Name_generator() {
	char* first = NULL;
	char* middle = NULL;
	char* surname = NULL;
	char* full_name = NULL;

	first = get_random_UTF8_file_line("Files/First_names.txt");
	if (!first) return NULL;
	trim_whitespace(first);

	middle = get_random_UTF8_file_line("Files/Middle_name.txt");
	if (!middle) { free(first); return NULL; }
	trim_whitespace(middle);

	surname = get_random_UTF8_file_line("Files/Surname_list.txt");
	if (!surname) { free(first); free(middle); return NULL; }
	trim_whitespace(surname);

	size_t total_len = strlen(first) + strlen(middle) + strlen(surname) + 4;
	full_name = malloc(total_len);
	if (!full_name) { free(first); free(middle); free(surname); return NULL; }

	snprintf(full_name, total_len, "%s %s %s", first, middle, surname);

	free(first);
	free(middle);
	free(surname);

	return full_name;
}

//Random Number generator
//FORMAT: Random number
char* date_time_Generator() {
	unsigned long long int year = Generate_random_number(1970, 2026);
	unsigned long long int month = Generate_random_number(1, 12);
	unsigned long long int day = Generate_random_number(1, 28);
	unsigned long long int hour = Generate_random_number(0, 23);
	unsigned long long int minute = Generate_random_number(0, 59);
	unsigned long long int second = Generate_random_number(0, 59);

	char* datetime = malloc(20);
	if (!datetime) return NULL;

	snprintf(datetime, 20, "%04llu-%02llu-%02llu %02llu:%02llu:%02llu",
		year, month, day, hour, minute, second);

	return datetime;
}
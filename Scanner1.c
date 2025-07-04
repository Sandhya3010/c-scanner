#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to check if the character is a whitespace
int is_space(char ch) {
    if (ch == ' ' || ch == '\t' || ch == '\n')
        return 1; // It's a space character
    return 0;
}

// Function to check if the character is an alphabet letter
int is_alphabet(char ch) {
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        return 1; // It's a letter
    return 0;
}

// Function to check if the character is a digit
int is_digit(char ch) {
    if (ch >= '0' && ch <= '9')
        return 1; // It's a number
    return 0;
}

// Function to scan and print tokens from the input
void gettoken(char program_input[]) {
    int i = 0;
    int length = strlen(program_input);

    while (i < length) {
        if (is_space(program_input[i])) {
            i++; // Skip spaces, tabs, newlines
            continue;
        }

        if (is_alphabet(program_input[i])) {
            char word[100] = {0}; // Buffer to store the word
            int index = 0;

            while (i < length && is_alphabet(program_input[i])) {
                word[index++] = program_input[i];
                i++;
            }
            word[index] = '\0'; // End the string
            printf("%s tokword\n", word);
        }

        else if (is_digit(program_input[i])) {
            char number[100] = {0}; // Buffer to store the number
            int index = 0;

            while (i < length && is_digit(program_input[i])) {
                number[index++] = program_input[i];
                i++;
            }
            number[index] = '\0'; // End the string
            printf("%s toknumber\n", number);
        }

        else {
            // Any other character is treated as an operator
            printf("%c tokop\n", program_input[i]);
            i++;
        }
    }
}

int main() {
    char line[200];
    char program_input[10000] = ""; // Buffer to hold the entire input

    printf("Enter your code (press Enter on an empty line to finish input):\n");

    while (fgets(line, sizeof(line), stdin)) {
        if (strcmp(line, "\n") == 0) // Check for empty line to stop input
            break;
        strcat(program_input, line); // Append the line to the input
    }

    gettoken(program_input); // Start tokenizing the input
    return 0;
}

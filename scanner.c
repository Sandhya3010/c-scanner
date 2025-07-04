#include <stdio.h>
#include <ctype.h>

void gettoken(FILE *file);

int main() {
    FILE *file = fopen("input.txt", "r"); // input.txt is your source code file
    if (file == NULL) {
        printf("Cannot open file.\n");
        return 1;
    }

    gettoken(file);

    fclose(file);
    return 0;
}

void gettoken(FILE *file) {
    char ch;

    while ((ch = fgetc(file)) != EOF) { // Read character by character

        // Skip spaces and new lines
        if (isspace(ch)) {
            continue;
        }

        // If the token starts with a letter, it’s a word
        if (isalpha(ch)) {
            char word[100];
            int i = 0;

            word[i++] = ch;

            // Keep reading letters or digits
            while (isalnum(ch = fgetc(file))) {
                word[i++] = ch;
            }
            word[i] = '\0';

            printf("%s\ttokword\n", word);

            // If we read a non-alphanumeric character, put it back
            ungetc(ch, file);
        }

        // If the token starts with a digit, it’s a number
        else if (isdigit(ch)) {
            char number[100];
            int i = 0;

            number[i++] = ch;

            // Keep reading digits
            while (isdigit(ch = fgetc(file))) {
                number[i++] = ch;
            }
            number[i] = '\0';

            printf("%s\ttoknumber\n", number);

            ungetc(ch, file);
        }

        // Otherwise, it's a single-character operator or symbol
        else {
            printf("%c\ttokop\n", ch);
        }
    }
}

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define SIZE(x) (sizeof(x) / sizeof(x[0]))


int index_of_substr(char *buf, char *substr)
{
    int substr_len = strlen(substr);
    for (int i = 0; i < strlen(buf); i++) {
        if (buf[i] == substr[0]) {
            if (!strncmp(&buf[i], substr, substr_len))
                return i;
        }
    }
    return -69;
}

// One pass at replacing the (ordinal) first number
// in words to its digit form
// returns 1 if the buffer was changed
void num_in_words_to_digits(char *buf)
{
    char *numbers_in_words[] = {
         "one",  "two"  ,  "three",  "four",  "five",
         "six",  "seven",  "eight",  "nine", 
    };

    char *substr;

    for (int i = 0; i < SIZE(numbers_in_words); i++) {
        if (strstr(buf, numbers_in_words[i]) != NULL)  {
            substr = numbers_in_words[i];
            int x = 0;
            while (x > -1) { 
                x = index_of_substr(buf, substr);
                buf[x+1] = (char)(i + '1');
            }
        }
    }
}

int get_digits(const char *buf)
{
//    printf("pf -> %s", buf);
    char number_buffer[16] = {'\0'};
    int j = 0;

    for (int i = 0; buf[i] != '\0'; i++) {
        if (isdigit(buf[i])) {
            number_buffer[j++] = buf[i];
        }
    }
    number_buffer[j] = '\0';

    int number = -1;
    number = ((int)number_buffer[0] - '0') * 10;
    number += (int)number_buffer[j-1] - '0';

    return number;
}

int main(void)
{
    static const char *filename = "input.txt";
    FILE *file = fopen(filename, "r");

    char buf_part_two[80];
    char buf[80];
    int result_pt_2 = 0;
    int result_pt_1 = 0;

    while (fgets(buf_part_two, 80, file)) {
        strcpy(buf, buf_part_two);
        result_pt_1 += get_digits(buf);

        num_in_words_to_digits(buf_part_two);
        buf[strlen(buf)-1] = '\0';

        result_pt_2 += get_digits(buf_part_two);
    }
    printf("%d <- Result Part 1 (%s)\n", result_pt_1, filename);
    printf("%d <- Result Part 2 (%s)\n", result_pt_2, filename);
    return 0;
}

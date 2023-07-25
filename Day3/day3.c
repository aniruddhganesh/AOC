#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // toupper

#define MAX_SIZE 300

int item_priority(char ch) {
    int priority = 0;

    if (toupper(ch) == ch) {
        priority = (ch - ('A' - 1)) + 26;
    }
    else {
        priority = (ch - ('a' - 1));
    }
    return priority;
}

void str_split_half(char *buffer, int sizeof_half, char *str1, char *str2)
{
    strncpy(str1, buffer, sizeof_half+1); // Split first half
    str1[sizeof_half] = '\0';
    strncpy(str2, buffer + sizeof_half, sizeof_half); // Split second half
    str2[sizeof_half] = '\0';
}

// Checks 2 strings
int check_matching_char(char *str1, char *str2) {
    char common_char = '\0'; // Initialize the common character as null character '\0'

    for (int i = 0; i < MAX_SIZE; i++) {
        if (strchr(str2, str1[i])) { // str[i] char found in str[2]
            common_char = str1[i];
            break; // Break the loop once the common character is found
        }
    }
    return common_char;
}

// Checks 3 strings
char check_common(char strings[3][MAX_SIZE]) {
    char match_char;

    for (int i = 0; strings[0][i] != '\0'; i++) {
        match_char = strings[0][i];
        
        if (strchr(strings[1], match_char) && strchr(strings[2], match_char)) {
            return match_char;
        }

    }
    return '\0';
}


int part1(FILE *fp) 
{
    char buffer[MAX_SIZE];
    char matching_char;
    char compartment_1[MAX_SIZE / 2], compartment_2[MAX_SIZE/2];
    int sizeof_half, sum_priority_pt1 = 0;
   
    while (fgets(buffer, MAX_SIZE, fp) != NULL) {
        sizeof_half = (strlen(buffer) / 2);
        str_split_half(buffer, sizeof_half, compartment_1, compartment_2);
        
        matching_char = check_matching_char(compartment_1, compartment_2);
        sum_priority_pt1 += item_priority(matching_char);
    }

    return sum_priority_pt1;
}

int part2(FILE *fp) {
    char buffers[3][MAX_SIZE] = {0};
    int sum_priority = 0;

    while(1) {
        for (int i = 0; i < 3; i++) {
            if (fgets(buffers[i], MAX_SIZE, fp) == NULL)
                goto double_break;
        }
        char common_char = check_common(buffers);
        sum_priority += item_priority(common_char);
    }
double_break:
    return sum_priority;
}

int main(void)
{
    FILE *fp = fopen("./day3.txt", "r");

    printf("%.4d <- Part: 1\n", part1(fp)); // Part 1 solution
    rewind(fp);
    printf("%.4d <- Part: 2\n", part2(fp));

    fclose(fp);
    return 0;
}

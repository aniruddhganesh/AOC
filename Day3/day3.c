#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // toupper

#define MAX_SIZE 50

void str_split_half(char *buffer, int sizeof_half, char *str1, char *str2)
{
    strncpy(str1, buffer, sizeof_half+1); // Split first half
    str1[sizeof_half] = '\0';
    strncpy(str2, buffer + sizeof_half, sizeof_half); // Split second half
    str2[sizeof_half] = '\0';
}

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

int main(void)
{
    FILE *fp = fopen("./day3.txt", "r");
    char buffer[MAX_SIZE];
    char matching_char;
    char compartment_1[MAX_SIZE / 2], compartment_2[MAX_SIZE/2];
    int sizeof_half, sum_priority = 0;
   
    while (fgets(buffer, MAX_SIZE, fp) != NULL) {
        sizeof_half = (strlen(buffer) / 2);
        str_split_half(buffer, sizeof_half, compartment_1, compartment_2);
        
        matching_char = check_matching_char(compartment_1, compartment_2);
        sum_priority += item_priority(matching_char);
        printf("%c \t %s %s\n", matching_char, compartment_1, compartment_2);
    }
    printf("\n --> %d\n", sum_priority);
    fclose(fp);
    return 0;
}

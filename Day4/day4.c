#include <stdio.h>

#define PART_TWO

int is_subset(int *a, int *b)
{
    /* Case A subset of B */
    if (a[0] >= b[0] && b[1] >= a[1]) {
        return 1;
    } 
    /* Case B subset of A */
    if (a[0] <= b[0] && b[1] <= a[1]) {
        return 1;
    }
    return 0;
}

int is_overlap(int *a, int *b)
{
    /* Check A over B */
    if (a[0] <= b[0] && a[1] >=  b[0]) {
        return 1;
    }
    /* Check B over A */
    if (b[0] <= a[0] && b[1] >=  a[0]) {
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    FILE *data;
    if (!argv[1]) {
        data = fopen("data.txt", "r");
    } else {
        data = stdin;
    }

    char buffer[80] = {0};
    int a[2], b[2];

    while(fgets(buffer, 80, data)) {
        sscanf(buffer, "%d-%d,%d-%d", &a[0], &a[1], &b[0], &b[1]);

        printf("%d-%d .. %d-%d", a[0], a[1], b[0], b[1]);

#ifndef PART_TWO
        if  (is_subset(a, b)) {
            printf(" <- Subset\n");
        }
#else
        if (is_overlap(a, b)) {
            printf(" <- Overlap\n");
        } 
#endif 
        else  {
            putchar('\n');
        }
    }

    return 0;
}

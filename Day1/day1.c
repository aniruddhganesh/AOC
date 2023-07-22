#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int find_high(int *sums) {
    int highest = 0;
    int final = 0;

    for(int j = 0; j < 3; j++) {
        for (int i = 0; i < 1024; i++) {
            if (sums[highest] < sums[i]) {
                highest = i;
            }
        }
        printf("%d\n", sums[highest]);
        final += sums[highest];
        sums[highest] = 0;
    }
    return final;
}

int main(void)
{
    // FILE *fp = fopen("./day1.txt", "r");
    FILE *fp = fopen("./day1.txt", "r");
    char buffer[80] = {0};
    int i = 0, sums[1024] = {0};

    while(fgets(buffer, 80, fp) != NULL) {
        if (isdigit(buffer[0])) {
            sums[i] += atoi(buffer);
        }
        else {
            i++;
        }
    }
    printf("%d -- final \n", find_high(sums));

    return 0;
}

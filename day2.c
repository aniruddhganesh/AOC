#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* A     B       C  [Opponent]
 * Rock  Paper   Scisors
 * X     Y       Z  [US]
 * +1   +2      +3
 * 0 : lost, +3 : draw, +6 : Win
 */
int calc_shape(int mov_self)
{
    int pts_shape = 0;
    // Calculate shape bonus
    switch (mov_self) { // WORKS!
        case 'A': 
            pts_shape += 1; break; // Rock +1
        case 'B':
            pts_shape += 2; break; // Paper +2
        case 'C':
            pts_shape +=3; break; // Scissors +3
        default:
            exit(EXIT_FAILURE); // IDK man error handling
    }
    return pts_shape;
}

int calc_result(int mov_self, int mov_opp)
{
    int pts_result = 0;
    // Calculate Victory or Loss
    if (mov_opp != mov_self) { // Break through if draw
        if ((mov_opp - mov_self) == 2 || (mov_opp - mov_self) == -1)
            // Self lesser by 2 beats, greater by 1 beats, else loss
            pts_result += 6;
    }
    else {
        pts_result += 3; // If moves are equal draw!
    }
    return pts_result;
}

int part_two(void)
{
    return 0;
}

int main(void)
{
    FILE *fp = fopen("./day2.txt", "r");
    char buffer[8];
    char mov_self, mov_opp;
    int pts_total = 0;

    // In part 1 Opponent is left column, self right
    while(fgets(buffer, 8, fp) != NULL) {
        mov_opp = buffer[0];
        mov_self = (buffer[2] - 23); // Equates ie; X becomes A; Y becomes B...
        pts_total += (calc_result(mov_self, mov_opp) + calc_shape(mov_self));
    }

    printf("%d Total --> Part 1 Solution!\n", pts_total);
    return 0;
}

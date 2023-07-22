#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define PART_1 
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

// Takes Opponent move, and required outcome,
// Returns the Move we should play "mov_self"
int outcome_shape(int mov_opp, int result_shape)
{
    int mov_self;

    if (result_shape == 'X') {
        if (mov_opp == 'B' || mov_opp == 'C')
            mov_self = (mov_opp -1);
        else
            mov_self = (mov_opp + 2);
    }
    else if (result_shape == 'Z'){
        if (mov_opp == 'A' || mov_opp == 'B') // If needed to win
            mov_self = (mov_opp + 1);   // Add 1 if Rock or Paper
        else
            mov_self = (mov_opp - 2); // Remove 2 If Scissors
    }
    else {
        mov_self = mov_opp;
    }
    
    return mov_self;
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

int main(void)
{
    FILE *fp = fopen("./day2.txt", "r");
    char buffer[8];
    char mov_self, mov_opp;
    int pts_total = 0;

    // In part 1 Opponent is left column, self right
    while(fgets(buffer, 8, fp) != NULL) {
        mov_opp = buffer[0];
#ifdef PART_1
        mov_self = (buffer[2] - 23); // Equates ie; X becomes A; Y becomes B...
#else
        char result_shape = buffer[2];
        mov_self = outcome_shape(mov_opp, result_shape);
#endif
        pts_total += (calc_result(mov_self, mov_opp) + calc_shape(mov_self));
    }

#ifdef PART_1 
    printf("%d Total --> Part 1 Solution!\n", pts_total);
    return 0;
#else
    printf("%d Total --> Part 2 Solution!\n", pts_total);
    return 0;
#endif

}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* A     B       C  [Opponent]
 * Rock  Paper   Scisors
 * X     Y       Z  [US]
 * +1   +2      +3
 * 0 : lost, +3 : draw, +6 : Win
 */

int main(void)
{
    FILE *fp = fopen("./day2.txt", "r");
    char buffer[8];
    char mov_self, mov_opp;
    int pts_result = 0, pts_shape = 0;


    while(fgets(buffer, 8, fp) != NULL) {
        mov_opp = buffer[0];
        mov_self = (buffer[2] - 23); // Equates ie; X becomes A; Y becomes B...

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

        // Calculate Victory or Loss
        if (mov_opp != mov_self) { // Break through if draw
            if (mov_opp > mov_self) {
                if ((mov_opp - mov_self) == 2)  // self lesser by 2 beats
                    pts_result += 6;
            }
            if (mov_self > mov_opp) {
                if ((mov_self - mov_opp) == 1) // self greater by 1 beats
                    pts_result += 6;
            }
        }
        else {
            pts_result += 3;
        }
    }

    printf("Result ------>\n%d\n", pts_result);
    printf("Shape  ------>\n%d\n", pts_shape);
    printf("Total: %d\n", (pts_shape + pts_result));
    return 0;
}

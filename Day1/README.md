# Day 1: Calorie Counting
## PART 1:
> Basically count the sum of numbers of each group, separated by
> New line. Find the highest sum.
### My Solution:
use ```fgets``` to get each line (fgets stops after newline). You
can use loops as the file cursor doesn't reset. Convert the buffer
to integer and compute the sum adding it to sums array.
After that finding the highest is easy, just loop through the sums
array.

## PART 2:
> Find the top three highest and their sums.
Print the highest sum and add it to the final, remove the highest.
Do this 3 times for getting three highest, and the sum of them in
'final'

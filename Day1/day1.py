fp = open("./day1.txt", "rt")
fp = open("day1.txt", "rt")

sums = [0]
temp = 0
for x in fp:
    if x == '\n':
        sums.append(temp)
        temp = 1
    else:
        temp += int(x)
# End for                                            

print(sum(sorted(sums)[-1:]), "<- Part 1")
print(sum(sorted(sums)[-3:]), "<- Part 2")


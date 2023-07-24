#include <stdio.h>

int max(int *arr, size_t n) {
    int highest = 0;
    
    for (int i = 0; i < n; i++) {
        if (highest < arr[i])
            highest = arr[i];
    }
    return highest;
}

}

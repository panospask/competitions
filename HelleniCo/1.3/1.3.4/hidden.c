#include "hiddenlib.h"
#include <stdlib.h>


void trinary_search(int min, int max) 
{
    if (min >= max - 1) {
        if (!ishidden(min))
            ishidden(max);
        exit(0);
    }

    int first_point = (min + min + max) / 3;
    int second_point = (min + max + max) / 3;

    int result = compare(first_point, second_point);
    int middle = (first_point + second_point) / 2;
    
    if (result == 0) {
        ishidden(middle);
        exit(0);
    }
    else if (result > 0) {
        trinary_search(middle + 1, max);
    }
    else {
        if ((first_point + second_point) % 2 == 0)
            middle--;
        trinary_search(min, middle);
    }
}

int main(void)
{
    int n = getN();

    trinary_search(1, n);
    return -1;
}
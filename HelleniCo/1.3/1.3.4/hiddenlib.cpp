#include "hiddenlib.h"
#include <bits/stdc++.h>
#define R  100
#define N 5

static int count = 0;

bool ishidden(int x)
{
    count++;
    if (x == N) {
        printf("Βρέθηκε με την %d προσπάθεια!\n", count);
        return 1;
    } else {
        return 0;
    }
}

int distance(int x, int y) {
    if (x >= y) {
        return x - y;
    } else {
        return y - x;
    }
}

int compare(int x, int y)
{
    count++;
    if (distance(x, N) < distance(y, N)) {
        return 1;
    } else if (distance(x, N) > distance(y, N)) {
        return -1;
    } else {
        return 0;
    }
}

int getN(void)
{
    count++;
    return R;
}
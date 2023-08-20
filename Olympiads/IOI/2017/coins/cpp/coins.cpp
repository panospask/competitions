#include "coins.h"

std::vector<int> coin_flips(std::vector<int> b, int c) {
    std::vector<int> flips(1);

    int N = 64;

    int xorsum = 0;
    for (int i = 0; i < N; i++) {
        if (b[i])
            xorsum = xorsum ^ i;
    }

    flips[0] = xorsum ^ c;

    return flips;
}

int find_coin(std::vector<int> b) {
    int xorsum = 0;
    int N=64;
    for (int i = 0; i < N; i++)
        if (b[i])
            xorsum = xorsum ^ i;

    return xorsum;
}

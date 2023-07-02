#include <bits/stdc++.h>

using namespace std;

// const int k = 2;
// const int d = 2;
const int k = 340;
const int d = 330;
const int MAXV = 1e6;

unordered_map<int, int> sectors;

int add_sectors(int a)
{
    printf("+ %d\n", a);
    fflush(stdout);
    int i;
    scanf("%d", &i);

    return i;
}

int main(void)
{
    int mnum;
    scanf("%d", &mnum);

    srand(2222);

    for (int i = 0; i < k; i++)
        mnum = max(mnum, add_sectors(rand() % MAXV + 1));

    int total_sectors = 0;
    for (int i = 0; i < d; i++) {
        int res = add_sectors(1);
        if (sectors.find(res) != sectors.end()) {
            printf("! %d\n", total_sectors);
            return 0;
        }
        else
            sectors[res] = ++total_sectors;
    }

    int res = add_sectors(mnum);
    total_sectors += mnum;
    if (sectors.find(res) != sectors.end()) {
        printf("! %d\n", total_sectors - sectors[res]);
        return 0;
    }

    while (true) {
        int res = add_sectors(d);
        total_sectors += d;

        if (sectors.find(res) != sectors.end()) {
            printf("! %d\n", total_sectors - sectors[res]);
            return 0;
        }
    }

    return 0;
}
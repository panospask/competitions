#include <bits/stdc++.h>

using namespace std;

const int STEP = 1000;

unordered_map<int, int> sectors;

int add_sector(int i)
{
    printf("+ %d\n", i);
    fflush(stdout);
    int num;
    scanf("%d", &num);

    return num;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    sectors[n] = 1;

    int total_sectors = 1;
    while (total_sectors <= STEP) {
        int res = add_sector(1);

        if (sectors.find(res) != sectors.end()) {
            // Gone full circle
            printf("! %d\n", total_sectors);
            return 0;
        }
        else {
            sectors[res] = ++total_sectors;
        }
    }


    while (true) {
        int res = add_sector(STEP);
        total_sectors += STEP;

        if (sectors.find(res) != sectors.end()) {
            total_sectors -= sectors[res];
            printf("! %d\n", total_sectors);
            return 0;
        }
    }
}
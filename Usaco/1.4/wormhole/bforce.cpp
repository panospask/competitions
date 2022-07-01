/*
ID: panos.p1
LANG: C++
TASK: wormhole
*/

#include <bits/stdc++.h>

using namespace std;

#define MAXN 15

int wormhole_pair[MAXN];
int xcord[MAXN], ycord[MAXN];
int n;
long long int solutions = 0;

int find_next(int i) 
{
    int xi = xcord[i];
    int yi = ycord[i];

    int next_x = INT_MAX;
    int nextnode = -1;

    for (int j = 0; j < n; j++)
        if (ycord[j] == yi && xcord[j] > xi && xcord[j] < next_x) {
            nextnode = j;
            next_x = xcord[j];
        }

    return nextnode;
}

bool check_cycle(void)
{
    int start;

    for (int i = 0; i < n; i++) {
        start = i;

        for (int c = 0; c < n; c++) {
            start = find_next(wormhole_pair[start]);

            if (start == -1)
                break;
        }

        if (start != -1)
            return true;
    }

    return false;
}

void pair_wormhole(void)
{
    int i;
    for (i = 0; i < n; i++)
        if (wormhole_pair[i] == -1)
            break;

    if (i == n)
        if (check_cycle())
            solutions++;

    for (int j =  i + 1; j < n; j++)
        if (wormhole_pair[i] == -1 && wormhole_pair[j] == -1) {
            wormhole_pair[i] = j;
            wormhole_pair[j] = i;

            pair_wormhole();

            wormhole_pair[i] = -1;
            wormhole_pair[j] = -1;
        }
}

int main(void)
{
    freopen("wormhole.in", "r", stdin);
    freopen("wormhole.out", "w", stdout);

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &xcord[i], &ycord[i]);
        wormhole_pair[i] = -1;
    }

    pair_wormhole();

    printf("%lld", solutions);
    printf("\n");

    return 0;
}
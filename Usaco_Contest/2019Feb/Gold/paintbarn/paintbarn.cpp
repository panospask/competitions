#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXCOORD 201
#define MAXN (int)(10e5)

using namespace std;

int n, k;
int modby[MAXCOORD + 10][MAXCOORD + 10];
int field[MAXCOORD + 10][MAXCOORD + 10];
int one_left_for_k[MAXCOORD + 10][MAXCOORD + 10];
int at_k[MAXCOORD + 10][MAXCOORD + 10];

int main(void)
{
    freopen("paintbarn.in", "r", stdin);
    freopen("paintbarn.out", "w", stdout);

    scanf("%d", &n);
    int x1, x2, y1, y2;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        x1++; y1++; x2++; y2++;
        modby[x1][y1]++;
        modby[x1][y2]--;
        modby[x2][y1]--;
        modby[x2][y2]++;
    }

    // Calculate current field state
    int curk = 0;
    for (int x = 1; x <= MAXCOORD; x++)
        for (int y = 1; x <= MAXCOORD; y++) {
            field[x][y] = -field[x - 1][y - 1] + field[x][y - 1] + field[x - 1][y] + modby[x][y];
            one_left_for_k[x][y] = -one_left_for_k[x - 1][y - 1] + one_left_for_k[x][y - 1] + one_left_for_k[x - 1][y];
            one_left_for_k[x][y] += field[x][y] == k - 1;
            at_k[x][y] = -at_k[x - 1][y - 1] + at_k[x][y - 1] + at_k[x - 1][y];
            at_k[x][y] += field[x][y] == k;
            curk += field[x][y] == k;
        }

    // Find the optimal way to add(or not) the two disjoint rectangles
    int optgain = 0;
    
}
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN (int)(10e5)

using namespace std;

int n;
int times_crossed[MAXN];
int reduce_by = 0;

int find_next_viable(int viab, int dir)
{
    for (int i = viab; i >= 0 && i < n; i += dir) {
        if (times_crossed[i] - reduce_by > 0) {
            if (dir == 1 && times_crossed[i] - reduce_by > 1)
                return i;
            else 
                return i;
        }
    }

    return -1;
}

int main(void)
{
    freopen("mroot.in", "r", stdin);
    freopen("mroot.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &times_crossed[i]);

    int min_viable = 0;
    int max_viable = n - 1;

    bool go_right = true;
    // while ()   
}
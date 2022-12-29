#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100

using namespace std;

int cowplace[MAXN];
int before[MAXN + 2];
int n, m, k;
set<int> next_standard;

int main(void)
{
    freopen("milkorder.in", "r", stdin);
    freopen("milkorder.out", "w", stdout);

    scanf("%d %d %d", &n, &m, &k);
    int cow, place;
    int ans = -1;
    for (int i = 0; i < m; i++) {
        scanf("%d", &cow);
        before[cow] = i;
    }
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &cow, &place);
        cowplace[place - 1] = cow;
        if (cow == 1) 
            ans = place - 1;
        next_standard.insert(place - 1);
    }

    

    printf("%d\n", ans + 1);
    return 0;
}

// FIX TMRW
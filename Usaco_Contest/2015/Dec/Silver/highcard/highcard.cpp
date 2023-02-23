#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 50000

using namespace std;

int n;
set<int> bessiecards;
int elsiecards[MAXN + 5];

int main(void)
{
    freopen("highcard.in", "r", stdin);
    freopen("highcard.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; i++)
        bessiecards.insert(i);
    int curcard;
    for (int i = 0; i < n; i++) {
        scanf("%d", &curcard);
        bessiecards.erase(curcard);
        elsiecards[i] = curcard;
    }
    sort(elsiecards, elsiecards + n);

    int winnum = 0;
    for (int i = 0; i < n;i ++) {
        auto it = bessiecards.lower_bound(elsiecards[i]);
        if (it == bessiecards.end()) 
            it = bessiecards.begin();
        else 
            winnum++;
        bessiecards.erase(it);
    }

    printf("%d\n", winnum);
    return 0;
}
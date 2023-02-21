#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 50000

using namespace std;

int n;
set<int> bessiecards, lowcards, highcards;
int elsiecards[MAXN + 5];

int main(void)
{
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; i++)
        bessiecards.insert(i);

    for (int i = 0; i < n; i++) {
        scanf("%d", &elsiecards[i]);
        bessiecards.erase(elsiecards[i]);
    }
    int cardorder = 0;
    for (auto card : bessiecards) {
        if (cardorder < n / 2)
            lowcards.insert(card);
        else 
            highcards.insert(card);
        cardorder++;
    }


    int winnum = 0;
    for (int i = 0; i < n / 2; i++) {
        auto it = highcards.lower_bound(elsiecards[i]);
        if (it != highcards.end()) 
            winnum++;
        else 
            it = highcards.begin();
        highcards.erase(it);
    }
    for (int i = n / 2; i < n; i++) {
        auto it = lowcards.lower_bound(elsiecards[i]);
        if (it != lowcards.begin()) 
            winnum++;
        else 
            it = lowcards.end();
        lowcards.erase(--it);
    }

    printf("%d\n", winnum);
    return 0;
}
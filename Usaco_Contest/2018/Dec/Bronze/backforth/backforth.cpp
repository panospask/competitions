#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define N 10

using namespace std;

typedef pair<int, int> ii;

set<int> ans;
multiset<ii> buck1;
multiset<ii> buck2;
int onesize = 1000;
int twosize = 1000;

void generate_possibilities(int dayn)
{
    if (dayn == 4) { ans.insert(onesize); return;}

    if (dayn % 2 == 0) {
        // Get milk from 1 --> 2
        multiset<ii> curset = buck1;
        int to_remove;

        for (auto& bucket : curset) {
            to_remove = min(bucket.first, onesize);

            onesize -= to_remove;
            twosize += to_remove;
            buck1.erase(bucket);
            buck2.insert(bucket);

            generate_possibilities(dayn + 1);

            onesize += to_remove;
            twosize -= to_remove;
            buck1.insert(bucket);
            buck2.erase(bucket);
        }
    }
    else {
        // Get milk from 2 --> 1
        multiset<ii> curset = buck2;
        int to_remove;

        for (auto& bucket : curset) {
            to_remove = min(bucket.first, twosize);

            onesize += to_remove;
            twosize -= to_remove;
            buck1.insert(bucket);
            buck2.erase(bucket);

            generate_possibilities(dayn + 1);

            onesize -= to_remove;
            twosize += to_remove;
            buck1.erase(bucket);
            buck2.insert(bucket);
        }
    }
}

int main(void)
{
    freopen("backforth.in", "r", stdin);
    freopen("backforth.out", "w", stdout);

    int bucksize;
    for (int i = 0; i < N; i++) {
        scanf("%d", &bucksize);
        buck1.insert(mp(bucksize, i));
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &bucksize);
        buck2.insert(mp(bucksize, 10 + i));
    }
    generate_possibilities(0);

    printf("%d\n", (int)ans.size());
    return 0;
}
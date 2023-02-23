#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000
#define MAXK 1000

using namespace std;

bool greatercomp(int a, int b)
{
    return a > b;
}

multiset<int, decltype(greatercomp)*> berries_for_a_basket(greatercomp);
int n, k;
int max_berries = 0;

int main(void)
{
    freopen("berries.in", "r", stdin);
    freopen("berries.out", "w", stdout);

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        int curberries;
        scanf("%d", &curberries);
        berries_for_a_basket.insert(curberries);
        max_berries = max(max_berries, curberries);
    }

    int ans = 0;
    for (int v = 1; v <= max_berries; v++) {
        // Assume the k / 2 first baskets have v berries
        int baskets_rem = k / 2;
        multiset<int, decltype(greatercomp)*> cur_berries(greatercomp);
        cur_berries = berries_for_a_basket;
        bool isgood = true;

        while (baskets_rem > 0 && !cur_berries.empty()) {
            auto it = cur_berries.begin();
            int current = *it;
            if (current < v) break;
            cur_berries.erase(it);

            int baskets_removable = min(current / v, baskets_rem);
            baskets_rem -= baskets_removable;
            cur_berries.insert(current - baskets_removable * v);
        }

        if (baskets_rem > 0) {
            isgood = false;
        }

        // Fill the next as many baskets are possible with v berries
        int local_ans = 0;
        int baskets_to_fill = k / 2;
        while (!cur_berries.empty() && baskets_to_fill > 0 && isgood) {
            auto it = cur_berries.begin();
            int current = *it;
            if (current < v) break;
            cur_berries.erase(it);

            int to_rem = min(baskets_to_fill, current / v);
            baskets_to_fill -= to_rem;
            local_ans += to_rem * v;
            if (to_rem * v != current)
                cur_berries.insert(current - to_rem * v);
        }

        while (baskets_to_fill > 0 && isgood && !cur_berries.empty()) {
            auto it = cur_berries.begin();
            int current = *it;
            cur_berries.erase(it);
            local_ans += current;
            baskets_to_fill--;
        }

        if (!isgood)
            local_ans = -1;

        ans = max(ans, local_ans);
    }

    printf("%d\n", ans);
    return 0;
}
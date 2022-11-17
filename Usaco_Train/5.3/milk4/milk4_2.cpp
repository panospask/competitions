/*
ID: panos.p1
LANG: C++11
TASK: milk4
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100

using namespace std;

int q, p;

int gallons[MAXN];
set<int> curvals;
set<int> ans;

bool iddfs(int curval, int vals, int curi)
{
    if (curval > q)
        return false;
    
    if (curval == q) {
        ans = min(ans, curvals);
        if (ans.empty())
            ans = curvals;
        return true;
    }

    if (curvals.size() < vals) {
        for (int i = curi + 1; i < p; i++) {
            curvals.insert(gallons[i]);
            bool found = false;
            for (int to_add = gallons[i]; to_add + curval <= q; to_add += gallons[i])
                if (iddfs(curval + to_add, vals, i))
                    found = true;

            curvals.erase(gallons[i]);
            if (found)
                return true;

        }
    }
    

    return false;
}

int main(void)
{
    freopen("milk4.in", "r", stdin);
    freopen("milk4.out", "w", stdout);

    scanf("%d %d", &q, &p);
    for (int i = 0; i < p; i++)
        scanf("%d", &gallons[i]);

    for (int i = 1; i <= p; i++)
        if (iddfs(0, i, -1))
            break;
    sort(gallons, gallons + p);

    printf("%d", (int)ans.size());
    for (auto v : ans)
        printf(" %d", v);
    printf("\n");
    return 0;
}
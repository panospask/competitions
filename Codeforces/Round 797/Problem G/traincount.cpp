#include <bits/stdc++.h>

using namespace std;

set<int> leads;
int speed[100005];
int n, m;

void solve_query(void)
{
    int k, d;
    scanf("%d %d", &k, &d);

    speed[--k] -= d;

    auto prev = leads.upper_bound(k);
    prev--;

    if (k == *prev || speed[*prev] > speed[k]) {
        leads.insert(k);
        auto it = leads.upper_bound(k);

        while (it != leads.end()) {
            it = leads.upper_bound(k);

            if (it != leads.end()  && speed[(*it)] >= speed[k]) {
                leads.erase((*it));
            }
            else 
                break;
        }
    }


    printf("%d ", (int)leads.size());
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        leads.clear();
        
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; i++) {
            scanf("%d", &speed[i]);
            if (leads.empty() || speed[i] < speed[*(leads.rbegin())])
                leads.insert(i);
        }

        for (int j = 0; j < m; j++) {
            solve_query();
        }

        printf("\n");
    }

    return 0;
}
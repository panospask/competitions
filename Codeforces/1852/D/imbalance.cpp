#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int n;
set<pi> s;
vector<int> b;

void solve(void)
{
    s.clear();
    scanf("%d", &n);

    b.resize(n);
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        s.insert(mp(num, i));
    }

    int mod = 0;
    int placed = 0;
    while (placed < n) {
        pi fr = *s.begin();
        pi ba = *s.rbegin();

        bool v1 = fr.first == mod;
        bool v2 = ba.first == n - placed + mod;
        if (v1 && !v2) {
            // Assign small value to current index
            b[fr.second] = -(n - placed);
            s.erase(s.begin());
        }
        else if (v2 && !v1) {
            b[ba.second] = n - placed;
            mod++;
            s.erase(s.find(ba));
        }
        else {
            printf("NO\n");
            return;
        }

        placed++;
    }

    printf("YES\n");
    for (int i = 0; i < n; i++)
        printf("%d ", b[i]);
    printf("\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();


    return 0;
}
#include <bits/stdc++.h>
#define MAXN 1500
#define mp make_pair

using namespace std;

int n;
string garland;
set<char> seen;
map<pair<char, int>, int> ans;
int q;

int main(void)
{
    scanf("%d", &n);
    cin >> garland;
    for (int i = 0; i < n; i++) {
        seen.insert(garland[i]);
    }

    // Find the longest subsequence that has all but i characters of type c
    for (auto c : seen) {
        for (int i = 0; i <= n; i++) {
            int localmax = 0;
            int l = 0, r = 0;
            int extrachars = 0;

            while (l < n || l <= n - localmax) {
                if (extrachars > i) {
                    if (garland[l] != c)
                        extrachars--;
                    l++;

                    continue;
                }

                while (extrachars < i && r < n) {
                    if (garland[r] != c)
                        extrachars++;

                    r++;
                }
                while (r < n && garland[r] == c)
                    r++;

                localmax = max(localmax, r - l);

                if (garland[l] != c)
                    extrachars--;
                l++;
            }

            ans[mp(c, i)] = localmax;
        }
    }

    scanf("%d", &q);
    char cur;
    int allow;
    for (int x = 0; x < q; x++) {
        scanf("%d %c", &allow, &cur);
        if (seen.count(cur) != 0)
            printf("%d\n", ans[mp(cur, allow)]);
        else 
            printf("%d\n", allow);
    }

    return 0;
}
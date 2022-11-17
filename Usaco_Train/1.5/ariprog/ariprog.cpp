/*
ID: panos.p1
LANG: C++
TASK: ariprog
*/


#include <bits/stdc++.h>

using namespace std;

bool is_bisquare[250 * 250 * 2];
vector<pair<int,int>> ans;
int n, m;

bool check(int s, int d)
{
    int num = s;
    for (int i = 0; i < n; i++)
        if (!is_bisquare[s + i * d])
            return false;

    return true;
}

int main(void)
{
    freopen("ariprog.in", "r", stdin);
    freopen("ariprog.out", "w", stdout);

    scanf("%d %d", &n, &m);

    for (int i = 0; i <= m; i++)
        for (int j = i; j <= m; j++) {
            is_bisquare[i * i + j * j] = true;
        }

    int m2 = m * m * 2;

    for (int s = 0; s <= m2; s++)
        for (int d = 1; d <= (m2 - s) / (n -1) ; d++) {
            if (check(s, d)) {
                ans.push_back(make_pair(d, s));
            }
        }

    sort(ans.begin(), ans.end());
    if (!ans.empty()) {
        for (auto& a : ans)
            printf("%d %d\n", a.second, a.first);
    }
    else 
        printf("NONE\n");

    return 0;
}
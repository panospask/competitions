#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 500

using namespace std;

typedef pair<int, int> ii;

string cows[MAXN * 2 + 5];
unordered_map<string, bool> spotted_cows_have_gene;
int n, m;
int ans = 0;

bool found(int mod_by, vector<ii>& pos)
{
    int spot = 0;
    spot += mod_by * n;

    for (int i = spot; i < spot + n; i++) {
        bool exist = true;
        for (auto& place : pos) {
            if (!exist) 
                break;
            if (cows[spot][place.first] != place.second)
                exist = false;
        }
        if (exist)
            return true;
    }

    return false;
}

void check_correct(vector<int>& cur)
{
    spotted_cows_have_gene.clear();
    // Check spotted cows
    string curstring;
    for (int i = 0; i < n; i++) {
        curstring.clear();
        for (auto j : cur)
            curstring.pb(cows[i][j]);
        spotted_cows_have_gene[curstring] = true;
    }

    // Check unspotted cows
    bool same = false;
    for (int i = n; i < 2 * n && !same; i++) {
        curstring.clear();
        for (auto j : cur)
            curstring.pb(cows[i][j]);
        if (spotted_cows_have_gene[curstring])
            same = true;
    }

    if (!same)
        ans++;
}

void generate_genes(int nleft, int prev, vector<int>& cur)
{
    if (nleft == 0) {
        check_correct(cur);
        return;
    }

    for (int i = prev + 1; i < m; i++) {
        cur.pb(i);
        generate_genes(nleft - 1, i, cur);
        cur.pop_back();
    }
}

int main(void)
{
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for (int i = 0; i < 2 * n; i++) {
        cin >> cows[i];
    }

    vector<int> c;
    generate_genes(3, -1, c);

    printf("%d\n", ans);
    return 0;    
}
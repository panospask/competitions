#include <bits/stdc++.h>
#define MAXN 100
#define MAXM 100
#define pb push_back

using namespace std;

int n, m;
unordered_map<char, bool> has_genes[2][MAXM];

void read_cows(bool has_spots)
{
    char curgene;
    for (int i = 0; i < n; i++) {
        getchar();
        for (int c = 0; c < m; c++) {
            curgene = getchar();
            has_genes[has_spots][c][curgene] = true;
        }
    } 
}

bool check_gene(int place, char genes)
{
    int sp = has_genes[true][place][genes];
    int nsp = has_genes[false][place][genes];

    if (sp != nsp || (sp == 0 && nsp == 0))
        return true;
    return false;
}

bool check_place(int i)
{
    if (check_gene(i, 'A') && check_gene(i, 'T') && check_gene(i, 'C') && check_gene(i, 'G'))
        return true;
    return false;
}

int main(void) 
{
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);

    scanf("%d %d", &n, &m);
    read_cows(true);
    read_cows(false);

    vector<int> ans;
    for (int j = 0; j < m; j++)
        if (check_place(j))
            ans.pb(j);

    printf("%d\n", (int)ans.size());
    return 0; 
}
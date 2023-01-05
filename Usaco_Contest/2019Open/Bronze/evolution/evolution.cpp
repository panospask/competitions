#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 25
#define MAXK 25

using namespace std;

unordered_map<string, int> genes;
int genecount = 0;

set<int> genes_of[MAXN];
set<int> pops_with_gene[MAXK];
set<int> genes_after[MAXN];
int n;

bool check_for_pops_with_g1_and_no_g2(int gene1, int gene2)
{
    for (auto pop : pops_with_gene[gene1])
        if (genes_of[pop].count(gene2) == 0)
            return true;
    return false;
}

bool check_for_pops_with(int gene1, int gene2)
{
    for (auto pop : pops_with_gene[gene1])
        if (genes_of[pop].count(gene2) != 0)
            return true;

    return false;
}

int main(void)
{
    freopen("evolution.in", "r", stdin);
    freopen("evolution.out", "w", stdout);

    scanf("%d", &n);
    int gensize;
    int gene_id;
    string curgene;
    for (int i = 0; i < n; i++) {
        scanf("%d", &gensize);
        for (int j = 0; j < gensize; j++) {
            cin >> curgene;
            if (genes.count(curgene) == 0) {
                genes[curgene] = genecount;
                genecount++;
            }
            gene_id = genes[curgene];
            genes_of[i].insert(gene_id);
            pops_with_gene[gene_id].insert(i);
        }
    }

    bool isgood = true;
    for (int i = 0; i < n && isgood; i++)
        for (int j = i + 1; j < n && isgood; j++)
            if (check_for_pops_with_g1_and_no_g2(i, j) && check_for_pops_with_g1_and_no_g2(j, i) && check_for_pops_with(i, j))
                isgood = false;

    if (isgood)
        printf("yes\n");
    else 
        printf("no\n");

    return 0;
}
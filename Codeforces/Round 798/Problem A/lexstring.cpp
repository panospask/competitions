#include <bits/stdc++.h>

using namespace std;

#define pb push_back

vector<char> a;
vector<char> b;

int n, m, k;
int total_cont = 0;
int cont_from = 0;
int a_pt = 0;
int b_pt = 0;

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        a.clear();
        b.clear();
        
        scanf("%d %d %d", &n, &m, &k);

        a.resize(n);
        b.resize(m);
        for (int i = 0; i < n; i++)
            a[i] = getchar();
        for (int j = 0; j < m; j++)
            b[j] = getchar();

        total_cont = 0;
        cont_from = 0;
        a_pt = 0;
        b_pt = 0;

        for (int i = 0; i < n + m; i++) {
            
        }
    }
}
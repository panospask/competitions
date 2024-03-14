#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int OPTIONS[3] = {1, 2, 3};

int N, K;
vector<int> dep;
vector<int> col;
vector<vector<int>> kids;

void dfs(int node)
{
    if (node) {
        col[node] = (OPTIONS[dep[node] % 3]);
    }

    K = max(K, col[node]);

    for (auto kid : kids[node]) {
        dep[kid] = dep[node] + 1;
        dfs(kid);
    }
}

void print_colours(void)
{
    printf("%d\n", K);
    for (int i = 1; i < N; i++)
        printf("%d ", col[i]);
    printf("\n");

    fflush(stdout);
}

void read_colours(vector<int>& v)
{
    int g;
    scanf("%d", &g);
    if (g == 1)
        exit(EXIT_SUCCESS);
    else if (g == -1)
        exit(EXIT_FAILURE);

    v.resize(K);
    for (int i = 0; i < K; i++)
        scanf("%d", &v[i]);
}

void going_to(int c)
{
    printf("%d\n", c);
    fflush(stdout);
}

void process_node()
{
    vector<int> c;
    read_colours(c);

    // You will have either 1 or 2 colours
    for (int i = 0; i < K; i++) {
        if (c[i]) {
            int prv = (i - 1 + K) % K;

            if (K == 3 && c[prv]) {
                going_to(OPTIONS[prv]);
                process_node();
            }
            else {
                going_to(OPTIONS[i]);
                process_node();
            }
        }
    }
}

int main(void)
{
    scanf("%d", &N);

    dep.resize(N);
    kids.resize(N);
    col.resize(N);

    for (int i = 1; i < N; i++) {
        int p;
        scanf("%d", &p);
        p--;
        kids[p].pb(i);
    }

    dep[0] = -1;
    dfs(0);

    print_colours();

    process_node();

    return 0;
}
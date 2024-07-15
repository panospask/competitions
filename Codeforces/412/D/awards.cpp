#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int N, M;
set<pi> owes;
vector<int> p;

int main(void)
{
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        owes.insert(mp(u, v));
    }

    for (int i = 1; i <= N; i++) {
        p.push_back(i);

        int j = i - 1;
        while (j >= 1 && owes.count(mp(p[j - 1], p[j]))) {
            swap(p[j], p[j - 1]);
            j--;
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", p[i]);
    }
    printf("\n");

    return 0;
}
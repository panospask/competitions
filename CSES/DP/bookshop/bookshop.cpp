#include <bits/stdc++.h>
#define MAXN (int)1e3
#define MAXP (int)1e5

using namespace std;

typedef pair<int, int> ii;

long long int maxvalue[MAXP + 2][2];
int n, x;
ii books[MAXN + 2];

int main(void)
{
    scanf("%d %d", &n, &x);
    for (int i = 1; i <= n; i++)
        scanf("%d", &books[i].first);
    for (int i = 1; i <= n; i++)
        scanf("%d", &books[i].second);

    sort(books + 1, books + n + 1);

    maxvalue[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        // Find the maxvalue using only the first i books
        for (int p = 0; p <= x; p++) {
            maxvalue[p][1] = max(maxvalue[p][1], maxvalue[p-1][1]);
            maxvalue[p][1] = max(maxvalue[p][1], maxvalue[p][0]);

            if (books[i].first + p <= x)
                maxvalue[p + books[i].first][1] = max(maxvalue[p + books[i].first][1], maxvalue[p][0] + books[i].second);

        }

        for (int p = 0; p <= x; p++) {
            maxvalue[p][0] = maxvalue[p][1];
            maxvalue[p][1] = 0;
        }
    }

    printf("%lld\n", maxvalue[x][0]);
    return 0;
}
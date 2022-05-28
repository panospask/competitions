#include <bits/stdc++.h>

using namespace std;

#define mp make_pair

typedef pair<int,int> ii;

int find_common_range(ii a, ii b)
{
    if (a.first <= b.second && b.first <= a.second) {
        return max(a.first, b.first);
    }

    return -1;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        int x1, x2, y1, y2;
        scanf("%d %d %d %d", &x1, &x2, &y1, &y2);

        int common = find_common_range(mp(x1, x2), mp(y1, y2));

        if (common == -1)
            common = x1 + y1;
        
        printf("%d\n", common);
    }

    return 0;
}
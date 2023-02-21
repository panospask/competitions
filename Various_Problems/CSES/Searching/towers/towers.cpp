#include <bits/stdc++.h>
#define MAXN 200000 

using namespace std;

multiset<int> topsize;
int n;
int cubes[MAXN];

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i <n; i++) {
        scanf("%d", &cubes[i]);

        auto it = topsize.upper_bound(cubes[i]);
        if (it != topsize.end()) {
            topsize.erase(it);
        }
        topsize.insert(cubes[i]);
    }

    printf("%d\n", (int)topsize.size());
    return 0;
}
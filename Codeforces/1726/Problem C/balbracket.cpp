#include <bits/stdc++.h>

using namespace std;

int t, n;
string bal;
bool vis_level[100005];

int main(void)
{   
    scanf("%d", &t);
    for (int x = 0; x < t; x++) {
        scanf("%d", &n);
        cin >> bal;

        int level = 0;
        int ttl_comp = 0;
        memset(vis_level, false, sizeof(vis_level));
        for (int i = 0; i < 2 * n; i++) {
            if (bal[i] == '(') {
                level++;
                if (!vis_level[level]) {
                    ttl_comp++;
                    vis_level[level] = true;
                }
                vis_level[level + 1] = false;
            }
            if (bal[i] == ')') {
                level--;
            }
        }

        printf("%d\n", ttl_comp);
    }

    return 0;
}
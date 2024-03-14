#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
#define mp make_pair

ii shoes[100015];
int get_shoe[100015];
int n;
bool used[100015];
bool can_make = true;

void find_cycle(int i)
{
    if (used[i])
        return;

    int num = shoes[i].first;
    int last = 1;
    for (int j = i; j > 0; j--) {
        if (shoes[j].first != num) {
            last = j + 1;
            break;
        }
        else {
            used[j] = true;
        }
    }

    if (last == i) {
        can_make = false;
        return;
    }

    for (int j = i; j > last; j--) {
        get_shoe[shoes[j].second] = shoes[j - 1].second;
    }
    get_shoe[shoes[last].second] = shoes[i].second;

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        can_make = true;
        scanf("%d", &n);
        memset(used, false, n + 10);

        for (int i = 1; i <= n; i++) {
            scanf("%d", &shoes[i].first);
            shoes[i].second = i;
        }

        sort (shoes + 1, shoes + n + 1);

        for (int i = n; i > 0 && can_make; i--) {
            find_cycle(i);            
        }

        if (can_make) {
            for (int i = 1; i <= n; i++)
                printf("%d ", get_shoe[i]);
        }
        else 
            printf("-1");

        printf("\n");
    }

    return 0;
}
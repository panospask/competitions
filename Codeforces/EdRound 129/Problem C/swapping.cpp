#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair

typedef pair<int,int> ii;

int n;
int a[100], b[100];
vector<ii> swaps;

void print_swaps(void)
{
    printf("%d\n", (int)swaps.size());

    for (auto i : swaps)
        printf("%d %d\n", i.first + 1, i.second + 1);

    return;
}

void selection_sort(void)
{
    int cur_min;
    for (int i = 0; i < n; i++) {
        cur_min = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[cur_min])
                cur_min = j;
            else if (a[j] == a[cur_min])
                if (b[j] < b[cur_min])
                    cur_min = j;
        }

        if (i != cur_min) {
            swap(a[i], a[cur_min]);
            swap(b[i], b[cur_min]);
            swaps.pb(mp(i, cur_min));
        }
    }

    bool correct = true;
    for (int i = 1; i < n && correct; i++) {
        if (b[i - 1] > b[i])
            correct = false;
    }

    if (correct) 
        print_swaps();
    else 
        printf("-1\n");

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        swaps.clear();

        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &b[i]);
        }

        selection_sort();
    }
}
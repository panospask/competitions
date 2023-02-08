#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

int n;
int arr[MAXN + 5];
int relative_array[MAXN + 5];
map<int, vector<int>> places_of_digit;

int main(void)
{
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        relative_array[i] = arr[i];
        places_of_digit[arr[i]].pb(i);
    }

    int i = 0;
    for (auto d : places_of_digit) {
        for (auto place : d.second) {
            relative_array[place] = i++;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)    
        ans = max(ans, i - relative_array[i]);

    printf("%d\n", ans + 1);    
    return 0;
}
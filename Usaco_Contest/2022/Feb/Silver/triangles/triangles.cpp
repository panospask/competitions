#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN (int)(10e5)

using namespace std;

typedef pair<int, int> ii;

int n;
ii coords[MAXN + 5];
unordered_map<int, vector<int>> same_y;
unordered_map<int, vector<int>> same_x;
long long int sum;

void find_third_point(int f, int s)
{

}

int main(void)
{
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coords[i].first, &coords[i].second);
        same_x[coords[i].first].pb(i);
        same_y[coords[i].second].pb(i);
    }

    // Find the sum of all vertical sides for point

}
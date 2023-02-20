#include <bits/stdc++.h>
#define MAXN 200000
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

int n, k;
ii movies[MAXN];
int avail_members;
queue<int> finishing_times;

int main(void)
{
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &movies[i].second, &movies[i].first);
    }
    avail_members = k;
    sort(movies, movies + n);

    int curmovie = 0;
    int movies_watched = 0;
    while (curmovie < n) {
        int curtime = movies[curmovie].first;
    }

    // TO DO: FIX IT
}
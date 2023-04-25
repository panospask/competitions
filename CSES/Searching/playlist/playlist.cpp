#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> songs;
map<int, int> songcount;

int main(void)
{
    scanf("%d", &n);
    songs.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &songs[i]);

    int l = 0;
    int ans = 0;
    for (int r = 0; r < n; r++) {
        songcount[songs[r]]++;
        while (songcount[songs[r]] > 1) {
            if (l != -1)
                songcount[songs[l]]--;
            l++;
        }

        ans = max(ans, r - l + 1);
    }

    printf("%d\n", ans);
    return 0;
}
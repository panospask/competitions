#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

int n, m, k;
int appartment_size[MAXN + 5];
int guests[MAXN + 5];


int main(void)
{
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &appartment_size[i]);
    }
    sort(appartment_size, appartment_size + n);
    for (int i = 0; i < m; i++) {
        scanf("%d", &guests[i]);
    }
    sort(guests, guests + m);

    int total_rooms_served = 0;
    int cur_room = 0;
    for (int i = 0; i < m && cur_room < n; i++) {
        // Give every guest the first avail room
        // Everyone else will be able to take the bigger ones since they are sorted by desires

        while (cur_room < n && appartment_size[cur_room] < guests[i] - k)
            cur_room++;

        if (cur_room < n && appartment_size[cur_room] <= guests[i] + k) {
            cur_room++;
            total_rooms_served++;
        }
    }

    printf("%d\n", total_rooms_served);
    return 0;
}
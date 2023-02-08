#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

int n;
int pos[MAXN];

int main(void)
{
    freopen("herding.in", "r", stdin);
    freopen("herding.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &pos[i]);
    sort(pos, pos + n);

    // Find the most cows that are in an n-sized area
    int l = 0, r = 0;
    int maxcows = 0;
    bool iscon = true;
    bool anscon = false;
    deque<int> breaks_con;
    while (l < n) {
        while (r < n && pos[r] - pos[l] < n) {
            if (r > 0 && pos[r] != pos[r - 1] + 1) {
                iscon = false;
                breaks_con.push_back(r - 1);
            }
            r++;
        }
        
        if (r - l > maxcows || ((r - l == maxcows) && !iscon)) {
            maxcows = r - l;
            anscon = iscon;
        }

        if (breaks_con.front() == l)
            breaks_con.pop_front();

        iscon = breaks_con.empty();
        l++;
    }
    int minans = n - maxcows + anscon;
    if (maxcows == n)
        minans = 0;

    // For the most move, we cover at least one square per move
    // In the starting move, we move adjacently to the new endpoint
    int maxans = 1;
    // From there, we do one move at a time
    maxans += max(pos[n - 1] - pos[1], pos[n - 2] - pos[0]);
    maxans -= n - 1;

    printf("%d\n", minans);
    printf("%d\n", maxans);

    return 0;
}
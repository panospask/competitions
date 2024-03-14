#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int n;
vector<int> maximum_reach;
vector<int> packmen;
vector<int> asterisk;

bool can_reach(int t)
{
    maximum_reach[0] = -1;

    for (int i = 1; i <= packmen.size(); i++) {
        int most_back_pos = upper_bound(asterisk.begin(), asterisk.end(), maximum_reach[i - 1]) - asterisk.begin();
        int most_back = asterisk[most_back_pos];
        int cur = packmen[i - 1];

        if (most_back > cur) {
            maximum_reach[i] = t + cur;
            if (maximum_reach[i] >= asterisk.back())
                return true;
            continue;
        }

        int dist = cur - most_back;

        if (t < dist)
            return false;

        // Can either cover this distance twice or go front and then back
        maximum_reach[i] = cur + max((t - dist) / 2, t - 2 * dist);

        if (maximum_reach[i] >= asterisk.back())
            return true;
    }

    return false;
}

int main(void)
{
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char c;
        scanf(" %c", &c);

        if (c == '*')
            asterisk.pb(i);
        else if (c == 'P')
            packmen.pb(i);
    }

    maximum_reach.resize(packmen.size() + 5);

    int l = 0;
    int r = 2 * n;
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (can_reach(mid))
            r = mid;
        else
            l = mid;
    }

    printf("%d\n", r);
    return 0;
}
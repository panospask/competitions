#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> v;

//s[i] is the sum of the numbers from i - len + 1 to i
vector<int> s;

deque<int> sliding_minimum;

vector<int> minimum_segment;

int main(void)
{
    scanf("%d", &n);
    v.resize(2 * n);
    s.resize(2 * n);
    minimum_segment.assign(n, INT_MAX);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
        v[n + i] = v[i];
    }

    int len = n / 2 + n % 2;
    int cur_s = 0;
    for (int i = 0; i < len - 1; i++)
        cur_s += v[i];

    for (int i = len - 1; i < 2 * n; i++) {
        cur_s += v[i];
        s[i] = cur_s;
        while (!sliding_minimum.empty() && sliding_minimum.back() > s[i]) {
            sliding_minimum.pop_back();
        }
        sliding_minimum.push_back(s[i]);

        // Remove v[i - len + 1]
        int rm = i - len + 1;
        minimum_segment[rm % n] = min(minimum_segment[rm % n], sliding_minimum.front());

        if (s[rm] == sliding_minimum.front())
            sliding_minimum.pop_front();

        cur_s -= v[rm];
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, minimum_segment[i]);

    printf("%d\n", ans);
    return 0;
}
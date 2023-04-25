#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

int n;
vector<int> height;
stack<ii> left_smaller;
stack<ii> right_smaller;
vector<ii> accept_range;

int main(void)
{
    scanf("%d", &n);
    height.resize(n);
    accept_range.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &height[i]);

    for (int i = 0; i < n; i++) {
        while (!left_smaller.empty()) {
            ii cur = left_smaller.top();
            if (cur.first >= height[i])
                left_smaller.pop();
            else
                break;
        }

        if (left_smaller.empty())
            accept_range[i].first = -1;
        else
            accept_range[i].first = left_smaller.top().second;

        left_smaller.push(make_pair(height[i], i));
    }
    for (int i = n - 1; i >= 0; i--) {
        while (!right_smaller.empty()) {
            ii cur = right_smaller.top();
            if (cur.first >= height[i])
                right_smaller.pop();
            else
                break;
        }

        if (right_smaller.empty())
            accept_range[i].second = n;
        else
            accept_range[i].second = right_smaller.top().second;

        right_smaller.push(make_pair(height[i], i));
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int width = accept_range[i].second - accept_range[i].first - 1;
        ans = max(ans, (long long)width * height[i]);
    }

    printf("%lld\n", ans);
}
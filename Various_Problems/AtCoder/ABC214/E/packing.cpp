#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

struct Leftpoint {
    int x;
    vector<int> right;
};

int N;
vector<Leftpoint> leftpoints;
priority_queue<int, vector<int>, greater<int>> rightpoints;
vector<pi> balls;

void clear(void)
{
    while (!rightpoints.empty()) {
        rightpoints.pop();
    }
    leftpoints.clear();
}

void solve(void)
{
    scanf("%d", &N);

    clear();
    balls.resize(N);

    for (int i = 0; i < N; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        balls[i] = mp(l, r);
    }

    sort(balls.begin(), balls.end());
    for (int i = 0; i < N; i++) {
        if (leftpoints.empty() || leftpoints.back().x != balls[i].first) {
            leftpoints.push_back({balls[i].first, {balls[i].second}});
        }
        else {
            leftpoints.back().right.push_back(balls[i].second);
        }
    }
    leftpoints.push_back({INT_MAX, {}});

    for (int l = 0; l < leftpoints.size() - 1; l++) {
        for (auto r : leftpoints[l].right)
            rightpoints.push(r);

        int pos = leftpoints[l].x;
        while (!rightpoints.empty() && pos < leftpoints[l + 1].x) {
            if (pos > rightpoints.top()) {
                printf("No\n");
                return;
            }

            rightpoints.pop();
            pos++;
        }
    }

    printf("Yes\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}
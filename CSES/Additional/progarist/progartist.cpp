#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int N, A, B;
vector<pi> applicants;
ll ans = 0;

bool cmp1(const pi& a, const pi& b)
{
    if (a.first == b.first) {
        return a.second > b.second;
    }

    return a.first > b.first;
}

bool cmp2(const pi& a, const pi& b)
{
    if (a.first - a.second == b.first - b.second) {
        return a.first < b.first;
    }

    return a.first - a.second > b.first - b.second;
}

bool cmp3(const pi& a, const pi& b)
{
    return a.second > b.second;
}

int main(void)
{
    scanf("%d %d %d", &A, &B, &N);

    applicants.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &applicants[i].first, &applicants[i].second);
    }

    sort(applicants.begin(), applicants.end(), cmp1);

    ll cur = 0;

    priority_queue<int, vector<int>, greater<int>> programmers;
    priority_queue<int> aspiring_artists;
    aspiring_artists.push(0);

    for (int i = 0; i < A; i++) {
        cur += applicants[i].first;
        programmers.push(applicants[i].first - applicants[i].second);
    }
    for (int i = A; i < N; i++) {
        aspiring_artists.push(applicants[i].second);
    }
    for (int i = 0; i < B; i++) {
        cur += aspiring_artists.top();
        aspiring_artists.pop();
    }

    ans = max(ans, cur);
    for (int p = A; p < A + B; p++) {
        if (applicants[p].second > aspiring_artists.top())
    }

    return 0;
}
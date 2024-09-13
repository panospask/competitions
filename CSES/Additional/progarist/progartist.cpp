#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int N, A, B;
vector<pi> applicants;
ll ans = 0;

bool diffsort(const pi& a, const pi& b)
{
    return a.first - a.second < b.first - b.second;
}

int main(void)
{
    scanf("%d %d %d", &A, &B, &N);

    applicants.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &applicants[i].first, &applicants[i].second);
    }

    sort(applicants.rbegin(), applicants.rend(), diffsort);

    priority_queue<int, vector<int>, greater<int>> programmers;
    multiset<int> artists;
    multiset<int> future_artists;        

    ll ans = 0;
    ll cur = 0;

    int weakart = INT_MAX;
    for (int i = 0; i < A; i++) {
        programmers.push(applicants[i].first);
        cur += applicants[i].first;
    }
    for (int i = A; i < A + B; i++) {
        artists.insert(applicants[i].second);
        cur += applicants[i].second;
        weakart = min(weakart, applicants[i].second);
    }
    for (int i = A + B; i < N; i++) {

        int last = applicants[i].second;
        if (applicants[i].second > weakart) {
            artists.insert(applicants[i].second);
            
            cur -= weakart;
            cur += applicants[i].second;
            last = weakart;

            artists.erase(artists.find(weakart));
            weakart = *artists.begin();
        }

        future_artists.insert(last);
    }

    ans = max(ans, cur);
    for (int i = A; i < N - B; i++) {
        // Move i from artist to programmer

        // Remove artist
        if (applicants[i].second >= weakart) {
            cur -= applicants[i].second;
            artists.erase(artists.find(applicants[i].second));

            weakart = *future_artists.rbegin();
            future_artists.erase(future_artists.find(weakart));
            artists.insert(weakart);
            cur += weakart;
        }
        else {
            future_artists.erase(future_artists.find(applicants[i].second));
        }

        // Insert programmer
        if (A > 0 && programmers.top() < applicants[i].first) {
            cur += applicants[i].first;
            cur -= programmers.top();

            programmers.pop();
            programmers.push(applicants[i].first);
        }

        ans = max(ans, cur);
    }

    printf("%lld\n", ans);

    return 0;
}
#include <bits/stdc++.h>

using namespace std;

struct Group {
    int K;
    int people;
    vector<int> small;
    vector<int> big;

    Group (vector<int>& s) {
        K = s.size();
        small = big = s;
        people = 1;
    }

    bool operator < (const Group g) const {
        for (int i = 0; i < K; i++) {
            if (this->big[i] >= g.small[i])
                return false;
        }

        return true;
    }

    void merge(const Group& g) {
        for (int i = 0; i < K; i++) {
            this->big[i] = max(this->big[i], g.big[i]);
            this->small[i] = min(this->small[i], g.small[i]);
        }

        this->people += g.people;
    }
};

int N, K;
vector<vector<int>> s;

int main(void)
{
    scanf("%d %d", &N, &K);

    s.resize(N, vector<int>(K));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < K; j++)
            scanf("%d", &s[i][j]);

    set<Group> order;

    for (int i = 0; i < N; i++) {
        Group cur(s[i]);

        auto it = order.lower_bound(cur);
        while (it != order.end() && !(cur < *it)) {
            cur.merge(*it);
            order.erase(it);

            it = order.lower_bound(cur);
        }

        order.insert(cur);

        Group ans = *order.rbegin();

        printf("%d\n", ans.people);
    }

    return 0;
}
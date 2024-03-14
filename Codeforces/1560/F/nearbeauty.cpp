#include <bits/stdc++.h>

using namespace std;

const int MAXP = 9;

int N, K;

set<int> used;
vector<int> number;
vector<int> res;

bool generatenumber(int pos, bool bigger, bool leadz)
{
    if (pos == -1)
        return true;

    int v = number[pos];
    for (int l = 0; l < 10; l++) {
        if (used.size() == K && used.find(l) == used.end())
            continue;

        bool ins = false;
        bool newz = leadz && l == 0;
        if (used.find(l) == used.end() && !newz) {
            ins = true;
            used.insert(l);
        }


        res.push_back(l);
        if (l < v) {
            if (bigger && generatenumber(pos - 1, bigger, newz))
                return true;
        }
        else if (l == v) {
            if (generatenumber(pos - 1, bigger, newz))
                return true;
        }
        else {
            if (generatenumber(pos - 1, true, newz))
                return true;
        }

        res.pop_back();
        if (ins)
            used.erase(l);
    }

    return false;
}

void initialize(void)
{
    number.clear();
    used.clear();
    res.clear();
    for (int i = 0; i < MAXP + 1; i++) {
        number.push_back(N % 10);
        N /= 10;
    }
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &N, &K);
        initialize();
        generatenumber(MAXP, false, true);

        reverse(res.begin(), res.end());
        while (res.back() == 0)
            res.pop_back();
        reverse(res.begin(), res.end());
        for (auto r : res)
            printf("%d", r);
        printf("\n");
    }

    return 0;
}
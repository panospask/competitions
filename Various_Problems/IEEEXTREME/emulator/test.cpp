#include <cstdio>
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    int cmask = 0;
    vector <pair <int, int> > points;
    vector <bool> chosen;
    chosen.resize(n, false);
    for(int i = 0; i < 32; i++) {
        cmask |= (1 << i);
    }

    int x, y;
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        points.push_back(make_pair(x, y));
    }

    int cnt = 0;
    for(int i = 16; i < 32; i++) {
        int mask = cmask - ((1 << i) - 1);
        map <long long, vector <int> > sets;

        for(int j = 0; j < n; j++) {
            if(chosen[j]) continue;
            // auto p = make_pair(points[j].first & mask, points[j].second & mask);
            long long p = (((long long) (points[j].first & mask)) << 32) + ((long long) (points[j].second & mask));
            if(sets.find(p) == sets.end()) {
                vector <int> temp;
                temp.push_back(j);
                sets[p] = temp;
            }else sets[p].push_back(j);
        }

        for(auto &u : sets) {
            auto &v = u.second;
            for(int j = 0; j < (int)v.size() - 2; j += 3) {
                printf("%d %d %d\n", v[j], v[j + 1], v[j + 2]);
                chosen[v[j]] = chosen[v[j + 1]] = chosen[v[j + 2]] = true;
                cnt += 3;
            }
        }

        if(cnt == n) break;
    }

    vector <int> remaining;
    for(int i = 0; i < n; i++) {
        if(!chosen[i]) remaining.push_back(i);
    }

    for(int j = 0; j < (int)remaining.size() - 2; j += 3) {
        printf("%d %d %d\n", remaining[j], remaining[j + 1], remaining[j + 2]);
    }
}
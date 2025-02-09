#include <bits/stdc++.h>

using namespace std;

struct Segment {
    // The segment [l, r)
    int l, r;
    
    // Count of active numbers
    int active = 0;

    int e;
};

int N;

// segments[i]: The set of segments that have the number 2^i
map<int, set<Segment>> segments;

bool operator < (const Segment& a, const Segment& b)
{
    return a.l < b.l;
}

// Insert cur into s and merge with other segments if necessary
void insert_segment(Segment cur, set<Segment>& s)
{
    // Check if cur can be merged with any segment in s

    auto it = s.lower_bound(cur);
    if (it != s.end()) {
        Segment nxt = *it;

        if (nxt.l == cur.r) {
            cur.r = nxt.r;
            cur.active += nxt.active;
            s.erase(nxt);
        }
    }

    it = s.lower_bound(cur);
    if (it != s.begin()) {
        Segment prv = *prev(it);

        if (prv.r == cur.l) {
            cur.l = prv.l;
            cur.active += prv.active;
            s.erase(prv);
        }
    }

    s.insert(cur);
}

// Proccess s (Prerequisite: Process all segments with exponent <= s.e)
void process_segment(Segment s)
{
    // Merge the numbers of s together in pairs to create the next exponent
    // If there are an odd number of active numbers, erase one
    s.active /= 2;
    s.e++;

    insert_segment(s, segments[s.e]);
}

int main(void)
{
    freopen("mergegame.in", "r", stdin);
    freopen("mergegame.out", "w", stdout);

    int type;
    scanf("%d", &type);

    scanf("%d", &N);
    Segment cur;
    cur.e = -1;

    for (int i = 0; i < N; i++) {
        int e;
        scanf("%d", &e);
        if (e == cur.e) {
            continue;
        }

        if (cur.e != -1) {
            cur.r = i;
            cur.active = cur.r - cur.l;
            segments[cur.e].insert(cur);
        }

        cur.l = i;
        cur.e = e;
    }
    cur.r = N;
    cur.active = cur.r - cur.l;
    segments[cur.e].insert(cur);

    int ans = 0;
    while (!segments.empty()) {
        auto v = *segments.begin();

        bool found = false;
        for (auto s : v.second) {
            found = found || s.active > 0;
        }
        if (segments.size() == 1 && !found) {
            // There are no numbers left
            break;
        }

        ans = v.first;
        for (auto s : v.second) {
            process_segment(s);
        }

        segments.erase(segments.begin());
    }

    printf("%d\n", ans);

    return 0;
}
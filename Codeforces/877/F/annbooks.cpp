#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, K, Q;
set<ll> coords;
vector<int> v;
vector<ll> pref;
vector<int> freq;
vector<int> id1;
vector<int> id2;
vector<int> id3;
vector<ll> at;
vector<ll> ans;
int BLOCK_SIZE;

struct Query {
    int l, r, id;
};
bool operator < (const Query& a, const Query& b) {
    return a.r < b.r;
}
vector<vector<Query>> blocks;

int get(ll i)
{
    return lower_bound(at.begin(), at.end(), i) - at.begin();
}

void process_block(int b)
{
    ll cur_ans = 0;
    int to_add = BLOCK_SIZE * b;
    freq.assign(at.size(), 0);

    // Get the previous and insert it
    int f_add = to_add - 1;
    if (f_add >= 0) {
        freq[id1[f_add]]++;
    }
    else {
        freq[get(0)]++;
    }

    for (int i = 0; i < blocks[b].size(); i++) {
        int l = blocks[b][i].l;
        int r = blocks[b][i].r;
        int id = blocks[b][i].id;

        while (to_add <= r) {
            cur_ans += freq[id2[to_add]];
            freq[id1[to_add]]++;

            to_add++;
        }

        ans[id] = cur_ans;
        while (f_add < l - 1) {
            if (f_add < 0) {
                freq[get(0)]--;
                ans[id] -= freq[get(K)];
            }
            else {
                freq[id1[f_add]]--;
                ans[id] -= freq[id3[f_add]];
            }

            f_add++;
        }

        while (f_add >= b * BLOCK_SIZE) {
            f_add--;
            if (f_add >= 0)
                freq[id1[f_add]]++;
            else
                freq[get(0)]++;
        }
    }
}

int main(void)
{
    scanf("%d %d", &N, &K);

    v.resize(N);
    pref.resize(N);

    for (int i = 0; i < N; i++) {
        int type;
        scanf("%d", &type);

        if (type == 1)
            v[i] = +1;
        else
            v[i] = -1;
    }
    coords.insert(0);
    coords.insert(K);
    for (int i = 0; i < N; i++) {
        int num;
        scanf("%d", &num);

        v[i] *= num;
        pref[i] = v[i];
        if (i)
            pref[i] += pref[i - 1];

        coords.insert(pref[i]);
        coords.insert(pref[i] - K);
        coords.insert(K + pref[i]);
    }

    int cnt = 0;
    for (auto c : coords) {
        at.push_back(c);
    }
    freq.resize(coords.size());
    id1.resize(N);
    id2.resize(N);
    id3.resize(N);
    coords.clear();

    for (int i = 0; i < N; i++) {
        id1[i] = get(pref[i]);
        id2[i] = get(pref[i] - K);
        id3[i] = get(K + pref[i]);
    }

    BLOCK_SIZE = sqrt(N);
    blocks.resize(BLOCK_SIZE + 1);

    scanf("%d", &Q);
    ans.resize(Q);
    for (int i = 0; i < Q; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--; r--;

        blocks[l / BLOCK_SIZE].push_back({l, r, i});
    }

    for (int b = 0; b < BLOCK_SIZE + 1; b++) {
        sort(blocks[b].begin(), blocks[b].end());
        process_block(b);
    }

    for (int i = 0; i < Q; i++)
        printf("%lld\n", ans[i]);

    return 0;
}
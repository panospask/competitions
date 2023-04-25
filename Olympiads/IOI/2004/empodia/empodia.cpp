#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

struct empodiostart {
    int pos;
    int val;
    int max_between;
    int highest_used;
};

int n;
vector<int> seq;
stack<empodiostart> pos_begin;
vector<ii> anspos;
set<int> used;

int main(void)
{
    scanf("%d", &n);
    seq.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &seq[i]);

    int minele, maxele, pos;
    for (int i = 0; i < n; i++) {
        while (!pos_begin.empty() && pos_begin.top().val > seq[i]) {
            maxele = max(maxele, pos_begin.top().max_between);
            pos_begin.pop();
        }

        maxele = max(maxele, seq[i]);
        if (!pos_begin.empty() && maxele == seq[i]) {
            // Check if it's an empodio
            int minele = pos_begin.top().val;
            if (maxele - minele == i - pos_begin.top().pos) {
                anspos.push_back(make_pair(pos_begin.top().pos, i));
                while (!pos_begin.empty()) {
                    pos_begin.pop();
                }
            }
            else {
                empodiostart cur;
                cur.max_between = maxele;
                cur.pos = i;
                cur.val = seq[i];
                cur.highest_used;
                maxele = 0;

                pos_begin.push(cur);
            }
        }
        else {
            empodiostart cur;
            cur.max_between = maxele;
            cur.pos = i;
            cur.val = seq[i];
            maxele = 0;

            pos_begin.push(cur);
        }

    }
    printf("%d\n", (int)anspos.size());
}
#include <bits/stdc++.h>

using namespace std;

int find_biggest_sequence(string& s, vector<int>&used, stack<int>& places)
{
    stack<int> forw;
    for (int i = 0; i < s.size(); i++) {
        if (used[i])
            continue;

        if (s[i] == '(')
            forw.push(i);
        else {
            if (!forw.empty()) {
                places.push(i);
                places.push(forw.top());
                forw.pop();
            }
        }
    }

    return places.size();
}

int n;
string sequence, revseq;
stack<int> forw, backw;
vector<int> used;
int ttl_use = 0;

void solve(void)
{
    cin >> n >> sequence;
    revseq = sequence;
    reverse(revseq.begin(), revseq.end());
    used.assign(n, false);

    int fr = 0, bc = 0;
    for (int i = 0; i < n; i++) {
        if (sequence[i] == '(')
            fr++;
        else
            bc++;
    }

    if (fr != bc) {
        printf("-1\n");
        return;
    }

    int ans = 0;
    ttl_use = 0;
    while (ttl_use < n) {
        ans++;
        int c = find_biggest_sequence(sequence, used, forw);
        reverse(used.begin(), used.end());
        int d = find_biggest_sequence(revseq, used, backw);
        reverse(used.begin(), used.end());

        if (c > d) {
            ttl_use += c;
            while (!backw.empty())
                backw.pop();
            while (!forw.empty()) {
                used[forw.top()] = ans;
                forw.pop();
            }
        }
        else {
            reverse(used.begin(), used.end());
            ttl_use += d;
            while (!forw.empty())
                forw.pop();
            while (!backw.empty()) {
                used[backw.top()] = ans;
                backw.pop();
            }

            reverse(used.begin(), used.end());
        }
    }

    printf("%d\n", ans);
    for (int i = 0; i < n; i++)
        printf("%d ", used[i]);
    printf("\n");
}

int main(void)
{
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--)
        solve();
}
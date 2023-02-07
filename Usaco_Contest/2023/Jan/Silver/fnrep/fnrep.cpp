#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

int t;
string instr;
string outstr;

unordered_map<char, char> letter_match;
unordered_map<char, set<char>> want_to_become;
set<char> seen;
unordered_map<char, bool> proccessed;
unordered_map<char, int> c_to_num;
bool visited[60];
int numcount = 0;

// Graphs
set<int> curpath;
int go_to[60];
vector<int> inlist[60];

bool dfs(int node, int prevnode)
{
    if (visited[node]) {
        if (curpath.count(node) == 1 && node != prevnode)
            return false;
        else 
            return true;
    }
    visited[node] = true;
    curpath.insert(node);

    if (go_to[node] == -1)
        return true;

    return dfs(go_to[node], node);
}

int main(void)
{
    // freopen("fnrep.in", "r", stdin);
    // freopen("fnrep.out", "w", stdout);

    scanf("%d", &t);
    for (int x = 0; x < t; x++) {
        cin >> instr;
        cin >> outstr;

        int sz = instr.size();
        letter_match.clear();
        want_to_become.clear();
        seen.clear();
        proccessed.clear();
        c_to_num.clear();
        numcount = 0;
        for (int i = 0; i < 60; i++) {
            go_to[i] = -1;
            inlist[i].clear();
        }
        char inc, outc;
        bool isgood = true; 

        for (int i = 0; i < sz; i++) {
            inc = instr[i];
            outc = outstr[i];

            if (seen.count(inc) == 0) {
                seen.insert(inc);
                c_to_num[inc] = numcount++;
            }
            if (seen.count(outc) == 0) {
                seen.insert(outc);
                c_to_num[outc] = numcount++;
            }

            if (letter_match.count(inc) == 0) {
                seen.insert(inc);
                letter_match[inc] = outc;
                want_to_become[outc].insert(inc);
            }
            else if (letter_match[inc] != outc)
                isgood = false;
        }

        if (!isgood) {
            printf("-1\n");
            continue;
        }

        int numof;
        for (auto l : seen) {
                numof = c_to_num[l];
                go_to[numof] = c_to_num[letter_match[l]];
                inlist[c_to_num[letter_match[l]]].pb(numof);
        }

        // Graph ready
        int ttl_swaps = 0;
        bool has_cycle;
        bool find_sec;
        memset(visited, false, sizeof(visited));
        for (int i = 0; i < numcount; i++) {
            if (!visited[i]) {
                curpath.clear();
                has_cycle = !dfs(i, -1);

                if (has_cycle) {
                    find_sec = false;
                    for (auto node : curpath) {
                        if (inlist[node].size() > 1)    
                            find_sec = true;
                    }

                    if (curpath.size() == 1)
                        ttl_swaps += 0;
                    else if (find_sec)
                        ttl_swaps += curpath.size();
                    else 
                        ttl_swaps += curpath.size() + 1;
                }
                else 
                    ttl_swaps += curpath.size() - 1;
            }
        }


        printf("%d\n", ttl_swaps);
    }

    return 0;
}
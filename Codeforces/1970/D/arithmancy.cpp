#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N;
map<int, pi> m;

int calc(string a, string b) {
    string c = a + b;

    vector<string> tot;
    for (int l = 0; l < c.size(); l++) {
        for (int r = l; r < c.size(); r++) {
            tot.push_back(c.substr(l, r - l + 1));
        }
    }

    sort(tot.begin(), tot.end());
    tot.resize(unique(tot.begin(), tot.end()) - tot.begin());


    return tot.size();
}

int main(void) {
    cin >> N;
    
    vector<string> v;
    if (N >= 1) {
        v.push_back("X");
    }
    if (N >= 2) {
        v.push_back("XXO");
    }
    if (N >= 3) {
        v.push_back("OOOOOOOOOOXXX");
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            m[calc(v[i], v[j])] = {i, j};
        }
    }

    for (auto s : v) {
        cout << s << endl;
    }
    cout.flush();

    
    int Q;
    cin >> Q;
    
    while (Q--) {
        int p;
        cin >> p;
        
        auto res = m[p];
        cout << res.first + 1 << ' ' << res.second + 1 << endl;
        cout.flush();

    }

    return 0;
}
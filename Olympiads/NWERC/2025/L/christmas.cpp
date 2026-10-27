#include <bits/stdc++.h>

using namespace std;

const int NUM = 10;

int N;
vector<vector<string>> results;

// times[pos][artist] with pos 0 being everything
vector<map<string, int>> times;

bool customcmp (string a, string b) {
    for (int j = 0; j <= NUM; j++) {
        if (times[j][a] > times[j][b]) {
            return true;
        }
        if (times[j][a] < times[j][b]) {
            return false;
        }
    }
    return false;
}

int main(void) {
    cin >> N;

    results.resize(N, vector<string>(NUM + 1));
    times.resize(NUM + 1);
    vector<string> possible;
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= NUM; j++) {
            cin >> results[i][j];
            possible.push_back(results[i][j]);
            times[0][results[i][j]]++;
            times[j][results[i][j]]++;
        }
    }

    sort(possible.begin(), possible.end());
    possible.resize(unique(possible.begin(), possible.end()) - possible.begin());
    sort(possible.begin(), possible.end(), customcmp);

    if (possible.size() >= 2 && customcmp(possible[0], possible[1]) == false) {
        cout << "tie" << endl;
    }
    else {
        cout << possible.front() << endl;
    }

    return 0;
}
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> p;

ll calcucate(int remaining, ll weight1, ll weight2) {
    int pos = N - remaining;
    
    if (remaining == 1) {
        if (weight1 < weight2) {
            weight1 += p[pos];
        }
        else {
            weight2 += p[pos];
        }

        return abs(weight1 - weight2);
    }

    // We know the first N - remaining elements and we are testing the element in position pos
    return min(calcucate(remaining - 1, weight1 + p[pos], weight2), calcucate(remaining - 1, weight1, weight2 + p[pos]));
}

int main(void) {
    cin >> N;
    
    p.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> p[i];
    }

    cout << calcucate(N, 0, 0) << endl; 
}
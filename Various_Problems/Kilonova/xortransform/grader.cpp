#include <bits/stdc++.h>
#include "xortransform.h"

using namespace std;

int main() {
    ifstream cin("xortransform.in");
    ofstream cout("xortransform.out");
    int n, m, q;
    cin >> n >> m >> q;
    int** matrix = new int* [n];
    for (int i = 0;i < n;++i) {
        matrix[i] = new int[m];
        for (int j = 0;j < m;++j)
            cin >> matrix[i][j];
    }
    initialize(n, m, matrix);
    for (int i = 0;i < q;++i) {
        int x;
        cin >> x;
        cout << query(x) << '\n';
    }
}
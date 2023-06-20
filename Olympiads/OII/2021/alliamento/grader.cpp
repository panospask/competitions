#include <iostream>
#include <vector>
#include "allenamento.h"
using namespace std;

long long conta(int N, vector<int> A);

int main() {
    cin.exceptions(istream::failbit);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> A(N);
    for (int& i : A) {
        cin >> i;
    }

    cout << conta(N, A);

    cout << endl;

    return 0;
}

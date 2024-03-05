#include <bits/stdc++.h>

using namespace std;

int N;
vector<string> strings;

bool strcomp(const string& a, const string& b)
{
    // 2 * maxsize to avoid errors
    // Oficiall solution says to compare a + b and b + a
    for (int i = 0; i < 2 * max(a.size(), b.size()); i++) {
        int ind1 = i % a.size();
        int ind2 = i % b.size();
        if (a[ind1] < b[ind2])
            return true;
        if (a[ind1] > b[ind2])
            return false;
    }
    return false;
}

int main(void)
{
    cin >> N;

    strings.resize(N);
    for (int i = 0; i < N; i++)
        cin >> strings[i];
    sort(strings.begin(), strings.end(), strcomp);

    for (int i = 0; i < N; i++)
        cout << strings[i];
    cout << endl;

    return 0;
}
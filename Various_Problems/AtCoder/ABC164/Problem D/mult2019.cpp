#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

string s;
int n;
int suffarr[MAXN + 5];
int arr[MAXN + 5];
unordered_map<int, int> valcount;

int main(void)
{
    cin >> s;

    n = s.size();
    for (int i = 0; i < n; i++)
        arr[i] = s[i] - '0';

    suffarr[n] = 0;
    int modby = 1;
    valcount[0]++;
    for (int i = n - 1; i >= 0; i--) {
        suffarr[i] = (suffarr[i + 1] + (arr[i] * modby) % 2019) % 2019;
        valcount[suffarr[i]]++;
        modby *= 10;
        modby %= 2019;
    }

    // suffarr[i] = 1 * suffarr[n - 1] + 10 * suffar[n - 2] + ... + (10^n-i-1) * suffar[i]

    long long int ans = 0;
    for (auto val : valcount) 
        ans += (val.second) * (long long int)(val.second - 1) / 2;

    printf("%lld\n", ans);
    return 0;
}